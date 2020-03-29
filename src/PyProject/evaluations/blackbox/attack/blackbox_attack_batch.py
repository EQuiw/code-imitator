"""
ATTACK EVALUATION ::::::: !!!!!! ::::::: !!!!!! :::::::
"""
import numpy as np
import pickle
import os

from evasion.AttackEval import AttackEvalImpersonation, AttackEvalFixedDodging, AttackEvalAbstract
import evasion.utils_launch_attacks
from evasion.AttackMode import AttackMode
import classification.utils_load_learnsetup
from classification.LearnSetups.LearnSetup import LearnSetup
from evasion.AttackLogging import Global_Logging, SharedCounters
import argparse
import evaluations.blackbox.utils
from evasion.EvasionAlgorithm import EvasionAlgorithm
from evasion.BlackBox.AttackSettings import SimAnnealingSettings, MCTSClassicSettings

import Configuration as config

############################################################# ##########################################################
## Here, we run the attacks for a batch of author pairs to decrease computation time ##
## To test this script, you may want to set PROBLEM_ID and BATCH_ID to a single value (see comments below) and try...
############################################################# ##########################################################

TEST_MODE = False # choose true, if you just want to test s.th. without overwriting final results.... <<< Choose

# PROBLEM_ID = "3264486_5736519012712448"
# BATCH_ID = 1
#print("Load default problem id, as in python console mode. Will not parse args", file=sys.stderr)

parser = argparse.ArgumentParser(description='Start Parallel Attack')
parser.add_argument('problemid', type=str, nargs=1, help='the problem id')
parser.add_argument('authorset', type=str, nargs=1, help='the problem range')
args = parser.parse_args()
PROBLEM_ID = args.problemid[0]
BATCH_ID = int(args.authorset[0])

ch_choice = 0
threshold_sel: float = [1.0, 800][ch_choice] # <<< Choose
learn_method: str = ["RF", "RNN"][ch_choice] # <<< Choose
feature_method: str = ["Usenix", "CCS18"][ch_choice] # <<< Choose
impersonation_with_examplefile: bool = True
IMPERSONATION = True
evasion_algorithm: EvasionAlgorithm = EvasionAlgorithm.MCTS_Classic


####
attackdir = os.path.join(config.attackdirConfig, "_".join(["blackbox", PROBLEM_ID, str(BATCH_ID), feature_method, learn_method,
                                                           str(threshold_sel), str(IMPERSONATION), evasion_algorithm.name]))
if IMPERSONATION is True:
    attackdir = attackdir + "_" + str(impersonation_with_examplefile)
if not os.path.exists(attackdir):
    os.makedirs(attackdir)

if IMPERSONATION is True:
    _, pos_authors, authorspairs = evasion.utils_launch_attacks.loadauthorpairs_impersonation(
        learnmodelspath=config.learnmodelspath, feature_method=feature_method,
        learn_method=learn_method, threshold_sel=threshold_sel)

    ## Now split possible authors; # total_no_batches=19 so that with 380 pairs, we have 20 in each batch
    authorspairs, possible_authors, no_authors = evaluations.blackbox.utils.compute_impersonation_pairs(
        batch_id=BATCH_ID,
        authorspairs=authorspairs,
        possible_authors=pos_authors,
        total_no_batches=19)
else:
    authorspairs, possible_authors, no_authors = evaluations.blackbox.utils.compute_dodging_pairs(
        batch_id=BATCH_ID,
        total_no_batches=17,
        learnmodelspath=config.learnmodelspath,
        feature_method=feature_method,
        learn_method=learn_method,
        problem_id=PROBLEM_ID,
        threshold_sel=threshold_sel)


if TEST_MODE is True: # overwrite if we just want to test s.th.
    possible_authors = ["ACMonster", "4yn", "AnonymousBunny"] #, "AnonymousBunny", "ALOHA.Brcps"]
    no_authors = None
    authorspairs = None


resultsupperpath: str = config.evasionattackpath if TEST_MODE is False else os.path.join(config.attackdirConfig, "results")
resultsdir = os.path.join(resultsupperpath, "blackbox", evasion_algorithm.name, feature_method,
                          learn_method, ("impersonation" if IMPERSONATION else "dodging"))
if IMPERSONATION is True:
    resultsdir = os.path.join(resultsdir, "withexample_" + str(impersonation_with_examplefile))
resultsdir = os.path.join(resultsdir, PROBLEM_ID)
config.createattackdir(attdir=resultsdir)

############################################################# ##########################################################
# II. Get features #
testlearnsetup: LearnSetup = classification.utils_load_learnsetup.load_learnsetup(
    learnmodelspath=config.learnmodelspath,
    feature_method=feature_method,
    learn_method=learn_method,
    problem_id=PROBLEM_ID,
    threshold_sel=threshold_sel)

# Data Check: check whether nan are there
print(np.min(testlearnsetup.data_final_train.getfeaturematrix()), np.max(testlearnsetup.data_final_train.getfeaturematrix()))
print(np.min(testlearnsetup.data_final_test.getfeaturematrix()), np.max(testlearnsetup.data_final_test.getfeaturematrix()))

############################################################# ##########################################################
# III. Attack -- Code Transformations #
## We have four options: we can do an impersonation attack or dodging attack + simulated annealing or MCTS.

seed_range = (40, 45)
if IMPERSONATION:
    attackeval: AttackEvalAbstract = AttackEvalImpersonation(testlearnsetup=testlearnsetup,
                                                                  attack_dir=attackdir,
                                                                  no_authors=no_authors,
                                                                  selected_authors=possible_authors,
                                                                  verbose=False,
                                                                  seed=31)
    attack_mode__ = AttackMode.IMPERSONATION_WITH_EXAMPLE_FILES if impersonation_with_examplefile is True \
        else AttackMode.IMPERSONATION_WITHOUT_EXAMPLE_FILES

    if evasion_algorithm == EvasionAlgorithm.SimAnnealing:
        settings_file = "simannealing_impersonation.ini"
        attack_settings: SimAnnealingSettings = SimAnnealingSettings.load_settings_from_file(
            path=os.path.join(config.ini_settings_evasionattack_path, settings_file),
            attack_mode=attack_mode__
        )

    elif evasion_algorithm == EvasionAlgorithm.MCTS_Classic:
        settings_file = "amcts_impersonation_" + feature_method + ".ini"
        attack_settings: MCTSClassicSettings = MCTSClassicSettings.load_settings_from_file(
            path=os.path.join(config.ini_settings_evasionattack_path, settings_file),
            attack_mode=attack_mode__
        )
    else: raise Exception("Wrong Evasion Algorithm")

else:
    attackeval: AttackEvalAbstract = AttackEvalFixedDodging(testlearnsetup=testlearnsetup,
                                                                 attack_dir=attackdir,
                                                                 no_authors=no_authors,
                                                                 selected_authors=possible_authors,
                                                                 verbose=False,
                                                                 seed=31)

    if evasion_algorithm == EvasionAlgorithm.SimAnnealing:
        settings_file = "simannealing_dodging.ini"
        attack_settings: SimAnnealingSettings = SimAnnealingSettings.load_settings_from_file(
            path=os.path.join(config.ini_settings_evasionattack_path, settings_file),
            attack_mode=AttackMode.DODGING
        )

    elif evasion_algorithm == EvasionAlgorithm.MCTS_Classic:
        settings_file = "amcts_dodging_" + feature_method + ".ini"
        attack_settings: MCTSClassicSettings = MCTSClassicSettings.load_settings_from_file(
            path=os.path.join(config.ini_settings_evasionattack_path, settings_file),
            attack_mode=AttackMode.DODGING
        )
    else: raise Exception("Wrong Evasion Algorithm")


################
# Now start attacks
# a. first, we need a global logger that logs success / error of all instances in one file for a better overview
#   but we also have an individual logger for each instance with much more detailed logs
logpath= os.path.join(attackdir, "logs")
global_logger = Global_Logging.logger_sequential_init(logfilepath=logpath)

# save settings
attack_settings.dump(logpath)


# b. generate all instances, put them into a list...
# This was originally used for multiprocessing, but now we use gnu parallel to avoid all the python problems
# with multiprocessing.
procs = []
for sourceauthor, targetauthor, attackdirauthtarget in attackeval.getNextAuthorPair(fix_pair=authorspairs):
    procs.append((sourceauthor, targetauthor, attackdirauthtarget, testlearnsetup, seed_range, global_logger))
print("\n".join(["*" * 35, "Attack on {} pairs".format(len(procs)), "*" * 35]))
shared_cntr = SharedCounters.SharedCounterSingle(len(procs))


# c. now perform evasion attack
for iteration, proc in enumerate(procs):
    retresult = evasion.utils_launch_attacks.launch_attack(proc, shared_cntr, attack_settings)
    attackeval.setAuthorPairResult2(attackresult=retresult, sourceauthor=retresult.sourceauthor,
                                    targetauthor=retresult.targetauthor)

    # save the result, update the final result after each author pair.
    resultsfile = os.path.join(resultsdir, "results_" + PROBLEM_ID + "_" + str(BATCH_ID) +
                               "_" + str(threshold_sel) + ".pck")
    with open(resultsfile, "wb") as curf:
        pickle.dump(attackeval.authorEvasionMapping, curf)


Global_Logging.close_logger_sequential(logger=global_logger)
print("Attack finished on " + PROBLEM_ID + "_" + str(BATCH_ID))

