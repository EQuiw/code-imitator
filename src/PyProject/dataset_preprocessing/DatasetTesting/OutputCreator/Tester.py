from evasion.BBAttackHandler import BBAttackHandler
import os
import sys
import typing
import evasion.utils_launch_attacks
import classification.utils_load_learnsetup
import classification.LearnSetups.LearnSetup

from evasion.Author import Author
from dataset_preprocessing.DatasetTesting.OutputCreator import RunAuthor
import evasion.AttackLogging.Attack_Logging

import Configuration as config



parser = evasion.utils_launch_attacks.getProblemIDParser()
args = parser.parse_args()
PROBLEM_ID = args.problemid[0]

threshold_sel: float = 1.0
attackdir = os.path.join(config.attackdirConfig, "OutputCheck", PROBLEM_ID)
config.createattackdir(attdir=attackdir)


## just needed for loading all authors
testlearnsetup: classification.LearnSetups.LearnSetup.LearnSetup = classification.utils_load_learnsetup.load_learnsetup(
    learnmodelspath=config.learnmodelspath,
    feature_method="Usenix",
    learn_method="RF",
    problem_id=PROBLEM_ID,
    threshold_sel=threshold_sel)


authors = testlearnsetup.data_final_test.getauthors()


## Now create output file for each author
results = {}
logpath= os.path.join(attackdir, "logs")
config.createattackdir(logpath)

logger = evasion.AttackLogging.Attack_Logging.Logger(logfilepath=logpath,
                                                     logging_id=PROBLEM_ID)

for r in range(len(authors)):

    source_author_str = authors[r]
    sourceauthor = Author(author=source_author_str, learnsetup=testlearnsetup)
    attackdirauthtarget = os.path.join(attackdir, source_author_str)

    attackhandler: 'BBAttackHandler' = RunAuthor.RunAuthor(attackdirauth=attackdirauthtarget,
                                                           sourceauthor=sourceauthor,
                                                           learnsetup=testlearnsetup)

    res: typing.Tuple[bool, str] = attackhandler.run_attack()
    results[source_author_str] = res
    if res[0] is False:
        logger.logger.debug(str(source_author_str) + ": " + str(res[1]))


print("*"*30+"\n", file=sys.stderr)
for k, v in results.items():
    if v[0] is False:
        print(k, results[k], file=sys.stderr)

print("*"*30+"\n", file=sys.stderr)
