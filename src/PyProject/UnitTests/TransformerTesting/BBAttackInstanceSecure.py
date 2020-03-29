import evasion.utils_attack_workflow as uaw
import Configuration as Config
import os
import shutil
import typing
from evasion.BBAttackHandler import BBAttackHandler
from evasion.Transformers import TransformerBase
from evasion.Author import Author

from evasion.BBAttackInstance import BBAttackInstance

class BBAttackInstanceSecure(BBAttackInstance):
    """
        A lightweight version of AttackInstance with reduced functionality.

        Single attack instance -- more secure since we do not execute the compiled file.
    """

    def __init__(self, sourceauthor: Author, targetauthor: Author,
                 attackdirauth: str, bbattackhandler: 'BBAttackHandler') -> None:
        """
        Inits a single attack instance. If doding attack, use the same Author object for sourceauthor and targetauthor.
        :param sourceauthor: the source author.
        :param targetauthor: the target author.
        :param attackdirauth: the path where attack happens
        :param bbattackhandler: a reference to attack handler -- the object that uses this attack instance.
        """

        super(BBAttackInstanceSecure, self).__init__(
            attackdirauth=attackdirauth, sourceauthor=sourceauthor, targetauthor=targetauthor,
            bbattackhandler=bbattackhandler)


    # @overwrite
    def set_up(self) -> str:
        """
        Set up the directory for the attack.
        """

        ## I. Set-Up for attack ##
        # A. Set up directory where attack takes place. We copy the necessary files to this location.
        source_file_forattack, self.log_directory = uaw.create_dir_structure_forattack(datasetpath=Config.datasetpath,
                                                                        attackdirauth=self.attackdirauth,
                                                                        author=self.sourceauthor.author,
                                                                        authiid=self.sourceauthor.authiid)

        # Now copy the source file, so that we have an original file and the file that we will modify during attack
        source_file_forattack_splitext = os.path.splitext(source_file_forattack)
        self.original_source_file = source_file_forattack_splitext[0] + "_original" + source_file_forattack_splitext[1]
        shutil.copyfile(source_file_forattack, self.original_source_file)

        #print(self.original_source_file, source_file_forattack, self.log_directory)

        # copy the target source file -- just for easier comparison
        if self.sourceauthor.author != self.targetauthor.author:
            self.target_source_file = uaw.copy_sourcefile(datasetpath=Config.datasetpath, attackdirauth=self.attackdirauth,
                                                      authiid=self.targetauthor.authiid, author=self.targetauthor.author)

        self.testfilein = None # os.path.join(self.attackdirauth, "A-small-practice.in")
        self.testfileout = None # os.path.join(self.attackdirauth, "A-small-practice.out")

        # B. Copy A-small-practice.in file to current attack directory
        # uaw.copytestfile(testfilesdir=Config.testfilesdir, authiid=self.sourceauthor.authiid, targettestfile=self.testfilein)

        # C. Check if file reads input/ouput via file and not via stdout/stderr, so that we need to adapt paths..
        self.ifofstream = None

        # D. Create the A-small-practice.out file.

        # E. Compute the hash of the output file. We will check that output is not changed by a transformation

        # F. Load features for the first time and get initial prediciton
        self.get_model_prediction(source_file=source_file_forattack, target_class=self.targetauthor.true_class, verbose=0)


        return source_file_forattack


    # @overwrite
    def get_score_source(self) -> float:
        pass

    # @overwrite
    def get_score_for_class(self, classind: int) -> float:
        pass

    # @overwrite
    def do_transformation_and_predict(self, prefix: str, currenttransformer: TransformerBase, seed: int):
        pass


    # @overwrite
    def do_transformation_only(self, prefix: str, currenttransformer: TransformerBase, seed: int):
        assert self.ifofstream is None

        error_code: typing.Optional[str] = None
        loadnewfeatures: bool = False
        remainingtransformations = None
        transf_call: str = currenttransformer.transformer # fill it later with full cmd

        try:
            self.save_source_file(src_file=self.source_file, prefix=prefix, ending="before_secure")

            # A. do transformation
            source_file_modified = os.path.splitext(self.source_file)[0] + "_raw.cpp"
            transf_call, err = currenttransformer.dotransformercall(source_file=self.source_file,
                                                                    target_file=source_file_modified,
                                                                    seed=seed)
            if err is not None:
                raise Exception(err)
            self.save_source_file(src_file=source_file_modified, prefix=prefix, ending="after_transf_secure")

            # B. clang-format
            source_file_format = uaw.do_clang_format(source_file=source_file_modified)

            # C. Check if transformation has changed IO behaviour

            # D. check if transformation was successfull
            source_file_format_exe: str = uaw.compileclang(source_file=source_file_format, compilerflags=Config.compilerflags_list)

            # E. Prepare next iteration
            os.remove(self.source_file)
            os.rename(source_file_format, self.source_file)
            loadnewfeatures = True

        except Exception as e:
            # we only show an exception if we have a real error. If transformation was not possible, we do not show it.
            # But careful. We might have got an exception, continued and then have got Code 123. In this case,
            # we want to show the error as well; we should have multiple error lines == checked by first if-condition:
            if "Code 123" in str(e) and str(e).count("\\n") == 1:
                error_code = "123"
            elif "Code 900" in str(e) and str(e).count("\\n") == 1:
                error_code = "900"
            elif "Code 124" in str(e) and str(e).count("\\n") == 1:
                error_code = "124"
            else:
                self.logger.error("`{}`, T-id:{}, failed with: {}\n".format(transf_call, prefix, e))
                error_code = "000"


            loadnewfeatures = False

            # save full call to debug faster in log directory TODO

        finally:
            # clean dir for next transformation
            if 'source_file_format_exe' in locals() and os.path.exists(source_file_format_exe):
                os.remove(source_file_format_exe)
            if 'source_file_modified' in locals() and os.path.exists(source_file_modified):
                os.remove(source_file_modified)
            if 'source_file_format' in locals() and os.path.exists(source_file_format):
                os.remove(source_file_format)


        return loadnewfeatures, error_code, transf_call

