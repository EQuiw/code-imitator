"""
This is a test file to verify that MCTS /SimAnnealing still produces the valid results.
You need to set up the paths correctly (e.g. create ramdisk if you usually also uses a ramdisk).
This file will not save any results in the Results-Directory, only on the temporary attack dir.
Moreover, decide on the evasion algorithm (MCTS or SimAnneal).
"""
import numpy as np
import pickle
import sys
import os

from evasion.AttackEval import AttackEvalImpersonation, AttackEvalFixedDodging, AttackEvalAbstract
import evasion.utils_launch_attacks
import classification.utils_load_learnsetup
import classification.LearnSetups.LearnSetup
from evasion.AttackLogging import Global_Logging, SharedCounters
import Configuration as config
from evasion.AttackMode import AttackMode
from evasion.EvasionAlgorithm import EvasionAlgorithm
from evasion.BlackBox.AttackSettings import SimAnnealingSettings, MCTSClassicSettings


############### ############### ############### ############### ###############
## The only thing you have to do is to decide on attack algorith. Then just run and check if no warnings are shown later
# evasion_algorithm: EvasionAlgorithm = EvasionAlgorithm.SimAnnealing
evasion_algorithm: EvasionAlgorithm = EvasionAlgorithm.MCTS_Classic





############################################################# ##########################################################
PROBLEM_ID = "3264486_5736519012712448"
# PROBLEM_ID = "8294486_5630967708385280"
print("Load default problem id, as in python console mode. Will not parse args", file=sys.stderr)

threshold_sel: float = 1.0
learn_method: str = "RF"
feature_method: str = "Usenix"
IMPERSONATION = True

####
attackdir = os.path.join(config.attackdirConfig, "_".join(["test_mcts_simanneal_blackbox", PROBLEM_ID, feature_method, learn_method,
                                                 str(threshold_sel), str(IMPERSONATION), evasion_algorithm.name]))
config.createattackdir(attdir=attackdir)


possible_authors = ["ACMonster", "4yn", "chocimir", "ALOHA.Brcps"]
no_authors = None


authorspairs = [("ACMonster", "4yn"), ("ALOHA.Brcps", "chocimir")] #

resultsupperpath: str = os.path.join(config.attackdirConfig, "results")
resultsdir = os.path.join(resultsupperpath, "test_mcts_simanneal_blackbox", evasion_algorithm.name, feature_method,
                          learn_method, ("impersonation" if IMPERSONATION else "dodging"))
config.createattackdir(attdir=resultsdir)



############################################################# ##########################################################
# II. Get features #
testlearnsetup: classification.LearnSetups.LearnSetup.LearnSetup = classification.utils_load_learnsetup.load_learnsetup(
    learnmodelspath=config.learnmodelspath,
    feature_method=feature_method,
    learn_method=learn_method,
    problem_id=PROBLEM_ID,
    threshold_sel=threshold_sel)

# Data Check: check whether nan are there
print(np.min(testlearnsetup.data_final_train.getfeaturematrix()), np.max(testlearnsetup.data_final_train.getfeaturematrix()))  # make sure there are no NaN's
print(np.min(testlearnsetup.data_final_test.getfeaturematrix()), np.max(testlearnsetup.data_final_test.getfeaturematrix()))

############################################################# ##########################################################
# III. Attack -- Code Transformations #

seed_range = (40, 44)
assert IMPERSONATION is True

attackeval: AttackEvalAbstract = AttackEvalImpersonation(testlearnsetup=testlearnsetup,
                                                         attack_dir=attackdir,
                                                         no_authors=no_authors,
                                                         selected_authors=possible_authors,
                                                         verbose=False,
                                                         seed=31)

attack_mode__ = AttackMode.IMPERSONATION_WITH_EXAMPLE_FILES
if evasion_algorithm == EvasionAlgorithm.SimAnnealing:
    # Either get settings directly:
    # attack_settings: SimAnnealingSettings = SimAnnealingSettings(
    #   ...
    # )

    # Or use a settings file:
    settings_file = "test_simannealing_impersonation_Usenix.ini"
    attack_settings: SimAnnealingSettings = SimAnnealingSettings.load_settings_from_file(
        path=os.path.join(config.ini_settings_evasionattack_path, settings_file),
        attack_mode=attack_mode__
    )

elif evasion_algorithm == EvasionAlgorithm.MCTS_Classic:

    settings_file = "test_amcts_impersonation_Usenix.ini"
    attack_settings: MCTSClassicSettings = MCTSClassicSettings.load_settings_from_file(
        path=os.path.join(config.ini_settings_evasionattack_path, settings_file),
        attack_mode=attack_mode__
    )

else:
    raise Exception("Wrong Evasion Algorithm")





################
# Now do hill climbing / simulated annealing / MCTS attack
# a. first, we need a global logger that logs success / error of all instances in one file for a better overview
#   but we also have an individual logger for each instance with much more detailed logs
logpath= os.path.join(attackdir, "logs")
global_logger = Global_Logging.logger_sequential_init(logfilepath=logpath)

# save settings
attack_settings.dump(logpath)

# b. generate all instances, put them into a list...
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
    resultsfile = os.path.join(resultsdir, "results_" + PROBLEM_ID + "_" + str(threshold_sel) + ".pck")
    with open(resultsfile, "wb") as curf:
        pickle.dump(attackeval.authorEvasionMapping, curf)


Global_Logging.close_logger_sequential(logger=global_logger)
print("Attack finished on " + PROBLEM_ID)

### Now perform some checks ###
import evasion.AttackResult
import evasion.AttackStatus

res_1: evasion.AttackResult.AttackResult = attackeval.authorEvasionMapping.loc['ACMonster', '4yn']
assert res_1.attackstatus == evasion.AttackStatus.AttackStatus.SUCCESS

if evasion_algorithm == EvasionAlgorithm.MCTS_Classic:
    expected_scores = np.array([ 0.00017857,  0.01281803,  0.04768637,  0.07189862,  0.07883553,
        0.08470679])
elif evasion_algorithm == EvasionAlgorithm.SimAnnealing:
    expected_scores = np.array([ 0.00017857,  0.01281803,  0.04768637,  0.05279924,  0.05971047,
        0.09389864])
else:
    raise Exception("Evasion Algorithm not supported here in test case!")
assert np.allclose(np.array(res_1.log_chosentransformers.score), expected_scores)


res_2: evasion.AttackResult.AttackResult = attackeval.authorEvasionMapping.loc['ALOHA.Brcps', 'chocimir']
assert res_2.attackstatus == evasion.AttackStatus.AttackStatus.SUCCESS

if evasion_algorithm == EvasionAlgorithm.MCTS_Classic:
    assert np.array(res_2.log_chosentransformers.transformer_id)[-1] == 'Typedef_add_listing'

    expected_scores = np.array([ 0.        ,  0.00382957,  0.00772568,  0.01385755,  0.02119358,
        0.03154124,  0.04592232,  0.0926928 ,  0.11608453,  0.13608492])
elif evasion_algorithm == EvasionAlgorithm.SimAnnealing:
    assert np.array(res_2.log_chosentransformers.transformer_id)[-1] == 'DeclNam:variable'
    expected_scores = np.array([ 0.        ,  0.00382957,  0.01564326,  0.01946591,  0.02352267,
        0.02871822,  0.07109563])
else:
    raise Exception("Evasion Algorithm not supported here in test case!")

assert np.allclose(np.array(res_2.log_chosentransformers.score), expected_scores)




