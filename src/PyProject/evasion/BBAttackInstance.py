import copy
import os
import shutil
import typing

import pandas

import Configuration as Config
import evasion.utils_attack as ua
import evasion.utils_attack_workflow as uaw
from evasion.AttackLogging.Attack_Logging import Logger
from evasion.Author import Author
from evasion.BBAttackHandler import BBAttackHandler
from evasion.Transformers import TransformerBase
from evasion.Transformers.TransformerHandler import TransformerHandler


class BBAttackInstance:
    """
        A single attack instance.
    This class represents a directory where the source file will be saved and modified iteratively.
    The log files will be present in this directory, the input and output files,
    and when we extract the features, all the *.dat files will be saved in this directory.
    In other words, this class represents a particular state in the sequence of code transformations.

    Usually, an attack starts with such an attack instance (then the whole directory will be created under
    attackdirauth). Then, if we do a hill climbing attack/MCTS attack, we run various transformers.
    So we use the clone function to clone this attack instance to a new temporary sub-directory where the sub-directory
    represents a novel attack instance where the transformer was used.
    """

    def __init__(self, sourceauthor: Author, targetauthor: Author,
                 attackdirauth: str, bbattackhandler: 'BBAttackHandler') -> None:
        """
        Inits a single attack instance. If dodging attack, use the same Author object for sourceauthor and targetauthor.
        :param sourceauthor: the source author.
        :param targetauthor: the target author.
        :param attackdirauth: the path where attack happens
        :param bbattackhandler: a reference to attack handler -- the object that uses this attack instance.
        """

        self.bbattackhandler = bbattackhandler # todo refactor this to learnsetup simply!
        self.attackdirauth: str = attackdirauth
        self.sourceauthor = sourceauthor
        self.targetauthor = targetauthor

        # The following attributes will be set up by self.set_up():
        self.target_source_file: str = None
        self.originaloutputhash: str = None
        self.testfilein: str = None
        self.testfileout: str = None
        self.original_source_file: str = None
        self.log_directory: str = None

        self.original_predscore: float = None
        self.scoreprednew: float = None
        self.classprednew: int = None

        self.ifofstream: typing.Tuple[bool, bool] = None

        self.log_chosentransformers: pandas.DataFrame = pandas.DataFrame(columns=["transformer_id", "transformer_call",
                                                                                  "success", "score", "class"])

        # set up all variables
        self.source_file: str = self.set_up()

        # set up logger, we can only do so after set_up since we need to know log_director before
        self.logger = Logger(logfilepath=self.log_directory,
                             logging_id=self.sourceauthor.author + str(self.targetauthor.author))
        self.logger.debug_details("INIT: IfOfStream: {}".format(str(self.ifofstream)))
        self.logger.debug_details("INIT: Pred:{} /({})".format(round(self.scoreprednew, 4), self.classprednew))


        self.transformerhandler: 'TransformerHandler' = TransformerHandler(sourceauthor=sourceauthor,
                                                                           targetauthor=targetauthor,
                                                                           attackdir=self.attackdirauth,
                                                                           attack_mode=self.bbattackhandler.attack_mode,
                                                                           logger=self.logger)





    def clone(self, attackdirauth: str, newlogdir: str) -> 'BBAttackInstance':
        """
        Clones this object / directory to new sub directory.
        Used for running a transformation without impact on the original source file.
        Used during hill climbing, if we try several transformations and choose the best.
        :param attackdirauth: the new attackdir
        :param newlogdir: new log directory path
        :return: returns a new BBAttackInstance
        """

        # create the directory temp+suffix / authorname /
        if not os.path.exists(attackdirauth):
            os.makedirs(attackdirauth)
        csourcefile = os.path.join(attackdirauth, self.sourceauthor.authiid)
        shutil.copyfile(self.source_file, csourcefile)

        newobjinstance: 'BBAttackInstance' = copy.copy(self)
        newobjinstance.log_chosentransformers = copy.deepcopy(self.log_chosentransformers)
        newobjinstance.source_file = csourcefile
        newobjinstance.attackdirauth = attackdirauth

        newobjinstance.transformerhandler: 'TransformerHandler' = copy.deepcopy(self.transformerhandler)
        newobjinstance.transformerhandler.attackdir = attackdirauth
        newobjinstance.log_directory = newlogdir

        return newobjinstance


    def cleandir(self, currentbaselevel: str) -> None:
        """
        Deletes the directory and parent directory of saved source file.
        We should have a structure such as <temporary-dir>/authorname/...
        :param currentbaselevel: the parent of the removed directory. Used to check that we do not delete something
        what we actually need ;)
        """
        cleandirstr = os.path.realpath(os.path.join(self.attackdirauth, os.path.pardir))
        cleandirstrpar = os.path.realpath(os.path.join(cleandirstr, os.path.pardir))
        if os.path.realpath(currentbaselevel) != cleandirstrpar:
            raise Exception("Dangerous Delete Operation")

        if os.path.exists(cleandirstr):
            shutil.rmtree(cleandirstr)


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

        # print(self.original_source_file, source_file_forattack, self.log_directory)

        # copy the target source file -- just for easier comparison
        if self.sourceauthor.author != self.targetauthor.author:
            self.target_source_file = uaw.copy_sourcefile(datasetpath=Config.datasetpath, attackdirauth=self.attackdirauth,
                                                      authiid=self.targetauthor.authiid, author=self.targetauthor.author)

        self.testfilein = os.path.join(self.attackdirauth, "A-small-practice.in")
        self.testfileout = os.path.join(self.attackdirauth, "A-small-practice.out")

        # B. Get correct A-small-practice.in file
        # Check if author needs some special input treatment
        reduced_testfile: bool = uaw.check_if_author_needs_reduced_testfile(authiid=self.sourceauthor.authiid,
                                                                            author=self.sourceauthor.author,
                                                                            call_instructions_csv_path=Config.call_instructions_csv_path)

        # Copy A-small-practice.in file to current attack directory
        uaw.copytestfile(testfilesdir=Config.testfilesdir, authiid=self.sourceauthor.authiid,
                         targettestfile=self.testfilein, reduced=reduced_testfile)

        # C. Check if file reads input/ouput via file and not via stdout/stderr, so that we need to adapt paths..
        self.ifofstream = uaw.ifofstreampreprocesser(source_file=source_file_forattack,
                                inputstreampath=self.testfilein,
                                outputstreampath=self.testfileout, #os.path.basename
                                ifopreppath=Config.ifostreampreppath, flags = Config.flag_list)

        # D. Create the A-small-practice.out file.
        source_file_exe: str = uaw.compileclang(source_file=source_file_forattack, compilerflags=Config.compilerflags_list)
        uaw.executecontestfile(source_file_executable=source_file_exe, testfilein=self.testfilein,
                               testfileout=self.testfileout, ifofstream=self.ifofstream)
        os.remove(source_file_exe)

        # E. Compute the hash of the output file. We will check that output is not changed by a transformation
        self.originaloutputhash = uaw.computeHash(source_file=self.testfileout)


        # F. Load features for the first time and get initial prediciton
        self.get_model_prediction(source_file = source_file_forattack, target_class=self.targetauthor.true_class, verbose = 0)

        # F.2 Check outputs...
        if self.classprednew != self.sourceauthor.true_class:

            # it is possible that source author is already not correctly predicted if we changed the path with ifostream
            self.get_model_prediction(source_file=self.original_source_file, target_class=self.targetauthor.true_class,
                                      verbose=0)
            # If still unequal, it might be something more serious:
            if self.classprednew != self.sourceauthor.true_class:
                raise Exception("Mismatch of true and predicted class before attack, should not be the case, for: {},{}".
                    format(self.sourceauthor.author, self.targetauthor.author))
            else:
                # Otherwise, it is really due to ifostream and we can continue ...
                # print("Mismatch of true class and predicted class due to ifostream,{},{}".format(
                #     self.sourceauthor.author, self.targetauthor.author), file=sys.stderr)
                # reset object attributes to correct initial file that is used for attack... and continue...
                self.get_model_prediction(source_file=source_file_forattack, target_class=self.targetauthor.true_class,
                                          verbose=0)

        self.original_predscore = self.scoreprednew


        # E. Init log of done transformations so far
        self.log_chosentransformers = self.log_chosentransformers.append(
            {'transformer_id': "-", 'transformer_call': "-", 'success': "-",
             'score': self.original_predscore, 'class': self.sourceauthor.true_class}, ignore_index=True)

        return source_file_forattack



    def get_model_prediction(self, source_file: str, target_class: int,
                             verbose: int = 1, already_extracted: bool = False) -> None: # -> typing.Tuple[float, int]:

        # A. Load features TODO, use feature_paths instead of already_extracted...
        self.attack_data_merged = ua.load_new_features_merged(datasetpath=Config.datasetpath,
                                                              attackdirauth=os.path.dirname(source_file),
                                               verbose=False, cppfile=source_file,
                                               train_object=self.bbattackhandler.learnsetup.data_final_train,
                                               already_extracted=already_extracted)

        # B. Evaluate and update score and class of target class
        self.scoreprednew = self.bbattackhandler.learnsetup.predict_proba(
            feature_vec=self.attack_data_merged.getfeaturematrix()[0, :],
            target_class=target_class)
        self.classprednew = self.bbattackhandler.learnsetup.predict(
            feature_vec=self.attack_data_merged.getfeaturematrix()[0, :])

        if verbose >= 1:
            print("\t Pred:{} /({})".format(round(self.scoreprednew, 4), self.classprednew))

        #return self.scoreprednew, self.classprednew


    # def get_score_and_class_target(self) -> typing.Tuple[float, int]:
    #     """
    #     Returns the predicted class label and the respective score for target author = the target class.
    #     """
    #     return self.scoreprednew, self.classprednew

    def get_score_source(self) -> float:
        """
        Returns the score of source author = the true class.
        In the case of dodging attack, consider true and target class are the same.
        """
        return self.get_score_for_class(classind = self.sourceauthor.true_class)


    def get_score_for_class(self, classind: int) -> float:
        """
        Returns the score of given class index..
        """
        scorepredtrue = self.bbattackhandler.learnsetup.predict_proba(
            feature_vec=self.attack_data_merged.getfeaturematrix()[0, :],
            target_class=classind)
        return scorepredtrue



    def do_transformation_and_predict(self, prefix: str, currenttransformer: TransformerBase, seed: int):
        """
        Perform transformation and prediction.
        """

        loadnewfeatures, _, transf_call = self.do_transformation_only(
            prefix=prefix, currenttransformer=currenttransformer, seed=seed)

        if loadnewfeatures:
            self.get_model_prediction(source_file = self.source_file,
                                      target_class = self.targetauthor.true_class, verbose = 0)
            self.log_chosentransformers = self.log_chosentransformers.append(
                {'transformer_id': currenttransformer.uniqueid, 'transformer_call': transf_call, 'success': True,
                 'score': self.scoreprednew, 'class': self.classprednew}, ignore_index=True)

            return transf_call, True, self.scoreprednew, self.classprednew
        else:
            return transf_call, False, None, None


    def do_transformation_only(self, prefix: str, currenttransformer: TransformerBase, seed: int):
        """
        ** The heart of this class **
        Perform a transformation without extracting features = loading model score (= prediction).
        Use method 'do_transformation_and_predict' if you want to obtain the score as well.
        """

        transf_call: str = currenttransformer.transformer # fill it later with full cmd
        loadnewfeatures: bool = False
        error_code: typing.Optional[str] = None

        try:
            self.save_source_file(src_file=self.source_file, prefix=prefix, ending="before")

            # A. do transformation
            source_file_modified = os.path.splitext(self.source_file)[0] + "_raw.cpp"
            transf_call, err = currenttransformer.dotransformercall(source_file=self.source_file,
                                                                    target_file=source_file_modified,
                                                                    seed=seed)
            if err is not None:
                raise Exception(err)
            self.save_source_file(src_file=source_file_modified, prefix=prefix, ending="after_transf")

            # B. clang-format
            source_file_format = uaw.do_clang_format(source_file=source_file_modified)

            # C. Check if transformation has changed IO behaviour
            testfileout_test = os.path.join(os.path.dirname(source_file_format), "A-small-practice_transformation.out")
            self.ifofstream = uaw.ifofstreampreprocesser(source_file=source_file_format,
                                                         inputstreampath=self.testfilein,
                                                         outputstreampath=testfileout_test,
                                                         ifopreppath=Config.ifostreampreppath, flags=Config.flag_list)
            self.save_source_file(src_file=source_file_format, prefix=prefix, ending="final")

            # D. check if transformation was successful
            source_file_format_exe: str = uaw.compileclang(source_file=source_file_format, compilerflags=Config.compilerflags_list)
            uaw.executecontestfile(source_file_executable=source_file_format_exe, testfilein=self.testfilein,
                                   testfileout=testfileout_test, ifofstream=self.ifofstream)

            transformedhash = uaw.computeHash(source_file=testfileout_test)
            if transformedhash != self.originaloutputhash:
                raise Exception("Output file has changed!!")

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
            if 'testfileout_test' in locals() and os.path.exists(testfileout_test):
                os.remove(testfileout_test)
            if 'source_file_format' in locals() and os.path.exists(source_file_format):
                os.remove(source_file_format)

        return loadnewfeatures, error_code, transf_call



    def get_source_log_file_target(self, src_file: str, prefix: str, ending: str) -> str:
        src_file_splitted: typing.Tuple[str, str] = os.path.splitext(os.path.basename(src_file))
        assert len(src_file_splitted) == 2

        logfile: str = "_".join([src_file_splitted[0], prefix, ending, src_file_splitted[1]])
        return os.path.join(self.log_directory, logfile)


    def save_source_file(self, src_file: str, prefix: str, ending: str) -> None:
        """
        Saves the src_file to the logdirectory. Only if savemorelogfiles is true in log file.
        :param src_file: full path to src file
        :param prefix: prefix that we will add
        :param ending: string that we will add as ending
        """
        if Config.savemorelogfiles:
            b = self.get_source_log_file_target(src_file=src_file, prefix=prefix, ending=ending)
            shutil.copyfile(src_file, b)
