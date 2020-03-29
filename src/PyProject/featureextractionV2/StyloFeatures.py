import numpy as np
from abc import ABC, abstractmethod
import typing
import copy
import scipy.sparse.csr


class StyloFeatures(ABC):

    def __init__(self):
        # Be careful! If you add new class variables, think of adding them to getitem if necessary.
        # Not needed if they stay the same if we select a subset of rows/authors.

        # the main four elements that we need for authorship attribution:
        #   featurematrix: a scipy.sparse matrix with rows: authors, columns: features
        #   colnames: the names of the columns in featurematrix, the features
        #   authors: an array with the author names, corresponds to the rows of feature matrix
        #   iids: an array with the respective iids, corresponds to the rows of feature matrix
        # In addition: we use labels to convert authors to unique labels for the later classification
        self._featurematrix, self._colnames, self._authors, self._iids = None, None, None, None
        self._labels = None

        # a reference to the next stylo feature object
        self.codestyloreference: typing.Optional['StyloFeatures'] = None

        # indices from feature selection if performed on this object
        self._selected_features_indices: typing.Optional[np.ndarray] = None


    def setnextstylo(self, codestyloreference: typing.Optional['StyloFeatures']):
        self.codestyloreference = codestyloreference


    def __getitem__(self, index):
        """
        Implements the row-access via [].
        For example, you can select the wanted rows via obj[2:5] now.
        Returns a deep copy!
        :param index: the wanted indices
        :return: a new StyloFeatures object with filtered rows.
        """
        # If we use deepcopy, everything works normally, but it is a little bit slower,
        #   since all objects after codestyloreference would be copied over and over recursively.
        #   Thus, we use a simple trick here. We remove the reference before using deepcopy and add it afterwards.
        #   The alternative would be that each child class needs to implement its own get-item method.
        temporaryreference = self.codestyloreference
        self.codestyloreference = None
        newstylofeatureobject = copy.deepcopy(self)
        newstylofeatureobject.codestyloreference = temporaryreference
        self.codestyloreference = temporaryreference

        # now select the rows
        newstylofeatureobject._featurematrix = newstylofeatureobject._featurematrix[index, :]
        newstylofeatureobject._iids = newstylofeatureobject._iids[index]
        newstylofeatureobject._authors = newstylofeatureobject._authors[index]
        newstylofeatureobject._labels = newstylofeatureobject._labels[index]
        # _selected_features_indices remains the same, so no need to adjust other class variables.

        # now go to next object in chain
        if self.codestyloreference is not None:
            nextobj = self.codestyloreference[index]
            newstylofeatureobject.codestyloreference = nextobj

        return newstylofeatureobject

    @abstractmethod
    def getunique_key(self) -> str:
        """
        Returns a unique key for this feature object, e.g. if tf is true, but idf false, it should return
        something like 'tf-true-idf-false'.
        It is used to check that we have the correct training object for a test-time object
        when using the tf-idf-transformers of the training object. Remind that we should rely on the
        tf-idf-transformers from the training set for each novel test set to avoid data snooping.
        :return: a unique key
        """
        pass

    @abstractmethod
    def getfeaturematrix(self) -> scipy.sparse.csr.csr_matrix:
        """
        Get feature amtrix
        """
        pass


    @abstractmethod
    def getcolnames(self) -> np.ndarray:
        """
        Get column names as strings
        """
        pass

    @abstractmethod
    def getcolnamesraw(self) -> list:
        """
        Get column names as original FeatureNames objects
        """
        pass

    @abstractmethod
    def getauthors(self) -> np.ndarray:
        """
        Get authors
        """
        pass

    @abstractmethod
    def getiids(self) -> np.ndarray:
        """
        Get iids
        """
        pass

    @abstractmethod
    def getlabels(self) -> np.ndarray:
        """
        Get labels
        """
        pass


    @abstractmethod
    def createtfidffeatures(self, trainobject: typing.Optional['StyloFeatures']) -> None:
        """
        Create TF-IDF features.
        :param trainobject: a previous training object that saved a tf-idf-transformer.
        """
        pass


    @abstractmethod
    def selectcolumns(self, index: typing.Optional[np.ndarray], trainobject: typing.Optional['StyloFeatures']) -> None:
        """
        Sub-select columns. Important: Either pass index array or trainobject. Do not pass both!
        :param index: array with column indices
        :param trainobject: a previous training object that saved the wanted column indices
        """
        pass
