from enum import Enum


# TODO at some points in code, we also test if doging or impersonation mode by checking
# if target author == source author (if equal, it means doging, it not, impersonation).
# We should replace it by AttackMode enum.


class AttackMode(Enum):
    """
    Enum to represent the different attack modes for an evasion attack.
    """

    # untargeted attack
    DODGING=1
    # targeted attack where we do not have example files
    IMPERSONATION_WITHOUT_EXAMPLE_FILES=2
    # targeted attack where we have example files of target author that were not used during training/test.
    IMPERSONATION_WITH_EXAMPLE_FILES=3