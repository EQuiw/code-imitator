import numpy as np
import typing
from evasion.BlackBox.AMCTS.State import State
from evasion.BlackBox.AMCTS.StateWithAttackInstance import StateWithAttackInstance


class Node:

    def __init__(self,
                 node_id: int,
                 parent: typing.Optional['Node'] = None,
                 state: typing.Optional[typing.Union[State,StateWithAttackInstance]] = None) \
            -> None:

        self.unique_node_id = node_id
        self.parent: 'Node' = parent
        self.childlist: typing.List['Node'] = []

        if state is None:
            self.state: typing.Union[State,StateWithAttackInstance] = State()
        else:
            self.state: typing.Union[State,StateWithAttackInstance] = state


    def __str__(self):
        return "Node" if self.state.state_id is None else "Node:" + str(self.state.state_id)


    def add_child(self, child: 'Node') -> None:
        self.childlist.append(child)


    def get_random_child(self, seed:int) -> 'Node':
        np.random.seed(seed)
        randchoice = np.random.randint(0, len(self.childlist))
        return self.childlist[randchoice]


    def get_child_with_stateid(self, state_id) -> typing.Optional['Node']:
        for child_node in self.childlist:
            if child_node.state.state_id == state_id:
                # we found a match
                newnode = child_node
                return newnode
        return None


    def get_child_with_max_score_mean(self):
        children_scores = np.array([x.state.getMeanScore() for x in self.childlist])
        bestindex = np.where(children_scores == np.max(children_scores))[0][0]
        return self.childlist[bestindex]

    def get_child_with_min_score_mean(self):
        children_scores = np.array([x.state.getMeanScore() for x in self.childlist])
        bestindex = np.where(children_scores == np.min(children_scores))[0][0]
        return self.childlist[bestindex]

    def get_child_with_max_score_std(self):
        children_scores = np.array([x.state.getSdScore() for x in self.childlist])
        bestindex = np.where(children_scores == np.max(children_scores))[0][0]
        return self.childlist[bestindex]

    def get_child_with_lowest_visit_score(self, seed):
        children_scores = np.array([x.state.VisitCount for x in self.childlist])
        bestindex_list = np.where(children_scores == np.min(children_scores))[0]
        np.random.seed(seed)
        randchoice = np.random.randint(0, len(bestindex_list))
        return self.childlist[bestindex_list[randchoice]]