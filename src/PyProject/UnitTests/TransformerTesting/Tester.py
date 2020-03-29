#####################################################################################
#####################################################################################
#   #   #   This file and corresponding classes allow us to test a respective transformer
#   #   #   in the way we will call it from Python.. Choose a respective transformer,
#   #   #   and this file will iterate over each author and call the transformer with
#   #   #   various seeds.
#   #   #   We have two options:
#   #   #   a. without execution (only compile check)
#   #   #     Default, for security reasons, the file will not be executed; It's just compiled,
#   #   #     so that we cannot test if the output would be changed,
#   #   #            but if we can check for compiler errors.
#   #   #   b. with execution (then we also check if output changes)
#   #   #     Less secure, since we execute code from unknown developers
#   #   #     Use a Virtual Machine...
#####################################################################################
#####################################################################################

from featureextractionV2.StyloARFFFeatures import StyloARFFFeatures
from evasion.BBAttackHandler import BBAttackHandler
import classification.utils_load_learnsetup
import numpy as np
from evasion.AttackLogging import Global_Logging
from evasion.Author import Author
from evasion.AttackMode import AttackMode
import utils_authorship
from UnitTests.TransformerTesting.TransformerAttackTester import TransformerAttackTester
import pandas

from Configuration import *
def getproblemids():
    arffmatrix = StyloARFFFeatures(inputdata=arffile, removelog=True)
    return np.sort(np.array(list(set([x.split("_")[0] + "_" + x.split("_")[1] for x in arffmatrix.getiids()]))))

def load_transformers_table():
    df: pandas.DataFrame = pandas.read_csv(transformercsvfile)
    df = df.fillna("")
    return df

############################################################# ##########################################################
# TRANSFORMER_ID_TO_TEST = "Cout:ofstreamtocout"
TRANSFORMER_ID_TO_TEST = load_transformers_table().loc[ 9-2 ,"uniqueid"]
print(TRANSFORMER_ID_TO_TEST)

# <<< Choose here how many problems we'd like to test..., if only 1 problem, use 0:1 for 0-th problem.
PROBLEM_IDS = getproblemids()[0:8]
# <<< Decide if targeted, some transformers like those from AddTemplate family require source code example files
ATTACK_MODE = AttackMode.DODGING
# <<< Decide if we just do a compile check or we also check if output behaviour changed
# (SET ONLY TO TRUE IF YOU KNOW WHAT YOU ARE DOING):
CHECK_WITH_EXECUTION = False
I_KNOW_WHAT_I_AM_DOING = False


############################################################# ##########################################################

# replace special characters in transformer id to be able to create dir or file names:
transformer_id_suitable_asname = TRANSFORMER_ID_TO_TEST.replace(":","_").replace(";","_")
# set up log directory and log file:
logdir = os.path.join(attackdirConfig, "tester_logs")
createattackdir(attdir=logdir)
logfile = utils_authorship.create_unique_file_dir_with_suffix(parent_dir=logdir,
                                                              file_or_dir="logfile_" + transformer_id_suitable_asname)
global_logger = Global_Logging.logger_sequential_init(logfilepath=logdir, logfile_name=logfile)


assert isinstance(PROBLEM_IDS, np.ndarray)
if CHECK_WITH_EXECUTION is True and I_KNOW_WHAT_I_AM_DOING is False:
    raise Exception("you want to execute all files, do it with care\n")
if CHECK_WITH_EXECUTION is True:
    print("TESTING WITH OUTPUT CHECK BY EXECUTION (Be careful!)", file=sys.stderr)

for PROBLEM_ID in PROBLEM_IDS:
    print("*"*70)
    print("Problem ID:", PROBLEM_ID)

    attackdir = os.path.join(attackdirConfig, utils_authorship.create_unique_file_dir_with_suffix(
        parent_dir=attackdirConfig, file_or_dir=transformer_id_suitable_asname + "_" + PROBLEM_ID))
    createattackdir(attdir=attackdir)

    ############################################################# ######################################################

    testlearnsetup = classification.utils_load_learnsetup.load_learnsetup(
            learnmodelspath=learnmodelspath,
            feature_method="Usenix",
            learn_method="RF",
            problem_id=PROBLEM_ID,
            threshold_sel=1.0)

    # authors = ["femto", "nofto"]
    authors = testlearnsetup.data_final_test.getauthors()[:]

    for r in range(len(authors)):

        source_author_str = authors[r]
        sourceauthor = Author(author=source_author_str, learnsetup=testlearnsetup)

        if ATTACK_MODE != ATTACK_MODE.DODGING:
            target_author_str = authors[(r + 1) % len(authors)]
            targetauthor = Author(author=target_author_str, learnsetup=testlearnsetup)
            attackdirauthtarget = os.path.join(attackdir, target_author_str, source_author_str)
        else:
            targetauthor = sourceauthor
            attackdirauthtarget = os.path.join(attackdir, source_author_str)

        attackhandler: 'BBAttackHandler' = TransformerAttackTester(attackdirauth=attackdirauthtarget,
                                                                   sourceauthor=sourceauthor,
                                                                   targetauthor=targetauthor,
                                                                   learnsetup=testlearnsetup,
                                                                   max_iterations=6,
                                                                   attack_mode=ATTACK_MODE,
                                                                   initialseed=43,
                                                                   transformer_id=TRANSFORMER_ID_TO_TEST,
                                                                   secure_mode=not CHECK_WITH_EXECUTION)


        output, noerr = attackhandler.run_attack()
        global_logger.debug(output) if noerr is True else global_logger.error(output)


Global_Logging.close_logger_sequential(logger=global_logger)

