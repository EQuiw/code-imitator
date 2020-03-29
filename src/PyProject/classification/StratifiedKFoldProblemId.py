from sklearn.model_selection import KFold, BaseCrossValidator
import sklearn.utils
import numpy as np
import typing


class StratifiedKFoldProblemId(BaseCrossValidator):
    """
    A Grouped Stratified K-Fold. Ensures that we have unique problems in training- and test set.
    In partiuclar, this class creates folds which have the same number of solution files per author
    AND the training set / test set consists of the same solution files, respectively.
    Assume that we have problems A, B, C, D and we have the authors 1, 2, 3, 4, 5.
    First split consists of problems A,B,C from each author as training set, and of problem D from each author
    as test set. Another split could consist of A,B,D for training, and of problem C for testing.
    """

    def __init__(self, iids:np.ndarray, n_splits: int, shuffle: bool, random_state: int, nocodesperprogrammer: int) -> None:
        super(StratifiedKFoldProblemId, self).__init__()
        self.iids = iids
        self.n_splits = n_splits
        self.shuffle = shuffle
        self.random_state = random_state
        self.probsperprogrammer = nocodesperprogrammer

        # variables that store the current train/test problem ids that are used for generating the splits.
        self.train_index_probs = None
        self.test_index_probs = None

    def get_n_splits(self, X=None, y=None, groups=None) -> int:
        return self.n_splits

    def split(self, X, y=None, groups=None) -> typing.Tuple[np.ndarray, np.ndarray]:
        """
        Each of the input parameters are ignored, but included due to compability with scikit api.
        Only the iids object from constructor is used.
        :param X: ignored
        :param y: ignored
        :param groups: ignored
        :return: np array of train and test indices.
        """
        # extract the problem id from the iids
        problem_ids = [x.split("_")[1] for x in self.iids]
        assert len(set(problem_ids)) == self.probsperprogrammer

        problem_id_no = np.unique(np.array(problem_ids))
        kf = KFold(n_splits=self.n_splits, random_state=self.random_state + 42)

        for train_index, test_index in kf.split(problem_id_no):
            print("TRAIN:", train_index, "TEST:", test_index)
            self.train_index_probs = problem_id_no[train_index]
            self.test_index_probs = problem_id_no[test_index]

            sel_train_rows = np.array(
                [(True if x.split("_")[1] in problem_id_no[train_index] else False) for x in self.iids],
                dtype=np.bool)
            sel_test_rows = np.array(
                [(True if x.split("_")[1] in problem_id_no[test_index] else False) for x in self.iids],
                dtype=np.bool)
            train_rows = np.arange(len(self.iids))[sel_train_rows]
            test_rows = np.arange(len(self.iids))[sel_test_rows]
            assert np.sum(sel_train_rows) + np.sum(sel_test_rows) == len(self.iids)

            if self.shuffle:
                train_rows = sklearn.utils.shuffle(train_rows, random_state=self.random_state)
                test_rows = sklearn.utils.shuffle(test_rows, random_state=self.random_state)

            yield train_rows, test_rows

    def get_n_problems(self, X=None, y=None, groups=None) -> typing.Tuple[np.ndarray, np.ndarray]:
        """
        Returns the current ids of the problems used for training and testing.
        If split was not called before, they are None. After that, you get the current state after split() always.
        :param X: ignored
        :param y: ignored
        :param groups: ignored
        :return: iids of problems used for training, iids used for testing
        """
        return self.train_index_probs, self.test_index_probs

    def _iter_test_masks(self, X=None, y=None, groups=None):
        """Generates boolean masks corresponding to test sets.
        By default, delegates to _iter_test_indices(X, y, groups)
        """
        raise NotImplementedError

    def _iter_test_indices(self, X=None, y=None, groups=None):
        """Generates integer indices corresponding to test sets."""
        raise NotImplementedError

