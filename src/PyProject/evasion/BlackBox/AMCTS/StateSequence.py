import typing

from evasion.BlackBox.AMCTS.State import State
from evasion.BlackBox.AMCTS.Node import Node

class StateSequence:

    def __init__(self):

        # various transformations...
        self.states: typing.List[State] = []

        # at what step we stopped the sequence due to empty set, errors, ...
        self.status: int = None

        # check if we want to perform 2nd round on current sequence
        self.exctract_and_do_hash_analysis = False

        # save last node in tree of this sequence so that we can easily backpropagate later...
        self.last_node_of_sequence: Node = None

        # set to true if this sequence was executed and its output file has not been changed...
        self.usable_sequence = False

        self.final_score = None

