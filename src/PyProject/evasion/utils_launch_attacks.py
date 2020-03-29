# import sys
# import collections
# import traceback

import evasion.BlackBox.SimAnnealing.HillClimbingAttack as HillClimbingAttack
from evasion.BlackBox.AMCTS.AMCTSAttack import AMonteCarloTreeSearch
from evasion.BBAttackHandler import BBAttackHandler
from evasion.AttackStatus import AttackStatus
from evasion.AttackResult import AttackResult
from evasion.EvasionAlgorithm import EvasionAlgorithm
from evasion.BlackBox.AttackSettings import MCTSClassicSettings, SimAnnealingSettings

from evasion.AttackLogging import SharedCounters

import time
import os
import pickle
import argparse
import typing


def launch_attack(args: tuple,
                  counter_eq: SharedCounters.SharedCounterSingle,
                  attack_settings: typing.Union[SimAnnealingSettings, MCTSClassicSettings]):
    """
    Wrapper to start the attack. Originally used for multiprocessing, now the interface to start attacks.
    """

    if attack_settings.evasion_algorithm == EvasionAlgorithm.MCTS_Classic:
        retresult = domcts(args, counter_eq, attack_settings)
    elif attack_settings.evasion_algorithm == EvasionAlgorithm.SimAnnealing:
        retresult = doannealing(args, counter_eq, attack_settings)
    else:
        raise Exception("Wrong attack strategy chosen as parameter")

    return retresult


def doannealing(args: tuple,
                counter_eq: SharedCounters.SharedCounterSingle,
                attack_settings: SimAnnealingSettings) -> AttackResult:
    """
    Starts HillClimbing/Sim.Annealing for attack.
    """
    sourceauthor, targetauthor, attackdirauthtarget, testlearnsetup, seed_range, logger = args

    # try various seeds
    lastresult: AttackResult = None
    for curseed in range(seed_range[0], seed_range[1]):

        logger.debug("-".join(["Start", sourceauthor.author,targetauthor.author,str(curseed)]))

        attackhandler: 'BBAttackHandler' = HillClimbingAttack.HillClimbingAttack(attackdirauth=attackdirauthtarget,
                                                                                 sourceauthor=sourceauthor,
                                                                                 targetauthor=targetauthor,
                                                                                 learnsetup=testlearnsetup,
                                                                                 simannealingsettings=attack_settings,
                                                                                 initialseed=curseed,
                                                                                 )

        results: AttackResult = attackhandler.run_attack()

        log_attack_process(logger=logger, attackresult=results)
        log_seed_process(status=results.attackstatus == AttackStatus.SUCCESS, curseed = curseed,
                         seedrange=seed_range, logger=logger)

        lastresult = results
        if results.attackstatus == AttackStatus.SUCCESS:
            break
        elif results.attackstatus == AttackStatus.ERROR:
            # since error could also happen due to IO blocking error (that sometimes occured on some machines..)
            time.sleep(5)


    counter_eq.decrement()
    add_attack_result_to_sharedcounter(attackresult=lastresult, counter=counter_eq)
    show_final_attack_stats(logger=logger, counter=counter_eq)

    return lastresult


def domcts(args: tuple,
           counter_eq: SharedCounters.SharedCounterSingle,
           attack_settings: MCTSClassicSettings) -> AttackResult:
    """
    Starts the Monte-Carlo Tree Search attack algorithm.
    """
    sourceauthor, targetauthor, attackdirauthtarget, testlearnsetup, seed_range, logger = args

    logger.debug("-".join(["Start", sourceauthor.author, targetauthor.author, "MCTS"]))

    if attack_settings.evasion_algorithm == EvasionAlgorithm.MCTS_Classic:
        attackhandler: AMonteCarloTreeSearch = AMonteCarloTreeSearch(attackdirauth=attackdirauthtarget,
                                                               sourceauthor=sourceauthor,
                                                               targetauthor=targetauthor,
                                                               learnsetup=testlearnsetup,
                                                               mctsclassicsettings=attack_settings,
                                                               initialseed=seed_range[0],
                                                               )
    else:
        raise Exception("Wrong evasion_algorithm")


    lastresult: AttackResult = attackhandler.run_attack()
    log_attack_process(logger=logger, attackresult=lastresult)

    counter_eq.decrement()
    add_attack_result_to_sharedcounter(attackresult=lastresult, counter=counter_eq)
    show_final_attack_stats(logger=logger, counter=counter_eq)
    return lastresult



def run_simulation(objInstance):
    return objInstance.run_attack()


def loadauthorpairs_impersonation(learnmodelspath, feature_method, learn_method, threshold_sel):
    """
    Short wrapper for loadauthorpairs
    """
    prefix = "authorpairsforimpersonation" + "AllProblems"
    return loadauthorpairs(learnmodelspath, prefix, feature_method, learn_method, threshold_sel)


def loadauthorpairs(learnmodelspath, prefix, feature_method, learn_method, threshold_sel):
    """
    Loads a pickle file that was created by collect_authorpairs.py or analyze_blackbox_imperson.py
    Returns a set of author pairs that we can use for attack.
    :param learnmodelspath: the path to all model files
    :param prefix unique id for authors
    :param feature_method unique id for model
    :param learn_method unique id for model
    :param threshold_sel unique id for model
    :return: no_authors, possible-authors and authorpairs that can be passed to AttackEval and further steps...
    """

    authorsfile = prefix + "_" + feature_method +\
        "_" + learn_method + "_" + str(threshold_sel) + ".pck"

    # load fixed author pairs
    pathtoauthorsfile: str = os.path.join(learnmodelspath, "authorpairs", authorsfile)
    with open(pathtoauthorsfile, 'rb') as curf:
        authorspairs = pickle.load(curf)  # typing.List(typing.Tuple[str,str])

    # if we just aim at specific author pairs, we can limit the number of possible authors..
    a1, a2 = zip(*authorspairs)
    possible_authors = [x for x in list(set(list(a1) + list(a2)))]
    no_authors = None

    return no_authors, possible_authors, authorspairs


def loadauthors_dodging(learnmodelspath, prefix, feature_method, learn_method, threshold_sel):
    authorsfile = prefix + "_" + feature_method + \
                  "_" + learn_method + "_" + str(threshold_sel) + ".pck"

    # load fixed author pairs
    pathtoauthorsfile: str = os.path.join(learnmodelspath, "authorpairs", authorsfile)
    with open(pathtoauthorsfile, 'rb') as curf:
        authors = pickle.load(curf)  # typing.List[str]

    return None, authors, None




def getProblemIDParser():
    parser = argparse.ArgumentParser(description='Start Attack')
    parser.add_argument('problemid', type=str, nargs=1,
                        help='the problem id')
    return parser


### Global Logging Utilities ###

def log_attack_process(logger, attackresult: AttackResult):
    """
    Log the current attack result for author to author rewriting (dodging, impersonation).
    :param logger: logger object
    :param attackresult: current attack result
    """

    if logger is None:
        return

    if attackresult.attackstatus == AttackStatus.ERROR:
        logger.debug("Error occured for {} -> {}".format(
            attackresult.sourceauthor.author, attackresult.targetauthor.author))
        logger.debug(attackresult.error_message[0])
        logger.debug(attackresult.error_message[1])
        # logger.debug("\n")

    else:
        logger.debug("Status for {} -> {}".format(
            attackresult.sourceauthor.author, attackresult.targetauthor.author))
        logger.debug(str(attackresult.attackstatus))
        # logger.debug("\n")


def add_attack_result_to_sharedcounter(attackresult:AttackResult, counter: SharedCounters.SharedCounter):

    if attackresult.attackstatus == AttackStatus.SUCCESS:
        counter.increment_success()
    elif attackresult.attackstatus == AttackStatus.NOSUCCESS:
        counter.increment_nosuccess()
    elif attackresult.attackstatus == AttackStatus.MISCLASS:
        counter.increment_misclass()
    elif attackresult.attackstatus == AttackStatus.ERROR:
        counter.increment_error()
    else:
        raise Exception("Unvalid Attack Result in utils_launch_attacks")


def show_final_attack_stats(logger, counter: SharedCounters.SharedCounter):
    """
    Logs remaining attack instances.
    In addition, if no remaining attack instances are there, this method will log the final attack stats.
    :param logger: global attack logger
    :param counter: Shared Counter
    """

    logger.debug("Remaining:" + str(counter.value()) + "\n")

    if counter.value() == 0:
        logger.debug("Final Status:")
        s, n, m, e = counter.get_stats()
        logger.debug("Success: {}, No-Success: {}, Misclass: {}, Error: {}".format(s, n, m, e))


def log_seed_process(status: bool, curseed: int, seedrange: tuple, logger):
    """
    Log in what outer iteration we achieved the success
    """
    if status is True:
        if curseed > seedrange[0]:
            logger.debug("Success in {}. OUTER-iteration.".format(curseed - seedrange[0]))

