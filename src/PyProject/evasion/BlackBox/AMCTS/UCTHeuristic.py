from evasion.AttackMode import AttackMode
from evasion.BlackBox.AMCTS.Node import Node



def find_best_node_with_uct_heuristic(node: Node, attack_mode: AttackMode, iteration_index: int):
    # In 33.34% of the cases, we choose a child w.r.t to the highest score,
    # in 16.67% of the cases, we choose a child w.r.t to the highest std,
    # in 50% of the cases, a child w.r.t to VisitCount.

    if iteration_index % 2 == 0:
        # lowest visit count
        return node.get_child_with_lowest_visit_score(seed=iteration_index)
    else:
        if iteration_index % 6 == 0:
            # highest std score
            return node.get_child_with_max_score_std()
        else:
            # highest/lowest mean score, w.r.t to attack mode
            return select_next_child_wrt_mean_score(node=node, attack_mode=attack_mode)


def select_next_child_wrt_mean_score(node: Node, attack_mode: AttackMode) -> Node:
    """
    Select next node w.r.t to highest/lowest mean score (depending on attack mode).
    :param node: node
    :param attack_mode: current attack mode (dodging, impersonation (what type?)).
    :return: next node.
    """
    if attack_mode == AttackMode.DODGING:
        return node.get_child_with_min_score_mean()

    elif attack_mode == AttackMode.IMPERSONATION_WITH_EXAMPLE_FILES or \
            attack_mode == AttackMode.IMPERSONATION_WITHOUT_EXAMPLE_FILES:
        return node.get_child_with_max_score_mean()

    else:
        raise Exception("Unknown attack mode here in MCTS select-next-child")