import numpy as np
from abc import ABC, abstractmethod
import scipy.sparse
import typing
import copy
from sklearn.feature_extraction.text import TfidfTransformer


class CodeStyloFeatures(ABC):

    def __init__(self, inputdata: typing.Union[str, list, dict], trainobject: typing.Optional['CodeStyloFeatures']) -> None:
        self.inputdata_ref = inputdata # remove if not used later

        # call the data extraction method that each subclass needs to implement
        self.featurematrix, self.colnames, self.authors, self.iids = self.read_data_from_source(inputdata, trainobject)

        # Save a possible tf idf transformer that can be used to transform the various features later
        # type: (typing.Optional[TfidfTransformer])
        self.tfidftransformer = None

        self.do_checks()


    def do_checks(self):
        """
        Perform a series of small checks to avoid simple mistakes.
        Throws Assertion error if anything is not correct.
        """
        # now check that the return type of each subclass is correct and some more short checks.
        assert type(self.featurematrix) is scipy.sparse.csr_matrix
        assert type(self.colnames) is list
        assert type(self.authors) is np.ndarray
        assert type(self.iids) is np.ndarray
        assert len(self.colnames) == self.featurematrix.shape[1]
        assert self.featurematrix.dtype is np.dtype("float32")


    @abstractmethod
    def read_data_from_source(self,
                              inputdata: typing.Union[str, list, dict],
                              trainobject: typing.Optional['CodeStyloFeatures']) \
            -> typing.Tuple[scipy.sparse.csr_matrix, list, np.ndarray, np.ndarray]:
        """
        Reads the features, labels and column names
        :param inputdata: input where features are given. A string with filepath, a dict with lists,
        or a list with features in it.
        :param trainobject: a previously created CodeStyloObject that is used to get vectorizer and tfidf-transformer
        :return: featurematrix, colnames, authors, ids
        """
        # return scipy.sparse.csr_matrix(0), np.ndarray([0]), np.ndarray([0]), np.ndarray([0])
        pass


    def __getitem__(self, index):
        """
        Implements the row-access via [].
        For example, you can select the wanted rows via obj[2:5] now.
        :param index: the wanted indices
        :return: a new CodeStyloFeatures object with filtered rows.
        """
        newstylofeatureobject = copy.deepcopy(self)
        newstylofeatureobject.featurematrix = newstylofeatureobject.featurematrix[index, :]
        newstylofeatureobject.iids = newstylofeatureobject.iids[index]
        newstylofeatureobject.authors = newstylofeatureobject.authors[index]
        return newstylofeatureobject


    def mergeToNewObject(self, codestyloobj: 'CodeStyloFeatures'):
        """
        Creates a new CodeStyloFeatures object that is the combination of this object and the given codestyloobj param.
        :param codestyloobj: another CodeStyloFeatures object.
        :return: a new CodeStyloFeatures object.
        """

        codestyloobjcopy = copy.deepcopy(codestyloobj)
        codestyloobjcopy.featurematrix = scipy.sparse.hstack([self.featurematrix, codestyloobj.featurematrix], format="csr")
        codestyloobjcopy.colnames = self.colnames + codestyloobj.colnames

        # authors and iids are already copied.
        assert np.sum((codestyloobj.iids != self.iids)) == 0
        assert np.sum((codestyloobj.authors != self.authors)) == 0

        # reset values that make no sense after merging
        self.tfidftransformer = None
        self.inputdata_ref = None

        codestyloobjcopy.do_checks()

        return codestyloobjcopy


    @abstractmethod
    def gettfidffeatures(self, trainobject: typing.Optional['CodeStyloFeatures']):
        """

        :param trainobject:
        :return:
        """
        pass








