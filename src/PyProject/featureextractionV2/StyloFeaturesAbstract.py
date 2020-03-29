import numpy as np
from abc import abstractmethod
import scipy.sparse
import typing
import copy
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn import preprocessing

from featureextractionV2.StyloFeatures import StyloFeatures


class StyloFeaturesAbstract(StyloFeatures):

    def __init__(self, inputdata: typing.Union[str, list, dict],
                 tf: bool, idf: bool,
                 trainobject: typing.Optional['StyloFeaturesAbstract']) -> None:
        """
        :param inputdata: input where features are given. A string with filepath, a dict with lists,
        or a list with features in it.
        :param trainobject: a previously created StyloFeaturesAbstract object that is used to get vectorizer and
         tfidf-transformer. If this object will be a validation- or test-set object, use this parameter to pass the
         training object.
        """
        super(StyloFeaturesAbstract, self).__init__()

        # Save a possible tf idf transformer that can be used to transform the various features later
        self._tfidftransformer: typing.Optional[TfidfTransformer] = None
        self.tf: bool = tf
        self.idf: bool = idf

        if trainobject is not None:
            if self.getunique_key() != trainobject.getunique_key():
                raise Exception("Passed train-time object and test-time object do not match to each other")

        # call the data extraction method that each subclass needs to implement
        self._featurematrix, self._colnames, self._authors, self._iids = self.read_data_from_source(inputdata,
                                                                                                    trainobject)

        # create labels
        le = preprocessing.LabelEncoder()
        le.fit(self._authors)
        self._labels = le.transform(self._authors)

        # some final checks, such as data type or length, to avoid very simple mistakes.
        self.do_checks()


    def do_checks(self):
        """
        Perform a series of small checks to avoid simple mistakes.
        Throws Assertion error if anything is not correct.
        """
        # now check that the return type of each subclass is correct and some more short checks.
        assert type(self._featurematrix) is scipy.sparse.csr_matrix
        assert type(self._colnames) is list
        assert type(self._authors) is np.ndarray
        assert type(self._iids) is np.ndarray
        assert type(self._labels) is np.ndarray
        assert len(self._labels) == len(self._iids) == len(self._authors)
        assert len(self._colnames) == self._featurematrix.shape[1]
        assert self._featurematrix.dtype is np.dtype("float32")


    @abstractmethod
    def read_data_from_source(self,
                              inputdata: typing.Union[str, list, dict],
                              trainobject: typing.Optional['StyloFeaturesAbstract']) \
            -> typing.Tuple[scipy.sparse.csr_matrix, list, np.ndarray, np.ndarray]:
        """
        Reads the features, labels and column names
        :param inputdata: input where features are given. A string with filepath, a dict with lists,
        or a list with features in it.
        :param trainobject: a previously created StyloFeaturesAbstract that is used to get vectorizer and
         tfidf-transformer.
        :return: featurematrix, colnames, authors, ids
        """
        pass


    # @Overwrite
    def getfeaturematrix(self) -> scipy.sparse.csr.csr_matrix:
        if self.codestyloreference is None:
            return self._featurematrix.copy()
        else:
            assert isinstance(self.codestyloreference, StyloFeatures)
            featurematrix = scipy.sparse.hstack([self._featurematrix.copy(),
                                                 self.codestyloreference.getfeaturematrix()],
                                                format="csr")
            assert type(featurematrix) is scipy.sparse.csr_matrix
            assert featurematrix.dtype is np.dtype("float32")
            return featurematrix


    # @Overwrite
    def getcolnames(self) -> np.ndarray:
        convertedcolnames = np.array([str(x) for x in self._colnames])
        if self.codestyloreference is None:
            return convertedcolnames
        else:
            assert isinstance(self.codestyloreference, StyloFeatures)
            return np.concatenate((convertedcolnames, self.codestyloreference.getcolnames()),axis=0)


    # @Overwrite
    def getcolnamesraw(self) -> list:
        if self.codestyloreference is None:
            return copy.deepcopy(self._colnames)
        else:
            assert isinstance(self.codestyloreference, StyloFeatures)
            return copy.deepcopy(self._colnames) + self.codestyloreference.getcolnamesraw()


    # @Overwrite
    def getauthors(self) -> np.ndarray:
        if self.codestyloreference is None:
            return copy.deepcopy(self._authors)
        else:
            cmps = (self.codestyloreference.getauthors() != self._authors)
            assert np.sum(cmps) == 0
            return copy.deepcopy(self._authors)

    # @Overwrite
    def getiids(self) -> np.ndarray:
        if self.codestyloreference is None:
            return copy.deepcopy(self._iids)
        else:
            cmps = (self.codestyloreference.getiids() != self._iids)
            assert np.sum(cmps) == 0
            return copy.deepcopy(self._iids)

    # @Overwrite
    def getlabels(self) -> np.ndarray:
        if self.codestyloreference is None:
            return copy.deepcopy(self._labels)
        else:
            cmps = (self.codestyloreference.getlabels() != self._labels)
            assert np.sum(cmps) == 0
            return copy.deepcopy(self._labels)


    # @Overwrite
    def selectcolumns(self, index:  typing.Optional[np.ndarray], trainobject: typing.Optional['StyloFeatures']) -> None:

        assert index is None or trainobject is None
        if trainobject is not None:
            assert trainobject.getunique_key() == self.getunique_key()

        nextindex = None
        if trainobject is None:
            newindex, nextindex = self.__getsubcolumns(index=index)
            self._selected_features_indices = newindex
        else:
            newindex = trainobject._selected_features_indices

        self._featurematrix = self._featurematrix[:, newindex]
        # self._colnames = [x for i, x in enumerate(self._colnames) if i in newindex]
        self._colnames = [self._colnames[i] for i in newindex]

        if self.codestyloreference is not None:
            if trainobject is None:
                self.codestyloreference.selectcolumns(index=nextindex, trainobject=None)
            else:
                self.codestyloreference.selectcolumns(index=None, trainobject=trainobject.codestyloreference)


    def __getsubcolumns(self, index: np.ndarray) -> typing.Tuple[np.ndarray, np.ndarray]:
        """
        Get the subcolumns for the current stylo object. The index can be larger and span over more code stylo
        objects, so that we need to extract only those indices that are relevant for the current feature object.
        :param index: indices
        :return: indices relevant for the current object, indices relevant for the next object
        """

        nofeats = len(self._colnames)
        cindex = np.copy(index)
        newindices = cindex[np.where(cindex < nofeats)[0]]
        nextindices = cindex[np.where(cindex >= nofeats)[0]] - nofeats
        return newindices, nextindices
        #
        # lastnofeats = 0
        #     for i, codestyloobj in enumerate(self._codestylobjects):
        #         ctrainobj = None if trainobject is None else trainobject._codestylobjects[i]
        #         if ctrainobj is not None:
        #             assert ctrainobj.getunique_key() == trainobject.getunique_key()
        #             assert str(ctrainobj.__class__) == str(codestyloobj.__class__)
        #
        #         # we get a list of indices that covers the whole feature matrix over all individual components, thus
        #         #   we need to split the indices regarding the individual components. To this end, we use a simple method:
        #         #   we subtract the indices by the current window that codestyloobj represents and keep only valid indices.
        #         #   In this way, we get the indices relative to the current codestyloobj.
        #         nofeats = len(codestyloobj.getcolnames())
        #         cindex = np.copy(index) - lastnofeats
        #         lastnofeats += nofeats
        #
        #         codestyloobj.selectcolumns(index=newindices, trainobject=ctrainobj)

    # @Overwrite
    def createtfidffeatures(self, trainobject: typing.Optional['StyloFeaturesAbstract']):

        # Key check if trainingobject and this object belong to each other.
        if trainobject is not None:
            assert trainobject.getunique_key() == self.getunique_key()

        # we check if we actually want a tf-transformation and if feature matrix is not empty. Otherwise, skip.
        if self.tf and len(self._colnames) > 0:
            for x in self._colnames:
                x.settfidf(tf=self.tf, idf=self.idf)
            if trainobject is None:
                tfidftransformer = TfidfTransformer(norm="l2", use_idf=self.idf)
                self._featurematrix = tfidftransformer.fit_transform(self._featurematrix).astype(np.float32)
                self._tfidftransformer = tfidftransformer
            else:
                self._featurematrix = trainobject._tfidftransformer.transform(self._featurematrix).astype(np.float32)

        if len(self._colnames) == 0 and trainobject is not None:
            # short a short check, can be removed later.
            assert len(trainobject._colnames) == 0

        # go to next feature object.
        if self.codestyloreference is not None:
            if trainobject is None:
                self.codestyloreference.createtfidffeatures(trainobject=None)
            else:
                self.codestyloreference.createtfidffeatures(trainobject=trainobject.codestyloreference)

