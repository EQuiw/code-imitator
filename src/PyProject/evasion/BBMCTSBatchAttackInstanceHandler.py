import os
import subprocess
import typing

import numpy as np

import Configuration as Config
import evasion.utils_attack
import evasion.utils_attack_workflow
from evasion.BBAttackInstance import BBAttackInstance
from evasion.BlackBox.AMCTS.State import State
from evasion.BlackBox.AMCTS.StateSequence import StateSequence
from evasion.Transformers.TransformerBase import TransformerBase
from featureextractionV2.ClangTypes.StyloClangFeaturesGenerator import StyloClangFeaturesGenerator
from featureextractionV2.ClangTypes.StyloLexemFeaturesGenerator import StyloLexemFeatureGenerator
from featureextractionV2.StyloFeatures import StyloFeatures


class BBMCTSBatchAttackInstanceHandler:
    """
    This class creates a bash script to call various transformers in parallel directly without any python overhead.
    Unfortunately, this class might not be so readable. In future work, we should be able to call transformers
    directly from python.

    Some Notes:
    - Note that we do not restore the original source file in each attack instance, since we work with it
    on the respective sequences... TODO
    """

    def __init__(self, noofcores: int, attackdirauth: str, inputlist: typing.List[BBAttackInstance], seed, path_length,
                 check_err_files_transformations, repeat_addtemplate_transformers: typing.Optional[float]):
        """
        :param noofcores:
        :param attackdirauth:
        :param inputlist: Input will be: tempattackinstance, seed
        :param seed: global seed
        :param path_length: length of each generated sequence
        :param check_err_files_transformations: true if we will check the stderr files of transformations for
        status codes and more errors, set false if you want to speed up the process as we do not parse any error files
        :param repeat_addtemplate_transformers: At each x-th iteration, select an AddTemplate Transformer. Ignored if None.
        """
        self.noofcores: int = noofcores
        self.attackdirauth: str = attackdirauth
        self.inputlist: typing.List[BBAttackInstance] = inputlist
        self.seed = seed
        self.path_length = path_length
        self.check_err_files_transformations = check_err_files_transformations
        self.repeat_addtemplate_transformers = repeat_addtemplate_transformers
        # self.outputlist: list = [None]*len(inputlist)

        # to avoid that we call multiple times getsubprocesscall,
        # as the transformers keep a state, which could lead to unwanted behaviour otherwise.
        self.mcts_statesequences: typing.List[StateSequence] = [None] * len(inputlist)


        # find out what features need to be extracted
        self.doarff = self.dojoern = self.dolexems = False

        train_obj: StyloFeatures = self.inputlist[0].bbattackhandler.learnsetup.data_final_train
        while train_obj is not None:
            # self.doarff
            self.dojoern = True if StyloClangFeaturesGenerator.check_unique_keys_for_trainobject_comparison(
                trainobj=train_obj) else self.dojoern
            self.dolexems = True if StyloLexemFeatureGenerator.check_unique_keys_for_trainobject_comparison(
                trainobj=train_obj) else self.dolexems

            train_obj = train_obj.codestyloreference


    def batch_do_transformations(self):

        # time1 = time.time()
        self.transform_format_preprocess() # done via gnu parallel
        # time2 = time.time()
        # print("Transform:{}s for {} instances ({}s/t)".format(time2 - time1, len(self.inputlist),
        #                                               (time2-time1)/len(self.inputlist)))

        self.transform_output_anaylsis()  # done in python



    def batch_execute_extractfeatures(self):

        # time1 = time.time()
        self.execute_extractfeatures()  # done via gnu parallel
        # time2 = time.time()
        # noinst = len([1 for x in self.mcts_statesequences if x.exctract_and_do_hash_analysis is True])
        # print("Execute:{}s for {} instances ({}s/t)".format(time2 - time1, noinst, None if noinst == 0 else (time2-time1)/noinst))

        self.hash_analysis()
        self.model_prediction()
        # time3 = time.time()
        # print("Execute:{}s; Extract:{}s".format(time2 - time1, time3 - time2))


    def call_gnu_parallel(self, timeout, shfile, ind_timeout):
        gnu_parallel_cmd = ["find", self.attackdirauth, "-type", "f", "|", "grep", shfile, "|", "parallel", "-j",
                            str(self.noofcores), "--timeout", str(ind_timeout), "'bash", "{}'"]
        with open(os.path.join(self.attackdirauth, "execute_all.sh"), "w") as f:
            f.write(" ".join(gnu_parallel_cmd))

        try:
            p = subprocess.run(["bash", os.path.join(self.attackdirauth, "execute_all.sh")],
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False, timeout=timeout)
            output, err = p.stdout, p.stderr
            if err != b'':
                # raise Exception("Execute gnu parallel exception:" + str(err))
                self.inputlist[0].logger.error("Call GNU PARALLEL ERROR:\n\n" + str(err))
                # we should handle errors in subsequent anaylsis
                # pass

        finally:
            if os.path.exists(os.path.join(self.attackdirauth, "execute_all.sh")):
                os.remove(os.path.join(self.attackdirauth, "execute_all.sh"))




    def transform_format_preprocess(self):

        for ix, curbbattinst in enumerate(self.inputlist):

            # set up files and file names
            source_file_copy = curbbattinst.source_file + ".original"
            copy_original_file_cmd = ["cp", curbbattinst.source_file, source_file_copy, "\n\n"]
            source_file_of_interest: str = curbbattinst.source_file
            source_file_of_interest_basename: str = os.path.splitext(source_file_of_interest)[0]

            error_file = os.path.join(source_file_of_interest_basename + ".stderr")
            self.mcts_statesequences[ix] = StateSequence()  # save sequence for repeating it

            for p in range(0, self.path_length):

                # A. + B. Transformation Call + clang-format
                source_file_modified = source_file_of_interest_basename + "_after_t.cpp"

                # choose transformer randomly
                np.random.seed(self.seed + ix * 11 + p)
                transfrange = curbbattinst.transformerhandler.update_check_number_available_transformers()
                add_template_indices = np.array(curbbattinst.transformerhandler.get_addtemplate_transformer_indices())

                # if repeat_addtemplate_transformers_ratio is set, select at each x-th iteration an AddTemplate Transformer.
                # In this way, we can add some more template transformers if we want to or need to...
                if self.repeat_addtemplate_transformers is not None and add_template_indices.shape[0] > 0\
                        and p==0 and ix % self.repeat_addtemplate_transformers == 0:
                    randchoice = np.random.choice(add_template_indices, 1)[0]
                else:
                    randchoice = np.random.randint(0, transfrange)

                # get transformer
                nextTransformer: TransformerBase = curbbattinst.transformerhandler.get_specified_transformation_per_index(
                    randchoice)
                cmdd_transform, _ = nextTransformer.getsubprocesscall(
                    source_file=source_file_of_interest,
                    seed=self.seed + ix * 9 + p)

                # save the call in our status list, so that we can easily retrieve the sequence information later...
                curstate = State(transformer=nextTransformer)
                self.mcts_statesequences[ix].states.append(curstate)


                # Clang-Format:
                clangformat_cmd, source_file_format = evasion.utils_attack_workflow.get_clang_format_call(
                    source_file=source_file_modified)

                # C. We skip ifostream preprocessor, since we execute file at the end of whole sequence.

                # D. check if transformation was successfull, by compiling here only
                clangcompile_cmd, source_file_format_exe = evasion.utils_attack_workflow.get_compileclang_call(
                    source_file=source_file_format,
                    compilerflags=Config.compilerflags_list)

                # if error, exit command
                error_check_transformer = "".join(["if [ -s ", error_file, " ]\n then \n exit 1 \n fi \n\n"])
                savesrc_1 = self.__save_source_file(src_file=source_file_of_interest, prefix=str(p),
                                        ending="", bbatt=curbbattinst)
                savesrc_2 = self.__save_source_file(src_file=source_file_modified, prefix=str(p),
                                        ending="", bbatt=curbbattinst)

                with open(os.path.join(curbbattinst.attackdirauth, "execute.sh"), "w" if p==0 else "a") as f:
                    cmdd_transform.extend(["2>", error_file, "1>", source_file_modified,"\n\n"])
                    clangformat_cmd.extend(["2>>", error_file, "1>", source_file_format,"\n\n"])
                    clangcompile_cmd.extend(["2>>", error_file, "\n\n"])

                    f.write("## Round:" + str(p) + "\n\n")
                    if p==0:
                        f.write(" ".join(copy_original_file_cmd))
                    f.write(savesrc_1)
                    f.write(" ".join(cmdd_transform))
                    f.write(savesrc_2)
                    f.write(error_check_transformer)

                    f.write(" ".join(clangformat_cmd))

                    f.write(" ".join(clangcompile_cmd))
                    f.write(error_check_transformer)

                    f.write("rm " + source_file_modified + "\n\n")
                    f.write(" ".join(["mv", source_file_format, source_file_of_interest]) + "\n")
                    if p > 0:
                        f.write("rm " + os.path.join(source_file_of_interest_basename + "." + str(p-1)) + "_STATUS" + "\n")  # TODO
                    f.write("touch " + os.path.join(source_file_of_interest_basename + "." + str(p)) + "_STATUS" + "\n")  # TODO

                    #f.write("rm " + source_file_format + "\n\n")


        # Now call all scripts in parallel via gnu parallel
        #   Set the global timeout w.r.t to number of sequences, but at least 60s.
        global_timeout = max(60, round(len(self.inputlist)*30))
        self.call_gnu_parallel(timeout=global_timeout, shfile="execute.sh", ind_timeout=30)


    def transform_output_anaylsis(self):
        """
        Analyze all sequences. We check where a sequence stopped by looking at the Status Files.
        """

        for ix, curbbattinst in enumerate(self.inputlist):
            # set up files and file names
            source_file_of_interest: str = curbbattinst.source_file
            source_file_of_interest_basename: str = os.path.splitext(source_file_of_interest)[0]

            # look at Status Files
            pardir = os.path.dirname(source_file_of_interest)
            statusfiles = [f for f in os.listdir(pardir) if os.path.isfile(os.path.join(pardir, f)) and f.endswith("STATUS")]

            if len(statusfiles) > 1:
                raise Exception("Multiple Status Files during BBMCTS-Batch")

            if len(statusfiles) == 1:
                statusfile = statusfiles[0].split(".")[-1]
                status = int(statusfile.split('_')[0])
                self.mcts_statesequences[ix].status = status
                check_for_errors_index = min(status + 1, self.path_length-1) # the next transformer, but if all were possible, the last one
            else:
                self.mcts_statesequences[ix].status = -1
                check_for_errors_index = 0

            # log if we had unexpected errors, if no state, 1st transformer caused problems, otherwise use status ...
            error_file_transf = os.path.join(source_file_of_interest_basename + ".stderr")
            self.__check_error_file_transformations(err_file=error_file_transf, attinstance=curbbattinst,
                                                    iteration=ix, check_index=check_for_errors_index)

            # trim sequence to only valid transformers
            for i in range(len(self.mcts_statesequences[ix].states)-1, self.mcts_statesequences[ix].status, -1):
                del self.mcts_statesequences[ix].states[i]
            assert len(self.mcts_statesequences[ix].states) == self.mcts_statesequences[ix].status+1




    def execute_extractfeatures(self):

        for ix, curbbattinst in enumerate(self.inputlist):
            if self.mcts_statesequences[ix].exctract_and_do_hash_analysis is False:
                continue

            # set up files and file names
            source_file_of_interest: str = curbbattinst.source_file
            source_file_of_interest_basename: str = os.path.splitext(source_file_of_interest)[0]
            error_file = os.path.join(source_file_of_interest_basename + ".compile.stderr")


            # If not None, we know that we should evaluate this sequence and backpropagate the score through tree
            # E. Check if transformation has changed IO behaviour
            testfileout_test = os.path.join(os.path.dirname(source_file_of_interest),
                                            "A-small-practice_transformation.out")
            ifostream_cmd = evasion.utils_attack_workflow.get_ifofstreampreprocesser_call(
                source_file=source_file_of_interest,
                inputstreampath=curbbattinst.testfilein,
                outputstreampath=testfileout_test,
                ifopreppath=Config.ifostreampreppath,
                flags=Config.flag_list)

            error_file_ifo = os.path.join(source_file_of_interest + ".ifo.stderr")
            source_file_ifo = os.path.join(source_file_of_interest_basename + ".ifo.cpp")
            savesrc_3 = self.__save_source_file(src_file=source_file_ifo, prefix="",
                                                ending="", bbatt=curbbattinst)
            # we need to check if ifo file has 1 row only and this row starts with Replace:
            countlines = "NUMOFLINES=$(wc -l < " + error_file_ifo + ")\n"
            error_ifo_check_transformer = "if [ $NUMOFLINES -ne 1 ]\n then \n exit 1 \n fi \n\n"
            error_ifo_check_for_content = "".join(["if grep -q \"Replace:\" ", error_file_ifo,
                                                   "; then : ; else exit 1 \n fi \n\n"])


            # F. Compile again with possibly adapted paths from ifostream preprocessor
            clangcompile_cmd, source_file_format_exe = evasion.utils_attack_workflow.get_compileclang_call(
                source_file=source_file_ifo,
                compilerflags=Config.compilerflags_list)
            error_check_transformer = "".join(["if [ -s ", error_file, " ]\n then \n exit 1 \n fi \n\n"])

            # G. Execute command
            # We handle ifostream's output parsing in bash, so that we do not have to switch to python.
            execute_cmd = evasion.utils_attack_workflow.get_executecontestfile_call(
                source_file_executable=source_file_format_exe, testfilein=curbbattinst.testfilein,
                testfileout=testfileout_test, ifofstream=(True, True)
            )

            # if a developer writes to stderr during executing, we need to ignore this by piping it into a file that we do not use later...
            execute_stderr = os.path.join(source_file_of_interest_basename + ".execute.stderr")

            # build execute command now...
            execute_cmd = "EXECUTE=\"" + "".join(execute_cmd) + "\"\n\n"

            choose_input_stream = "\n".join(["while IFS=':' read -r var1 var2 var3", "do", "USE_INPUT=${var2}", "USE_OUTPUT=${var3}",
                                             "done < " + error_file_ifo + "\n\n"])

            input_stream_concat = "".join(["if [ ${USE_INPUT} -eq \"0\" ]\n then \n EXECUTE=\"$EXECUTE < ", curbbattinst.testfilein, " \" \n fi \n\n"])
            output_stream_concat = "".join(["if [ ${USE_OUTPUT} -eq \"0\" ]\n then \n EXECUTE=\"$EXECUTE 1> ", testfileout_test, " \" \n fi \n\n"])
            output_stream_concat2 = "".join(["EXECUTE=\"$EXECUTE 2> ", execute_stderr, " \" \n\n"])

            mv_cmd = " ".join(["mv", source_file_ifo, source_file_of_interest])

            # H. Features: Compute Features in parallel as well != BBAttackInstance,
            #    which takes longer for all transf. if not parallelly done
            error_file_clang = os.path.join(source_file_of_interest_basename + ".clang" + ".stderr")
            error_file_lexems = os.path.join(source_file_of_interest_basename + ".lexems" + ".stderr")
            if self.dojoern:
                clang_call_cmd, _, clang_tarfile = evasion.utils_attack.get_clang_features_call(
                    src=source_file_of_interest, output_dir=curbbattinst.attackdirauth)
                clang_call_cmd.extend(["2>", error_file_clang, "1>", clang_tarfile, "\n\n"])
            else:
                clang_call_cmd = []
            if self.dolexems:
                lexems_call_cmd, lexems_tarfile = evasion.utils_attack.get_lexems_features_call(
                    src=source_file_of_interest, output_dir=curbbattinst.attackdirauth)
                lexems_call_cmd.extend(["2>", error_file_lexems, "1>", lexems_tarfile, "\n\n"])
            else:
                lexems_call_cmd = []



            with open(os.path.join(curbbattinst.attackdirauth, "execute_extractfeats.sh"), "a") as f:
                f.write("# Ifostream Handling \n")
                ifostream_cmd.extend(["2>>", error_file_ifo, "1>", source_file_ifo, "\n\n"])
                f.write(" ".join(ifostream_cmd))

                f.write(countlines)
                f.write(error_ifo_check_transformer)
                f.write(error_ifo_check_for_content)

                f.write("# **Compile and Execute** \n\n")
                clangcompile_cmd.extend(["2>>", error_file, "\n\n"])
                f.write(" ".join(clangcompile_cmd))
                f.write(error_check_transformer)

                f.write(choose_input_stream)
                f.write(execute_cmd)
                f.write(input_stream_concat)
                f.write(output_stream_concat)
                f.write(output_stream_concat2)
                f.write("eval ${EXECUTE}\n\n")
                f.write(mv_cmd + "\n\n")

                f.write("# ** Features **\n\n")
                f.write(" ".join(clang_call_cmd))
                f.write(" ".join(lexems_call_cmd))

        # Now call all scripts in parallel via gnu parallel
        #   Set the global timeout w.r.t to number of sequences, but at least 60s.
        noinst = len([1 for x in self.mcts_statesequences if x.exctract_and_do_hash_analysis is True])
        global_timeout = max(60, round(noinst*140))
        self.call_gnu_parallel(timeout=global_timeout, shfile="execute_extractfeats.sh", ind_timeout=150)


    def hash_analysis(self):

        for ix, curbbattinst in enumerate(self.inputlist):

            source_file_of_interest: str = curbbattinst.source_file
            source_file_of_interest_basename: str = os.path.splitext(source_file_of_interest)[0]

            if self.mcts_statesequences[ix].exctract_and_do_hash_analysis is True:
                # set up further files and file names
                error_file = os.path.join(source_file_of_interest_basename + ".compile.stderr")
                testfileout_test = os.path.join(os.path.dirname(source_file_of_interest),
                                        "A-small-practice_transformation.out")

                try:
                    # Compilation Error?
                    self.__check_error_file(error_file)

                    # Output behaviour changed?
                    transformedhash = evasion.utils_attack_workflow.computeHash(source_file=testfileout_test)
                    if transformedhash != curbbattinst.originaloutputhash:
                        raise Exception("Output file has changed!!")

                    # Feature problems?
                    if self.dojoern:
                        error_file_clang = os.path.join(source_file_of_interest_basename + ".clang" + ".stderr")
                        self.__check_error_file(error_file_clang)

                    if self.dolexems:
                        error_file_lexems = os.path.join(source_file_of_interest_basename + ".lexems" + ".stderr")
                        self.__check_error_file(error_file_lexems)

                    self.mcts_statesequences[ix].usable_sequence = True

                except Exception as e:
                    curbbattinst.logger.error(
                        "{}-th MCTS Sequence failed at the end due to: {}\n".format(str(ix), e))


    def model_prediction(self):

        for ix, curbbattinst in enumerate(self.inputlist):
            if self.mcts_statesequences[ix].usable_sequence is True:

                source_file_rewritten = curbbattinst.source_file
                try:
                    curbbattinst.get_model_prediction(source_file=source_file_rewritten,
                                                      target_class=curbbattinst.targetauthor.true_class,
                                                      verbose=0, already_extracted=True)

                    self.mcts_statesequences[ix].final_score = curbbattinst.scoreprednew

                except Exception as e:
                    curbbattinst.logger.error("Model prediction error for {}, {}".format(
                        curbbattinst.attackdirauth, source_file_rewritten))
                    curbbattinst.logger.error(str(e))
                    self.mcts_statesequences[ix].usable_sequence = False



    def keep_only_positive_unique_sequences(self) -> None:
        """
        Check for sequences that have zero sequence length or occur multiple times.
        If a sequence occurs multiple times (same state ids), then we choose the first by setting
        exctract_and_do_hash_analysis to True and the others are still exctract_and_do_hash_analysis=False.
        """

        already_visited_sequences = set()
        for s1, current_state_sequence in enumerate(self.mcts_statesequences):
            assert current_state_sequence.exctract_and_do_hash_analysis is False

            # Ignore empty sequences
            if current_state_sequence.status != -1:
                seq_key = "_".join([x.state_id for x in current_state_sequence.states])

                if seq_key not in already_visited_sequences:
                    already_visited_sequences.add(seq_key)
                    current_state_sequence.exctract_and_do_hash_analysis = True


    def __check_error_file(self, err_file: str):
        if not os.path.isfile(err_file):
            raise Exception("Error file does not exist")

        if os.path.getsize(err_file) > 0:
            with open(err_file, "r") as f:
                lines = f.readlines()
            raise Exception(str(lines))


    def __check_error_file_transformations(self, err_file: str, attinstance: BBAttackInstance, iteration: int, check_index: int):

        if self.check_err_files_transformations is True:
            if not os.path.isfile(err_file):
                raise Exception("Error-transf file does not exist")

            transf_call: str = self.mcts_statesequences[iteration].states[check_index].simplified_transformer_call

            if os.path.getsize(err_file) > 0:
                with open(err_file, "r") as f:
                    lines = f.readlines()

                if len(lines) == 1 and ("Code 123" in lines[0] or "Code 124" in lines[0]):
                    pass
                elif len(lines) == 1 and "Code 900" in lines[0]:
                    pass
                else:
                    er_msg = str(lines) # only log the first 500 letters for an error message...
                    attinstance.logger.error("{}-th seq. (T:{}) failed with: {}\n".format(iteration, transf_call,
                                                                                  er_msg[:min(500, len(er_msg))]))



    def __save_source_file(self, src_file: str, prefix: str, ending: str, bbatt: BBAttackInstance) -> str:

        if Config.savemorelogfiles:
            b = bbatt.get_source_log_file_target(src_file=src_file, prefix=prefix, ending=ending)
            return " ".join(["cp", src_file, b, "\n"])

        else:
            return "\n"



