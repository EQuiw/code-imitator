import typing
import sys
import traceback

from evasion.BBAttackHandler import BBAttackHandler
from evasion.BBAttackInstance import BBAttackInstance
from evasion.Author import Author
from evasion.AttackMode import AttackMode
from classification.LearnSetups.LearnSetup import LearnSetup

class RunAuthor(BBAttackHandler):
    """
    Just generate for each author the outputfile for the respective test file input.
    Not more. We reuse AttackInstance to this end.
    The output files allow us to analyze if some author could be compiled, but created no meaningful content
    due to more severe errors...
    """

    def __init__(self, attackdirauth: str,
                 sourceauthor: Author,
                 learnsetup: LearnSetup,
                 ) -> None:

        # call parent's init method
        super(RunAuthor, self).__init__(
            attackdirauth=attackdirauth, sourceauthor=sourceauthor, targetauthor=sourceauthor,
            learnsetup=learnsetup, max_iterations=1, attack_mode=AttackMode.DODGING, initialseed=1,
        )

    # @Overwrite
    def run_attack(self) -> typing.Tuple[bool, str]:

        try:
            # Init Attack Instance, this creates all the basic stuff including the output file.
            attackinstance = BBAttackInstance(sourceauthor = self.sauthor, attackdirauth=self.attackdirauth,
                                              targetauthor = self.tauthor, bbattackhandler=self)
            assert attackinstance.originaloutputhash is not None

            return True, ""

        except Exception as e:
            err_msg: str = "***HillClimbing: Unexpected ERROR *** {} with {}".format(
                self.sauthor.author, str(e))
            print(err_msg, file=sys.stderr)
            traceback.print_tb(e.__traceback__)

            return False, str(err_msg)



