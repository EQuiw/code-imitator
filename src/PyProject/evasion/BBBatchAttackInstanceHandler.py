import os
import subprocess
import time
import typing
from distutils.util import strtobool

import Configuration as Config
import evasion.utils_attack
import evasion.utils_attack_workflow
from evasion.BBAttackInstance import BBAttackInstance
from evasion.Transformers.TransformerBase import TransformerBase
from featureextractionV2.ClangTypes.StyloClangFeaturesGenerator import StyloClangFeaturesGenerator
from featureextractionV2.ClangTypes.StyloLexemFeaturesGenerator import StyloLexemFeatureGenerator
from featureextractionV2.StyloFeatures import StyloFeatures


class BBBatchAttackInstanceHandler:
    """
    This class creates a bash script to call various transformers in parallel directly without any python overhead.
    Unfortunately, this class might not be so readable. In future work, we should be able to call transformers
    directly from python.
    """

    def __init__(self, noofcores: int, attackdirauth: str, inputlist: typing.List[typing.Tuple[BBAttackInstance, int,
                                            TransformerBase, int, list]]):
        """
        :param noofcores:
        :param attackdirauth:
        :param inputlist: Input will be: tempattackinstance, nextransformerindex, currenttransformerobj, i*9+nextransformerindex*7, queue
        """
        self.noofcores: int = noofcores
        self.attackdirauth: str = attackdirauth
        self.inputlist: typing.List[typing.Tuple[BBAttackInstance, int,
                                            TransformerBase, int, list]] = inputlist
        self.outputlist: list = [None]*len(inputlist)

        # to avoid that we call multiple times getsubprocesscall,
        # the transformers keep a state, thus this may lead to unwanted behaviour.
        self.simplified_calls: list = [None] * len(inputlist)
        self.unique_transformer_ids: list = [None] * len(inputlist)


        # find out what features need to be extracted
        self.doarff = self.dojoern = self.dolexems = False

        train_obj: StyloFeatures = self.inputlist[0][0].bbattackhandler.learnsetup.data_final_train
        while train_obj is not None:
            # self.doarff # TODO
            # if not, use old value so we basically implement OR operator here for booleans
            self.dojoern = True if StyloClangFeaturesGenerator.check_unique_keys_for_trainobject_comparison(
                trainobj=train_obj) else self.dojoern
            self.dolexems = True if StyloLexemFeatureGenerator.check_unique_keys_for_trainobject_comparison(
                trainobj=train_obj) else self.dolexems
            train_obj = train_obj.codestyloreference


    def call_gnu_parallel(self, timeout, shfile, ind_timeout):
        gnu_parallel_cmd = ["find", self.attackdirauth, "-type", "f", "|", "grep", shfile, "|", "parallel", "-j",
                            str(self.noofcores), "--timeout", str(ind_timeout), "'bash", "{}'"]
        with open(os.path.join(self.attackdirauth, "execute_all.sh"), "w") as f:
            f.write(" ".join(gnu_parallel_cmd))

        p = subprocess.run(["bash", os.path.join(self.attackdirauth, "execute_all.sh")],
                           stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False, timeout=timeout)
        output, err = p.stdout, p.stderr
        if err != b'':
            # raise Exception("Execute gnu parallel exception:" + str(err))
            # we should handle errors in subsequent anaylsis
            pass

        if os.path.exists(os.path.join(self.attackdirauth, "execute_all.sh")):
            os.remove(os.path.join(self.attackdirauth, "execute_all.sh"))


    def batch_do_transformations(self):

        time1 = time.time()
        self.transform_format_preprocess() # done via gnu parallel
        nextround: list = self.transform_output_anaylsis() # done in python
        time2 = time.time()
        self.compile_hash(nextround) # done via gnu parallel, the prediction in python...
        finalround: list = self.compile_hash_analysis(nextround)
        time3 = time.time()
        self.model_prediction(finalround)
        time4 = time.time()
        # print("Transform:{}s, Execute:{}s, Prediction:{}s".format(time2-time1, time3-time2, time4-time3))
        return self.outputlist


    def transform_format_preprocess(self):

        ix: int = -1
        for inputparams in self.inputlist:
            ix += 1
            curbbattinst: BBAttackInstance = inputparams[0]
            prefix: str = str(inputparams[1])

            source_file_copy = curbbattinst.source_file + ".original"
            copy_cmd = ["cp", curbbattinst.source_file, source_file_copy,"\n\n"]

            # A. + B. Transformation Call + clang-format
            source_file_modified = os.path.splitext(curbbattinst.source_file)[0] + "_raw.cpp"

            cmdd_transform, simplified_cmdd_transform = inputparams[2].getsubprocesscall(
                                                                    source_file=curbbattinst.source_file,
                                                                    seed=inputparams[3])
            self.simplified_calls[ix] = simplified_cmdd_transform
            self.unique_transformer_ids[ix] = inputparams[2].uniqueid

            error_file = os.path.join(curbbattinst.source_file + ".stderr")
            clangformat_cmd, source_file_format = evasion.utils_attack_workflow.get_clang_format_call(
                source_file=source_file_modified)

            # C. Check if transformation has changed IO behaviour
            # In contrast to BBAttackInstance, we save ifostream into source-file directly, not format-file!
            testfileout_test = os.path.join(os.path.dirname(source_file_format), "A-small-practice_transformation.out")
            ifostream_cmd = evasion.utils_attack_workflow.get_ifofstreampreprocesser_call(source_file=source_file_format,
                                                                          inputstreampath=curbbattinst.testfilein,
                                                                          outputstreampath=testfileout_test,
                                                                          ifopreppath=Config.ifostreampreppath,
                                                                          flags=Config.flag_list)

            error_file_ifo = os.path.join(curbbattinst.source_file + ".ifo.stderr")

            # Log files
            savesrc_1 = self.__save_source_file(src_file=curbbattinst.source_file, prefix=prefix,
                                    ending="before", bbatt=curbbattinst)
            savesrc_2 = self.__save_source_file(src_file=source_file_modified, prefix=prefix,
                                    ending="after_transf", bbatt=curbbattinst)
            savesrc_3 = self.__save_source_file(src_file=curbbattinst.source_file, prefix=prefix,
                                    ending="final", bbatt=curbbattinst)


            with open(os.path.join(curbbattinst.attackdirauth, "execute.sh"), "w") as f:
                cmdd_transform.extend(["2>", error_file, "1>", source_file_modified,"\n\n"])
                clangformat_cmd.extend(["2>>", error_file, "1>", source_file_format,"\n\n"])
                ifostream_cmd.extend(["2>>", error_file_ifo, "1>", curbbattinst.source_file,"\n\n"])
                f.write(" ".join(copy_cmd))
                f.write(savesrc_1)
                f.write(" ".join(cmdd_transform))
                f.write(savesrc_2)
                f.write(" ".join(clangformat_cmd))
                f.write(" ".join(ifostream_cmd))
                f.write(savesrc_3)
                f.write("rm " + source_file_modified + "\n\n")
                f.write("rm " + source_file_format + "\n\n")

        # now call all scripts in parallel via gnu parallel
        self.call_gnu_parallel(timeout=60*4, shfile="execute.sh", ind_timeout=60*3)


    def transform_output_anaylsis(self):

        qualified_for_next_round = [None] * len(self.inputlist)

        ix: int = -1 # better via enumerate, but typing complains
        for inputparams in self.inputlist:
            ix += 1
            curbbattinst: BBAttackInstance = inputparams[0]
            prefix: str = str(inputparams[1])
            simplified_cmdd_transform = self.simplified_calls[ix]


            try:
                error_file = os.path.join(curbbattinst.source_file + ".stderr")
                error_file_ifo = os.path.join(curbbattinst.source_file + ".ifo.stderr")

                # A. + B. Transformer + clang-format
                self.__check_error_file(error_file)

                # C. ifo,
                if not os.path.isfile(error_file_ifo):
                    raise Exception("Error-ifostream-prep. file does not exist")
                if os.path.getsize(error_file_ifo) == 0:
                    raise Exception("ifofstream no output on stderr")
                ifofstream = None
                with open(error_file_ifo, "r") as f:
                    lines = f.readlines()
                    if len(lines) == 1 and str(lines).find("Replace:") != -1:
                        splits = str(lines[0]).split(":")
                        ifofstream = bool(strtobool(splits[1])), bool(strtobool(splits[2]))
                    else:
                        raise Exception("ifofstream preprocessor failure:" + str(lines))

                qualified_for_next_round[ix] = (True, ifofstream)

            except Exception as e:
                # we only show an exception if we have a real error. If transformation was not possible, we do not show it.
                # But careful. We might have got an exception, continued and then have got Code 123. In this case,
                # we want to show the error as well; we should have multiple error lines == checked by first if-condition:
                if ("Code 123" in str(e) or "Code 124" in str(e)) and str(e).count("\\n") == 1:
                    pass
                elif "Code 900" in str(e) and str(e).count("\\n") == 1:
                    pass
                else:
                    curbbattinst.logger.error("`{}`, T-id:{}, failed with: {}\n".format(simplified_cmdd_transform, prefix, e))

                qualified_for_next_round[ix] = (False, None)

                # we restore the original file...
                source_file_copy = curbbattinst.source_file + ".original"
                assert os.path.isfile(source_file_copy)
                os.rename(source_file_copy, curbbattinst.source_file)


        return qualified_for_next_round



    def compile_hash(self, qualified_for_next_round: typing.List[typing.Tuple]):

        # I. COMPILE + HASH
        for ix, inputparams in enumerate(self.inputlist):
            if qualified_for_next_round[ix][0] is False:
                continue
            assert qualified_for_next_round[ix][1] is not None


            curbbattinst: BBAttackInstance = inputparams[0]

            source_file_final = curbbattinst.source_file
            testfileout_test = os.path.join(os.path.dirname(curbbattinst.source_file), "A-small-practice_transformation.out")

            # D. check if transformation was successful
            error_file = os.path.join(source_file_final + ".compiled" + ".stderr")
            clangcompile_cmd, source_file_format_exe = evasion.utils_attack_workflow.get_compileclang_call(source_file=source_file_final,
                                                                                              compilerflags=Config.compilerflags_list)

            # D.2 Execute cmd...
            execute_cmd = evasion.utils_attack_workflow.get_executecontestfile_call(
                source_file_executable=source_file_format_exe, testfilein=curbbattinst.testfilein,
                testfileout=testfileout_test, ifofstream=qualified_for_next_round[ix][1]
            )

            # D.3 compute hash,
            #hashout_file = os.path.join(source_file_final + ".md5_hash")
            #hash_cmd = ["md5sum", testfileout_test, ">", hashout_file, "\n\n"]


            # F. Compute Features in parallel as well != BBAttackInstance,
            #    which takes around >1 min for all transf. if not parallelly done
            error_file_clang = os.path.join(source_file_final + ".clang" + ".stderr")
            error_file_lexems = os.path.join(source_file_final + ".lexems" + ".stderr")
            if self.dojoern:
                clang_call_cmd, _, clang_tarfile = evasion.utils_attack.get_clang_features_call(
                    src=source_file_final, output_dir=curbbattinst.attackdirauth)
                clang_call_cmd.extend(["2>", error_file_clang, "1>", clang_tarfile, "\n\n"])
            else:
                clang_call_cmd = []
            if self.dolexems:
                lexems_call_cmd, lexems_tarfile = evasion.utils_attack.get_lexems_features_call(
                    src=source_file_final, output_dir=curbbattinst.attackdirauth)
                lexems_call_cmd.extend(["2>", error_file_lexems, "1>", lexems_tarfile, "\n\n"])
            else:
                lexems_call_cmd = []


            with open(os.path.join(curbbattinst.attackdirauth, "execute_compile.sh"), "w") as f:
                clangcompile_cmd.extend(["&>", error_file, "\n\n"])
                execute_cmd.extend(["\n\n"])
                f.write(" ".join(clangcompile_cmd))
                f.write(" ".join(execute_cmd))
                f.write(" ".join(clang_call_cmd))
                f.write(" ".join(lexems_call_cmd))
                #f.write(" ".join(hash_cmd))

        # now call all scripts in parallel via gnu parallel
        self.call_gnu_parallel(timeout=70*6, shfile="execute_compile.sh", ind_timeout=70*4)


    def compile_hash_analysis(self, qualified_for_next_round: typing.List[typing.Tuple]):

        # II. ANALYSIS
        qualified_for_final_round = [False] * len(self.inputlist)
        for ix, inputparams in enumerate(self.inputlist):
            if qualified_for_next_round[ix][0] is False:
                continue

            curbbattinst: BBAttackInstance = inputparams[0]
            prefix = str(inputparams[1])
            simplified_cmdd_transform = self.simplified_calls[ix]

            try:
                source_file_final = curbbattinst.source_file
                error_file = os.path.join(source_file_final + ".compiled" + ".stderr")
                testfileout_test = os.path.join(os.path.dirname(curbbattinst.source_file),
                                                "A-small-practice_transformation.out")

                # Compilation Error?
                self.__check_error_file(error_file)

                # Output behaviour changed?
                transformedhash = evasion.utils_attack_workflow.computeHash(source_file=testfileout_test)
                if transformedhash != curbbattinst.originaloutputhash:
                    raise Exception("Output file has changed!!")

                # Feature problems?
                if self.dojoern:
                    error_file_clang = os.path.join(source_file_final + ".clang" + ".stderr")
                    self.__check_error_file(error_file_clang)

                if self.dolexems:
                    error_file_lexems = os.path.join(source_file_final + ".lexems" + ".stderr")
                    self.__check_error_file(error_file_lexems)


                # E. Prepare next iteration,
                # In contrast to BBAttackInstance, we save the final result in source_file, not in a temp file.
                # and if we have an error, we cp the original file to source_file != in BBAttackInstance, the other way round.
                qualified_for_final_round[ix] = True

            except Exception as e:
                curbbattinst.logger.error(
                    "`{}`, T-id:{}, failed with: {}\n".format(simplified_cmdd_transform, prefix, e))
                # we restore the original file...
                source_file_copy = curbbattinst.source_file + ".original"
                os.rename(source_file_copy, curbbattinst.source_file)



        return qualified_for_final_round


    def __check_error_file(self, err_file: str):
        if not os.path.isfile(err_file):
            raise Exception("Error file does not exist")

        if os.path.getsize(err_file) > 0:
            with open(err_file, "r") as f:
                lines = f.readlines()
            raise Exception(str(lines))


    def model_prediction(self, qualified_for_final_round: typing.List[bool]):

        for ix, inputparams in enumerate(self.inputlist):
            ix: int = ix

            curbbattinst: BBAttackInstance = inputparams[0]
            source_file_rewritten = curbbattinst.source_file
            transf_call = self.simplified_calls[ix]
            transf_uid = self.unique_transformer_ids[ix]

            if qualified_for_final_round[ix] is True:
                # tranformation + format + compile + output was successfull, get model prediction now
                curbbattinst.get_model_prediction(source_file=source_file_rewritten,
                                                  target_class=curbbattinst.targetauthor.true_class,
                                                  verbose=0, already_extracted=True)

                curbbattinst.log_chosentransformers = curbbattinst.log_chosentransformers.append(
                    {'transformer_id': transf_uid, 'transformer_call': transf_call, 'success': True,
                     'score': curbbattinst.scoreprednew, 'class': curbbattinst.classprednew}, ignore_index=True)

                self.outputlist[ix] = (inputparams[1], inputparams[2], transf_call, True, curbbattinst.scoreprednew, curbbattinst.classprednew)

            else:
                self.outputlist[ix] = (inputparams[1], inputparams[2], transf_call, False, None, None)



    def __save_source_file(self, src_file: str, prefix: str, ending: str, bbatt: BBAttackInstance) -> str:

        if Config.savemorelogfiles:
            b = bbatt.get_source_log_file_target(src_file=src_file, prefix=prefix, ending=ending)
            return " ".join(["cp", src_file, b, "\n"])

        else:
            return "\n"



