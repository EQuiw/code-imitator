# import numpy as np
# from abc import ABC, abstractmethod
# import evasion.utils_attack as ua
# import evasion.utils_attack_workflow as uaw
# import Configuration as Config
import os
import typing
import numpy as np
import sys

from evasion.BBAttackHandler import BBAttackHandler
from UnitTests.TransformerTesting.BBAttackInstanceSecure import BBAttackInstanceSecure
from evasion.BBAttackInstance import BBAttackInstance
from evasion.Author import Author
from evasion.AttackMode import AttackMode
from classification.LearnSetups.LearnSetup import LearnSetup
import evasion.Transformers.TransformerBase

class TransformerAttackTester(BBAttackHandler):

    def __init__(self, attackdirauth: str,
                 sourceauthor: Author,
                 targetauthor: Author,
                 learnsetup: LearnSetup,
                 transformer_id: str,
                 max_iterations: int,
                 attack_mode: AttackMode,
                 initialseed: int = 42,
                 secure_mode: bool = True
                 ) -> None:

        # call parent's init method
        super(TransformerAttackTester, self).__init__(
            attackdirauth=attackdirauth, sourceauthor=sourceauthor, targetauthor=targetauthor,
            learnsetup=learnsetup, max_iterations=max_iterations,
            attack_mode=attack_mode, initialseed=initialseed,
        )
        self.transformer_id: str = transformer_id
        self.secure_mode = secure_mode


    # @Overwrite
    def run_attack(self) -> typing.Tuple[str, bool]:

        try:
            # a. Init Attack Instance
            if self.secure_mode is True:
                attackinstance = BBAttackInstanceSecure(sourceauthor = self.sauthor, attackdirauth=self.attackdirauth,
                                              targetauthor = self.tauthor, bbattackhandler=self)
            else:
                attackinstance = BBAttackInstance(sourceauthor = self.sauthor, attackdirauth=self.attackdirauth,
                                              targetauthor = self.tauthor, bbattackhandler=self)

            queue = []

            for i in range(0, self.max_iterations):
                seed = i * 9 + 7

                # create log dir for current iteration
                logdir_iter = os.path.join(attackinstance.log_directory, "test" + str(seed))
                os.makedirs(logdir_iter)

                newtemppath = os.path.join(self.attackdirauth, "temp" + str(seed), self.sauthor.author)
                tempattackinstance = attackinstance.clone(attackdirauth = newtemppath, newlogdir=logdir_iter)

                # ** Choose transformer **
                currenttransformerobj: evasion.Transformers.TransformerBase = tempattackinstance.transformerhandler.\
                        get_specified_transformation_per_uniqueid(self.transformer_id)

                # ** Do transformation **
                # -> Check if transformer is callable, may happen with AddTemplateTransformers,
                #       e.g. if they do not have any target includes
                if currenttransformerobj.check_valid() is True:
                    lasttransfcall, successtransf, scoreprednew, classprednew, remainingtransformers = \
                        self.__helper_for_attackinstance(tempattackinstance=tempattackinstance,
                                                         prefix=str(seed),
                                                         currenttransformer=currenttransformerobj,
                                                         seed=seed)
                else:
                    # if no valid transformation is there anymore, it is like a "Code 124: Empty Set"...
                    lasttransfcall, successtransf, scoreprednew, classprednew, remainingtransformers = \
                        currenttransformerobj.transformer, False, None, None, 0

                # ** Eval **
                queue.append([str(seed), currenttransformerobj, lasttransfcall,
                              successtransf, scoreprednew, classprednew, remainingtransformers])
                if not successtransf:
                    tempattackinstance.cleandir(currentbaselevel=attackinstance.attackdirauth)
                    break
                else:
                    attackinstance = tempattackinstance.clone(attackdirauth=attackinstance.attackdirauth,
                                                              newlogdir=attackinstance.log_directory)
                    tempattackinstance.cleandir(currentbaselevel=attackinstance.attackdirauth)

            # print how many successfull transformations were possible at all
            succ = np.sum(np.array([successtransf for _, _, _, successtransf, _, _, _ in queue]))
            remainingtransformers = queue[-1][6]
            nooftrials = len(queue) - 1 if remainingtransformers == 0 else len(queue)

            authstr = self.sauthor.author if self.sauthor.author == self.tauthor.author \
                else (self.tauthor.author + "/" + self.sauthor.author)
            output: str = "{} had: {} / {}; remaining: {}".format(authstr, succ, nooftrials, remainingtransformers)
            print(output) if remainingtransformers == 0 else print(output, file=sys.stderr)

            return output, remainingtransformers == 0


        except Exception as e:
            err_msg: str = "***Unexpected ERROR *** {} -> {} with {}".format(
                self.sauthor.author, self.tauthor.author, str(e))
            printable_err_msg = "***Unexpected ERROR *** {} -> {} with {}".format(
                self.sauthor.author, self.tauthor.author, str(e)[0:(min(30,len(str(e))))])
            print(printable_err_msg, file=sys.stderr)
            return err_msg, False

        finally:
            try:
                attackinstance.logger.close_logger()
            except Exception:
                pass


    def __helper_for_attackinstance(self, tempattackinstance: BBAttackInstance,
                                    prefix: str,
                                    currenttransformer: evasion.Transformers.TransformerBase,
                                    seed: int):

        loadnewfeatures, error_code, transf_call = tempattackinstance.do_transformation_only(
            prefix=prefix,
            currenttransformer=currenttransformer,
            seed=seed
        )
        if error_code is not None:
            tempattackinstance.logger.logger.debug("`{}`, T-id:{}, failed with: {}\n".format(transf_call, prefix, error_code))

        remainingtransformations = 0 if error_code == "124" else None

        return transf_call, loadnewfeatures, None, None, remainingtransformations



