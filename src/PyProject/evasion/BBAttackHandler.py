from abc import ABC, abstractmethod

import typing
from evasion.Author import Author
from classification.LearnSetups.LearnSetup import LearnSetup
from evasion.AttackMode import AttackMode
import Configuration

class BBAttackHandler(ABC):

    def __init__(self, attackdirauth: str,
                 sourceauthor: Author,
                 targetauthor: typing.Optional[Author],
                 learnsetup: LearnSetup,
                 max_iterations: int,
                 attack_mode: AttackMode,
                 initialseed: int = 42,
                 early_stop: typing.Optional[typing.Union[int,float]] = None) -> None:
        """
        Constructor.
        """

        self.attackdirauth: str = attackdirauth
        self.sauthor = sourceauthor
        self.tauthor = targetauthor
        self.attack_mode = attack_mode

        self.learnsetup = learnsetup

        if targetauthor is None:
            self.tauthor = self.sauthor

        self.log_directory: str = None
        self.max_iterations = max_iterations
        self.seed = initialseed

        self.noofparallelthreads = Configuration.noofparallelthreads
        self.early_stop = early_stop

    @abstractmethod
    def run_attack(self):
        """
        Run the attack.
        :return:
        """
        pass
