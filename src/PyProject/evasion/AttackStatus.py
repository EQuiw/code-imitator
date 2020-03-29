from enum import Enum

class AttackStatus(Enum):
    """
    Enum to represent the different results after an evasion attack.
    Either we are successful with evasion attack, or we cannot rewrite source author.
    It is also possible that classifier already misclassifies the author,
    then there is no need to conduct a dodging attack.
    """

    SUCCESS=1 # success
    NOSUCCESS=0 # no success with dodging or impersonation
    MISCLASS=2 # source or target misclassified by classifier at the beginning
    ERROR=3 # attack interrupted with unexpected error


