import scipy.sparse
import numpy as np
from featureextraction import CodeStyloFeatures
from featureextraction.FeatureNames import FeatureName
import typing
from sklearn import preprocessing
import copy

class CodeStyloMergedFeatures:
    """
    Proxy for easy handling of the different feature classes.

    Class where the different Code Stylo Features objects can be merged into a single feature object.
    """

    def __init__(self, codestyloobjects: list):
        # a. define variables, Optional in typing because we fill them with None first.
        # type: (typing.Optional[scipy.sparse.csr_matrix], typing.Optional[FeatureName])
        self.featurematrix, self.colnames = None, None
        # type: (typing.Optional[np.ndarray], typing.Optional[np.ndarray])
        self.authors, self.iids = None, None


        # b. fill variables with all code stylo objects
        self.__merge(codestyloobjects=codestyloobjects)

        # c. create labels
        le = preprocessing.LabelEncoder()
        le.fit(self.authors)
        self.labels = le.transform(self.authors)

        # d. save reference to input list so that elements can be retrieved separately later.
        self.codestyloobject_list: typing.List[CodeStyloFeatures] = codestyloobjects

        # e. save selected columns due to feature selection
        self.sel_features_indices = None


    def __check_type(self) -> None:
        # now check that the return type of each subclass is correct.  Type Safety first.
        assert type(self.featurematrix) is scipy.sparse.csr_matrix
        assert type(self.colnames) is list
        assert type(self.authors) is np.ndarray
        assert type(self.iids) is np.ndarray

        assert self.featurematrix.dtype is np.dtype("float32")
        assert self.featurematrix.shape[1] == len(self.colnames)


    def __merge(self, codestyloobjects: list) -> None:

        # get the first element so we do not merge with an empty object in the for-loop
        assert isinstance((codestyloobjects[0]), CodeStyloFeatures.CodeStyloFeatures)
        self.featurematrix = (codestyloobjects[0]).featurematrix
        self.colnames = copy.deepcopy((codestyloobjects[0]).colnames)
        self.authors = (codestyloobjects[0]).authors.copy()
        self.iids = (codestyloobjects[0]).iids.copy()


        # now merge the other objects, as we already have the first object, skip it..
        iterobs = iter(codestyloobjects)
        next(iterobs)
        for codestyloobj in iterobs:
            # check that we only iterate over code stylo feature objects so that we can easily merge them
            assert isinstance(codestyloobj, CodeStyloFeatures.CodeStyloFeatures)

            # now concatenate their variables with variables from this object
            self.featurematrix = scipy.sparse.hstack([self.featurematrix, codestyloobj.featurematrix], format="csr")
            self.colnames.extend(copy.deepcopy(codestyloobj.colnames))

            # these variables do not need to be merged, but we can check again whether the order is the same:
            cmps: np.ndarray = (codestyloobj.authors != self.authors)
            assert np.sum(cmps) == 0
            cmps: np.ndarray = (codestyloobj.iids != self.iids)
            assert np.sum(cmps) == 0

        # Last but not least, check type and lengths..
        self.__check_type()


    def __getitem__(self, index):
        """
        Implements the row-access via [].
        For example, you can select the wanted rows via obj[2:5] now.
        :param index: the wanted indices
        :return: a new object with filtered rows.
        """

        new_codestyloobject_list = copy.deepcopy(self.codestyloobject_list)
        for i in range(len(new_codestyloobject_list)):
            new_codestyloobject_list[i] = new_codestyloobject_list[i][index]

        return CodeStyloMergedFeatures(new_codestyloobject_list)


    def getcolnames(self):
        """
        A small wrapper to get the feature names as string numpy array
        :return:
        """
        return np.array([str(x) for x in self.colnames])



    def update_tfidffeatures(self, trainobject: typing.Optional['CodeStyloMergedFeatures']) -> None:
        """
        Compute tf-idf on feature matrix and feature names, and update the internal feature matrix and names with
        new values.
        :param trainobject: if set, this object is used for tf-idf transformations.
        """

        featmatrix_list = []
        colnames_list = []
        for i in range(0, len(self.codestyloobject_list)):
            ctrainobj = None if trainobject is None else trainobject.codestyloobject_list[i]
            featmatrix, colnames = self.codestyloobject_list[i].gettfidffeatures(trainobject=ctrainobj)
            featmatrix_list.append(featmatrix)
            colnames_list.append(colnames)

        featurematrix = featmatrix_list[0]
        colnames = colnames_list[0]

        for i in range(1, len(featmatrix_list)):
            featurematrix = scipy.sparse.hstack([featurematrix, featmatrix_list[i]], format="csr")
            colnames = colnames + colnames_list[i]

        self.featurematrix = featurematrix
        self.colnames = colnames


    def update_columns(self, index, trainobject):
        """
        Selects columns. Use index or trainobject, not both.
        :param index: selected column indices due to feature selection
        :param trainobject: if set, this object is used to get selected column indices.
        """

        assert index is None or trainobject is None

        if trainobject is None:
            self.sel_features_indices = index
        else:
            index = trainobject.sel_features_indices

        self.featurematrix = self.featurematrix[:, index]
        self.colnames = [x for i, x in enumerate(self.colnames) if i in index]
