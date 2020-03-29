# import numpy as np
# from abc import ABC, abstractmethod
# import evasion.utils_attack as ua
# import evasion.utils_attack_workflow as uaw
# import Configuration as Config
import os
import typing
import numpy as np
# from featureextractionV2.StyloFeatures import StyloFeatures

import random
import pandas
import sys
import traceback
import sklearn.utils

import Configuration as Config
import evasion.utils_attack as ua

from evasion.BBAttackHandler import BBAttackHandler
from evasion.BBAttackInstance import BBAttackInstance
from evasion.AttackStatus import AttackStatus
from evasion.AttackMode import AttackMode
from evasion.Author import Author
from classification.LearnSetups.LearnSetup import LearnSetup
import evasion.Transformers.TransformerBase
from evasion.AttackResult import AttackResult
from evasion.BlackBox.AttackSettings import SimAnnealingSettings

from evasion.BBBatchAttackInstanceHandler import BBBatchAttackInstanceHandler


class HillClimbingAttack(BBAttackHandler):
    """
    Our Simulated Annealing + HillClimbingAttack procedure.
    This attack allows us to conduct a classic HillClimbingAttack,
    but also to perform a Simulated Annealing variant.
    """

    def __init__(self, attackdirauth: str,
                 sourceauthor: Author, targetauthor: Author,
                 learnsetup: LearnSetup,
                 simannealingsettings: SimAnnealingSettings,
                 initialseed: int = 42
                 ) -> None:

        # call parent's init method
        super(HillClimbingAttack, self).__init__(
            attackdirauth=attackdirauth, sourceauthor=sourceauthor, targetauthor=targetauthor,
            learnsetup=learnsetup, max_iterations=simannealingsettings.max_iterations, attack_mode=simannealingsettings.attack_mode,
            initialseed=initialseed, early_stop=simannealingsettings.early_stop
        )

        # set true if simulated annealing for next transformer
        self.simulated_annealing: bool = simannealingsettings.simulated_annealing
        # tuple to specify annealing params: first: k, second: x, third: z
        # at x. iteration decrease k by setting k = k*z
        self.simulated_annealing_params: typing.List[float, int, float] = list(simannealingsettings.simulated_annealing_params)


    # @Overwrite
    def run_attack(self) -> AttackResult:

        raise NotImplementedError("If you want to have the source code, contact me, but the code is here removed,"
                                  "as not used for the USENIX paper")
