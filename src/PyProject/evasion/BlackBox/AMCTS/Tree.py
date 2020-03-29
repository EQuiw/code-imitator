from evasion.BlackBox.AMCTS.Node import Node
from evasion.BlackBox.AMCTS.State import State
import typing

class Tree:

    def __init__(self):

        self.no_of_nodes = 1
        self.root = Node(node_id=0, parent=None)


    def switch_rootnode(self, newroot: Node):
        self.root = newroot
        self.root.parent = None

    def create_new_node(self,
                        parent: typing.Optional['Node'] = None,
                        state: typing.Optional[State] = None) -> Node:
        newnode = Node(node_id=self.no_of_nodes, parent=parent, state=state)
        self.no_of_nodes += 1

        return newnode


    # def addchild(self, parent: Node, child: Node):
    #     parent.childlist.append(child)