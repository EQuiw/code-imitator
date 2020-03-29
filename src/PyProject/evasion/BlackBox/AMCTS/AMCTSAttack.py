import os
import numpy as np
import time
import typing
import sys
import traceback
import subprocess

import Configuration as Config
import evasion.utils_attack as ua

from evasion.BBAttackHandler import BBAttackHandler
from evasion.BBAttackInstance import BBAttackInstance
from evasion.AttackStatus import AttackStatus
from evasion.Author import Author
from classification.LearnSetups.LearnSetup import LearnSetup
from evasion.Transformers.TransformerBase import TransformerBase
from evasion.AttackResult import AttackResult
from evasion.AttackMode import AttackMode

from evasion.BBMCTSBatchAttackInstanceHandler import BBMCTSBatchAttackInstanceHandler
import evasion.Transformers.TransformerBase

from evasion.BlackBox.AMCTS.Tree import Tree
from evasion.BlackBox.AMCTS.Node import Node
from evasion.BlackBox.AMCTS.StateWithAttackInstance import StateWithAttackInstance
import evasion.BlackBox.AMCTS.State
from evasion.BlackBox.AttackSettings import MCTSClassicSettings
from evasion.BlackBox.AMCTS.MCTS_Utils import ExpandNodeException
import evasion.BlackBox.AMCTS.UCTHeuristic as UCTHeuristic


class AMonteCarloTreeSearch(BBAttackHandler):
    """
    Adapted Monte Carlo Tree Search.
    Advantage over SimAnn.
    - We observed that if we do not find any direction, it is hard to find the sequence that goes towards the author.
    Here MCTS could help very much as we can explore much more paths more quickly than SimAnn.
    - And if we find a direction, it is often not so bad to go to this direction as we do in our adapted SimAnnealing.
    """

    def __init__(self, attackdirauth: str,
                 sourceauthor: Author, targetauthor: Author,
                 learnsetup: LearnSetup,
                 mctsclassicsettings: MCTSClassicSettings,
                 initialseed: int = 42,
                 ) -> None:

        # call parent's init method
        super(AMonteCarloTreeSearch, self).__init__(
            attackdirauth=attackdirauth, sourceauthor=sourceauthor, targetauthor=targetauthor,
            learnsetup=learnsetup, max_iterations=mctsclassicsettings.max_outer_iterations, attack_mode=mctsclassicsettings.attack_mode,
            initialseed=initialseed, early_stop=mctsclassicsettings.early_stop
        )

        self.mctssettings = mctsclassicsettings

        self.savemorelogfiles = Config.savemorelogfiles
        # if we check the error files from transformations and their compilation, output is checked anyway.
        self.check_err_files_transformations = Config.savemorelogfiles # todo

        # create the instance to save the result later
        self.attackresult = AttackResult(sourceauthor=self.sauthor, targetauthor=self.tauthor)

        self.tree: Tree = Tree()


    # @Overwrite
    def run_attack(self) -> AttackResult:

        try:
            # A. Init Attack Instance
            attackinstance = BBAttackInstance(sourceauthor = self.sauthor, attackdirauth=self.attackdirauth,
                                              targetauthor = self.tauthor, bbattackhandler=self)
            self.attackresult.initial_feature_vec = attackinstance.attack_data_merged.getfeaturematrix()[0, :].toarray().reshape(-1)

            current_root_node: Node = self.tree.root
            root_state: StateWithAttackInstance = StateWithAttackInstance(transformer=None,
                                                                          attackinstance=attackinstance)
            current_root_node.state = root_state


            # B. find next move multiple times
            for i in range(0, self.max_iterations):

                attackinstance.logger.logger.debug("\n\nOuter Iteration: {}".format(i))

                # B-1 Expand tree to find a suitable next move. If we already succeed with a seq., we break.
                succesfull_attackinstance = self.mcts_core(attackinstance=attackinstance, outer_iteration_index=i)
                if succesfull_attackinstance is not None:
                    attackinstance = succesfull_attackinstance
                    break

                # B-2 Perform a single step move. If we already succeed, we break.
                attackinstance = self.perform_next_move(attackinstance=attackinstance, outer_iteration_index=i)
                if self.on_next_move_success(attackinstance=attackinstance) is True:
                    break

                # B-3 Check for early stop.
                if self.check_for_early_stop(attackinstance=attackinstance, current_outer_iteration=i) is True:
                    break


            # C. Finally, collect further information about source file after evasion
            self.attackresult.final_feature_vec = attackinstance.attack_data_merged.getfeaturematrix()[0,
                                                 :].toarray().reshape(-1)
            assert attackinstance.log_chosentransformers.shape[1] == 5  # we expect 5 columns, adapt this value if more..
            self.attackresult.log_chosentransformers = attackinstance.log_chosentransformers
            self.attackresult.extract_changes_linesofcode(pathtooriginalfile=attackinstance.original_source_file,
                                                         pathtonewfile=attackinstance.source_file)

            attackinstance.logger.logger.info("-----> {} <----- from {} to {} \n".
                                                  format(self.attackresult.attackstatus.name, self.sauthor.author,
                                                         self.tauthor.author))


        except Exception as e:
            err_msg: str = "***MCTS: Unexpected ERROR *** {} -> {} with {}".format(
                self.sauthor.author, self.tauthor.author, str(e))
            print(err_msg, file=sys.stderr)
            traceback.print_tb(e.__traceback__)
            self.attackresult.attackstatus = AttackStatus.ERROR
            self.attackresult.error_message = [str(err_msg), traceback.format_exc()]

        finally:
            try:
                attackinstance.logger.close_logger()
            except Exception:
                print("Could not close logger in attackinstance", file=sys.stderr)

            return self.attackresult


    def create_log_dir(self, logpath: str, logdir: str):

        # create log dir for current iteration
        if self.savemorelogfiles is True:
            logdir_iter = os.path.join(logpath, logdir)
            os.makedirs(logdir_iter)
        else:
            logdir_iter = None

        return logdir_iter



    def on_next_move_success(self, attackinstance: BBAttackInstance):
        if self.wasattacksuccessfull(attackinstance=attackinstance) is True:
            self.attackresult.attackstatus = AttackStatus.SUCCESS
            return True



    def perform_next_move(self, attackinstance: BBAttackInstance, outer_iteration_index: int):
        # Check if no children are available.
        if len(self.tree.root.childlist) == 0:
            attackinstance.logger.logger.error("Break Up due to empty children list at {}. iter.".format(outer_iteration_index))
            raise Exception("Unusual: Empty Children List at Outer Iteration: {}".format(outer_iteration_index))

        # It can also happen at outer_iteration >= 1, that next_move fails because chosen transformer had
        # another basis as source file (as we do not keep seeds). (see Note #2 in State class).
        # We thus need to iterate here over children until success or no children, then raise Exception.

        previousrootnode: Node = self.tree.root
        noofchildren: int = len(self.tree.root.childlist)
        child_successfully_chosen = False
        for ci in range(noofchildren):
            prefix_outer = "_" + str(ci) if ci >= 1 else ""

            winnernode = UCTHeuristic.select_next_child_wrt_mean_score(node=self.tree.root,
                                                                       attack_mode=self.mctssettings.attack_mode)

            attackinstance.logger.logger.debug("\n\n")
            attackinstance.logger.logger.debug("~~>Next outer node id:" + str(winnernode.unique_node_id))

            try:
                attackinstance, tr = self.repeat_winnernode_transformation_on_outerdir(attackinstance=attackinstance,
                                                                                   prefix=str(outer_iteration_index) + prefix_outer,
                                                                                   transformer_id=winnernode.state.transformer_uniqueid,
                                                                                   transformer_seed=winnernode.state.seed)
            except ExpandNodeException as e:
                err_msg = " ".join(["Perform Next Move Exception (will continue); Node:", str(winnernode.unique_node_id), "with:", str(e)])
                attackinstance.logger.error(err_msg)
                print(err_msg, file=sys.stderr)
                # This winnernode should not have any children with AttackInstances, otherwise we went in mcts_core
                # through this node, and then we should have seen the same problem?!! So just remove it from tree:
                self.tree.root.childlist.remove(winnernode)
                continue

            self.tree.switch_rootnode(newroot = winnernode)

            # overwrite winner node's state, it can be that winner node has or has not an attack instance already.
            if isinstance(winnernode.state, StateWithAttackInstance):
                winnernode.state.attackinstance.cleandir(currentbaselevel=self.attackdirauth)

            nextstate: StateWithAttackInstance = StateWithAttackInstance(transformer=tr, attackinstance=attackinstance)
            winnernode.state = nextstate

            # Go one node above and delete all other instances recursively, except all under winnernode.
            self.__clean_attackinstances_from_old_nodes(rootnode=previousrootnode, excludenode=winnernode)
            child_successfully_chosen = True
            break


        # This should never happen since at least one node should be available, the successor from a sequence ...
        if child_successfully_chosen is False:
            raise Exception("Perform Next Move; Attack Stop since no child is available at {}. iter".
                            format(outer_iteration_index))
        return attackinstance


    def __clean_attackinstances_from_old_nodes(self, rootnode: Node, excludenode: Node) -> None:
        for child in rootnode.childlist:
            if child != excludenode and isinstance(child.state, StateWithAttackInstance) is True:
                child.state.attackinstance.cleandir(currentbaselevel=self.attackdirauth)
                # a child can only have an attack instance if its parent had an attack instance, thus
                # we only call the cleaning method recursively for children with an attack instance.
                self.__clean_attackinstances_from_old_nodes(rootnode=child, excludenode=excludenode)


    def mcts_core(self, attackinstance: BBAttackInstance, outer_iteration_index: int):
        """
        The core MCTS iterations. Includes promising node selection, its expansion and backpropagation.
        :param attackinstance:
        :param outer_iteration_index:
        :return: None Or attack instance if search was successful and we can stop.
        """
        rootnode: Node = self.tree.root

        # 1. Set up pathes for logging
        logdir_outer_iter = self.create_log_dir(logpath=attackinstance.log_directory, logdir="_".join(["mcts", str(outer_iteration_index)]))

        for inner_iteration_index in range(0, self.mctssettings.max_inner_iterations):
            # the number of times we select promising nodes, and perform random playout...
            logdir_outer_inner_iter = self.create_log_dir(logpath=logdir_outer_iter, logdir="_".join(["iter",
                                          str(inner_iteration_index)]))

            # 2. Selection
            # We may fail, if we cannot repeat a further transformation, since we neglect the seed for state-id.
            # See Note #2 in State Class for this problem.
            try:
                time1 = time.time()
                promisingnode: Node = self.selectpromisingnode(rootnode=rootnode,
                                                               inner_iteration_index=inner_iteration_index,
                                                               logdir_outer_inner_iter=logdir_outer_inner_iter)
                time2 = time.time()
                attackinstance.logger.debug_details("Time: Selection: {}s".format(time2-time1))
            except ExpandNodeException as e:
                attackinstance.logger.error("Select Promising Node Exception (will continue):" + str(e))
                print("Select Promising Node Exception (but will continue):" + str(e), file=sys.stderr)
                continue


            # 3. Simulation (includes step playout_sequences (generate sequences), expand-tree and backpropagate).
            nodetoexplore: Node = promisingnode
            succesfull_attackinstance = self.simulate_random_playouts(nodetoexplore=nodetoexplore,
                                                                      current_global_attackinstance=attackinstance,
                                                                      inner_iteration_index=inner_iteration_index)
            time4 = time.time()
            attackinstance.logger.debug_details("Time: Playout:{}s".format(time4 - time2))


            if succesfull_attackinstance is not None:
                return succesfull_attackinstance

        attackinstance.logger.logger.info("Final Root Score at {}th-Iter: {}, {}:".format(outer_iteration_index,
               str(self.tree.root.state.getMeanScore()), str(self.tree.root.state.getSdScore())))
        return None



    def selectpromisingnode(self, rootnode: Node,
                            inner_iteration_index: int,
                            logdir_outer_inner_iter: str) -> Node:

        if isinstance(rootnode.state, StateWithAttackInstance) is False:
            raise Exception("Select Promising Node, Node without State + Attack Instance")

        node = rootnode
        while len(node.childlist) > 0:
            newnode = UCTHeuristic.find_best_node_with_uct_heuristic(node=node,
                                                                     attack_mode=self.mctssettings.attack_mode,
                                                                     iteration_index=inner_iteration_index)

            if isinstance(newnode.state, StateWithAttackInstance) is False:
                # expand and return new node... fill it with an own attack instance to this end...
                newattackdir = os.path.join(self.attackdirauth, "prom_node_" + str(newnode.unique_node_id),
                                            self.sauthor.author)

                try:
                    tempattackinstance, temptransformer, result_string = self.expand_node_single(
                        attackinstance=node.state.attackinstance,
                        prefix=str(inner_iteration_index) + "_" + str(newnode.unique_node_id),
                        transformer_id=newnode.state.transformer_uniqueid,
                        transformer_seed=newnode.state.seed,
                        newattackdir=newattackdir,
                        log_directory=logdir_outer_inner_iter)
                except ExpandNodeException as e:
                    # if we have an exception here, we should remove the problem node from tree to avoid
                    # that we select it again later; we can just remove it, since it has no attackinstance so far.
                    node.childlist.remove(newnode)
                    raise e


                tempattackinstance.logger.logger.debug("Next promising node (ID: {}):".format(newnode.unique_node_id)
                                                       + result_string)

                newstate: StateWithAttackInstance = StateWithAttackInstance(
                    attackinstance=tempattackinstance,
                    transformer=temptransformer
                )
                newnode.state = newstate
                return newnode
            else:
                node = newnode

        return node



    def simulate_random_playouts(self, nodetoexplore: Node,
                                 current_global_attackinstance: BBAttackInstance,
                                 inner_iteration_index: int) \
            ->  typing.Optional[BBAttackInstance]:
        """
        Simulate multiple playouts. (!= MCTS, where we play one game, here we can play multiple games
        --- just to explore multiple pathes. We can easily explore many pathes with BBMCTSBatchAttackInstanceHandler
        very efficiently via gnu parallel)
        :param nodetoexplore:
        :param current_global_attackinstance:
        :param inner_iteration_index: inner iteration index.
        :return:
        """

        # A. Generate multiple sequences
        processes_list = []

        no_sequences = max(self.mctssettings.number_of_sequences_in_random_playout_0 if inner_iteration_index == 0 else\
                        self.mctssettings.number_of_sequences_in_random_playout_further, 2)

        for path_index in range(0, no_sequences):
            # e.g. for-transformer, if-transformer, ..., declaration-transformer

            newtemppath = os.path.join(self.attackdirauth, "temp" + str(path_index), self.sauthor.author)
            if Config.savemorelogfiles is True:
                logdir_seq_path = os.path.join(self.attackdirauth, "temp" + str(path_index), "log" + str(path_index))
                os.makedirs(logdir_seq_path)
            else:
                logdir_seq_path = None

            tempattackinstance = nodetoexplore.state.attackinstance.clone(attackdirauth=newtemppath, newlogdir=logdir_seq_path)
            processes_list.append(tempattackinstance)

        mcts_handler = BBMCTSBatchAttackInstanceHandler(noofcores=self.noofparallelthreads,
                                                        attackdirauth=self.attackdirauth,
                                                        inputlist=processes_list,
                                                        seed=self.seed + nodetoexplore.unique_node_id + 91,
                                                        path_length=self.mctssettings.path_length_in_random_playout,
                                                        check_err_files_transformations=self.check_err_files_transformations,
                                                        repeat_addtemplate_transformers=self.mctssettings.repeat_template_transformers)

        try:
            mcts_handler.batch_do_transformations()
        except subprocess.TimeoutExpired:
            mcts_handler.inputlist[0].logger.error("Timeout Exception occured at {}. inner-iteration.\n".
                                                   format(inner_iteration_index))
            for attinst in processes_list:
                attinst.cleandir(currentbaselevel=self.attackdirauth)
            return None

        # B. Expand Tree with Sequences
        self.expand_node_batch_mode(mcts_handler=mcts_handler, curnodestart=nodetoexplore,
                                    inner_iteration_index = inner_iteration_index)


        # C. Backpropagate Score
        for current_state_sequence in mcts_handler.mcts_statesequences:
            if current_state_sequence.final_score is not None:
                lastnode = current_state_sequence.last_node_of_sequence
                self.backpropagation(nodetoexplore=lastnode, score=current_state_sequence.final_score)

        # D. Check if we found a match w.r.t to dodging / impersonation so that we can already stop != MCTS
        # We sort all sequences w.r.t to their length, so that we favor shorter sequences if they are succ.
        sorted_indices_ic = sorted([(ic, len(mcts_handler.mcts_statesequences[ic].states)) \
                                        for ic in range(len(mcts_handler.inputlist))], key=lambda x: x[1])

        for ic, _ in sorted_indices_ic:
            if mcts_handler.mcts_statesequences[ic].final_score is not None:
                if self.wasattacksuccessfull(attackinstance=mcts_handler.inputlist[ic]) is True:

                    out = self.do_on_successfull_sequence_in_playout(
                        current_global_attackinstance=current_global_attackinstance,
                        nodetoexplore=nodetoexplore,
                        ic=ic,
                        mcts_handler=mcts_handler,
                        processes_list=processes_list)
                    if out is not None:
                        return out


        # E. Cleaning
        for attinst in processes_list:
            attinst.cleandir(currentbaselevel=self.attackdirauth)
        return None


    def expand_node_batch_mode(self, mcts_handler: BBMCTSBatchAttackInstanceHandler,
                               curnodestart: Node,
                               inner_iteration_index: int):

        # We first exclude sequences, then extend the tree.
        # Why? It can still happen that we have nodes that were not successful at the execution / extraction step (e.g.
        # output behaviour changed)

        # 1. Exlude sequences in current sequence batch of mcts_handler that are empty or occur multiple times
        mcts_handler.keep_only_positive_unique_sequences()

        # 2. Exlude sequences that are already present in tree... we do not need to perform them again...
        for current_state_sequence in mcts_handler.mcts_statesequences:
            if current_state_sequence.exctract_and_do_hash_analysis is True:
                curnode: Node = curnodestart

                for seq_index in range(len(current_state_sequence.states)):

                    curstate: evasion.BlackBox.AMCTS.State.State = current_state_sequence.states[seq_index]
                    assert curstate.state_id is not None  # must be there

                    curnode = curnode.get_child_with_stateid(state_id=curstate.state_id)
                    if curnode is None:
                        break

                if curnode is not None:
                    # the sequence is 1:1 present in tree from curnodestart already
                    current_state_sequence.exctract_and_do_hash_analysis = False

        # 3. Execute all remaining sequences
        try:
            mcts_handler.batch_execute_extractfeatures()
        except subprocess.TimeoutExpired:
            mcts_handler.inputlist[0].logger.error("Timeout Exception in execution phase at {}. inner iteration.\n".
                                                   format(inner_iteration_index))
            return

        # 4. Expand Tree w.r.t to only completely successful sequences. Create new nodes...
        for current_state_sequence in mcts_handler.mcts_statesequences:
            if current_state_sequence.final_score is not None \
                and current_state_sequence.exctract_and_do_hash_analysis is True:

                curnode: Node = curnodestart
                for seq_index in range(len(current_state_sequence.states)):

                    curstate: evasion.BlackBox.AMCTS.State.State = current_state_sequence.states[seq_index]
                    assert curstate.state_id is not None  # must be there

                    newnode = curnode.get_child_with_stateid(state_id=curstate.state_id)
                    if newnode is None:
                        newnode = self.tree.create_new_node(parent=curnode, state=curstate)
                        curnode.add_child(newnode)

                    curnode = newnode

                current_state_sequence.last_node_of_sequence = curnode


    def backpropagation(self, nodetoexplore: Node, score: float):
        tempnode: Node = nodetoexplore
        while tempnode is not None:
            tempnode.state.VisitCount += 1
            tempnode.state.Scores.append(score)
            tempnode = tempnode.parent


    def wasattacksuccessfull(self, attackinstance: BBAttackInstance):

        if (self.sauthor.true_class == self.tauthor.true_class and
            self.sauthor.true_class != attackinstance.classprednew) or \
                (self.sauthor.true_class != self.tauthor.true_class and
                 self.tauthor.true_class == attackinstance.classprednew):
            return True
        return False


    def do_on_successfull_sequence_in_playout(self,
                                              current_global_attackinstance: BBAttackInstance,
                                              nodetoexplore: Node,
                                              ic: int,
                                              mcts_handler: BBMCTSBatchAttackInstanceHandler,
                                              processes_list: typing.List[BBAttackInstance]):
        """
        Stuff that we do if we find a succesful sequence in simulate_random_playouts.
        :return: AttackInstance
        """

        # We know that this sequence was succesfull, in repeat_winner_sequence, we will repeat
        # the winner sequence on the global attack directory, thus if not root node, make nodetoexplore
        # to current global attack instance.
        if current_global_attackinstance != nodetoexplore.state.attackinstance:
            current_global_attackinstance = nodetoexplore.state.attackinstance.clone(
                attackdirauth=current_global_attackinstance.attackdirauth,
                newlogdir=current_global_attackinstance.log_directory)

        attackinstance = self.repeat_winner_sequence(mcts_handler=mcts_handler,
                                                     ic=ic,
                                                     attackinstance=current_global_attackinstance)

        self.attackresult.attackstatus = AttackStatus.SUCCESS
        for attinst in processes_list:
            attinst.cleandir(currentbaselevel=self.attackdirauth)
        return attackinstance





    def expand_node_single(self, attackinstance: BBAttackInstance, prefix: str, transformer_id, transformer_seed,
                                newattackdir: str, log_directory: str):

        outertempattackinstance = attackinstance.clone(attackdirauth=newattackdir,
                                                       newlogdir=log_directory)

        currenttransformerobj: TransformerBase = outertempattackinstance.transformerhandler. \
            get_specified_transformation_per_uniqueid(uniqueid=transformer_id)

        queue_outer = []
        ua.run_hill_simulation(args=(outertempattackinstance, prefix, currenttransformerobj,
                                     transformer_seed, queue_outer))

        nextransformerindex, currenttransformer, besttransfcall, \
            successtransf, scoreprednew, classprednew = queue_outer[0]
        if successtransf is not True:
            outertempattackinstance.cleandir(currentbaselevel=self.attackdirauth)
            raise ExpandNodeException("Chosen Transformation for next outer iteration not succesfull:" + str(besttransfcall) + "\n")

        result_string = " {}:`{}` successfull with {} ({}) [Before:{}({})]".\
            format(prefix, besttransfcall, round(scoreprednew, 4), classprednew,
                   round(outertempattackinstance.original_predscore, 4), self.tauthor.true_class)

        return outertempattackinstance, currenttransformerobj, result_string



    def repeat_winnernode_transformation_on_outerdir(self, attackinstance: BBAttackInstance,
                                                     prefix: str, transformer_id, transformer_seed):

        if Config.savemorelogfiles is True:
            logdir_iter_final_path = os.path.join(attackinstance.log_directory, "outer_" + prefix)
            os.makedirs(logdir_iter_final_path)
        else:
            logdir_iter_final_path = None

        newattackdir = os.path.join(self.attackdirauth, "outer_temp", self.sauthor.author)
        outertempattackinstance, currenttransformerobj, result_string = self.expand_node_single(
            attackinstance=attackinstance, prefix=prefix,
            transformer_id=transformer_id, transformer_seed=transformer_seed,
            newattackdir=newattackdir, log_directory=logdir_iter_final_path
        )
        attackinstance.logger.logger.info("~~> Best Instance:" + result_string)

        attackinstance = outertempattackinstance.clone(attackdirauth=attackinstance.attackdirauth,
                                                       newlogdir=attackinstance.log_directory)
        outertempattackinstance.cleandir(currentbaselevel=self.attackdirauth)

        return attackinstance, currenttransformerobj


    def repeat_winner_sequence(self, mcts_handler: BBMCTSBatchAttackInstanceHandler, ic: int,
                               attackinstance: BBAttackInstance):

        # Be aware that statesequences uses State class, not StateWithAttackInstance class.
        for ik, winner_state in enumerate(mcts_handler.mcts_statesequences[ic].states):
            attackinstance, _ = self.repeat_winnernode_transformation_on_outerdir(attackinstance=attackinstance,
                                                              prefix="winner_"+str(ik),
                                                              transformer_id=winner_state.transformer_uniqueid,
                                                              transformer_seed=winner_state.seed)

        if self.wasattacksuccessfull(attackinstance=attackinstance) is False:
            raise Exception("Repeating Winner Sequence led to unsuccess. Check why?\n")

        return attackinstance

        # Alternatively, we could simply use the attack instance that we created in the winner sequence
        # attackinstance = mcts_handler.inputlist[ic].clone(attackdirauth=attackinstance.attackdirauth,
        #                                                newlogdir=attackinstance.log_directory)


    def check_for_early_stop(self, attackinstance: BBAttackInstance, current_outer_iteration: int) -> bool:
        """
        Check if we made progress and if not, stop...
        :return: true if early stop, false if we can continue
        """
        if self.early_stop is not None and current_outer_iteration > self.early_stop:
            assert self.early_stop > 1 # this value = 1 makes no sense....
            value_to_cmp = np.array(attackinstance.log_chosentransformers.score)[-self.early_stop]
            current_score = np.array(attackinstance.log_chosentransformers.score)[-1]

            # get last x scores and check if improvement, if not, break
            if self.attack_mode == AttackMode.DODGING:
                proceed: bool =  current_score < value_to_cmp
            elif self.attack_mode == AttackMode.IMPERSONATION_WITH_EXAMPLE_FILES or \
                    self.attack_mode == AttackMode.IMPERSONATION_WITHOUT_EXAMPLE_FILES:
                proceed: bool = current_score > value_to_cmp
            else:
                raise Exception("Unknown attack mode here in early stop")

            if not proceed:
                attackinstance.logger.logger.info("\n Early Stop: {} vs. {} at {} (from {} to {})\n".
                                                  format(value_to_cmp, current_score, current_outer_iteration,
                                                         self.sauthor.author, self.tauthor.author))
                return True

        return False
