from featureextraction import CodeStyloFeatures
from featureextraction.FeatureNames import FeatureName
import os
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
import numpy as np
from scipy import sparse
import utils_authorship
import typing
import copy

# # use type alias to define the default type of min_df and max_df in scikit's vectorizer:
# min_max_type = typing.Tuple[typing.Union[int, float], typing.Union[int, float]]

class CodeStyloUnigramFeatures(CodeStyloFeatures.CodeStyloFeatures):
    """
    This class creates unigram word features.
    """

    def __init__(self, inputdata: str, noprogrammers: int, nocodesperprogrammer: int, binary:bool,
                 tf: bool, idf: bool, ngram_range: typing.Tuple[int,int],
                 stop_words: typing.List[str],
                 trainobject: typing.Optional['CodeStyloUnigramFeatures']) -> None:
        """
        Constructor for Unigram Features
        :param inputdata: path to directory where each subdirectory contains the program files for a particular programmer
        OR filepath to a specific source file.
        So either use e.g. in our case: .../data/dataset_2017/dataset_2017_8/
        or use .../data/dataset_2017/dataset_2017_8/someauthor/id_id2_authorname.cpp. The author name is obtained
        via the parent directory's name.
        :param noprogrammers: expected numbers of programmer's. Used to check if programmers were missed.
        We use it here since we access the dataset from the disk.
        :param nocodesperprogrammer: expected number of files per programmer.
        :param binary: binary features?
        :param trainobject: used for feature alignment to have same set of features as train set
        and used for tf-idf-transformation. This object should be a CodeStyloUnigramFeatures object,
        representing the training set. In particular, this object is used to vectorize the files for the test set
        and to perform the tf-idf transformation by using the already fitted tf-idf-transformer from the trainobject.
        """

        # we also add some variables that are unique to Unigram Feature extraction:
        self.noprogrammers = noprogrammers
        self.nocodesperprogrammer = nocodesperprogrammer
        self.binary = binary

        self.tf = tf
        self.idf = idf
        self.ngram_range = ngram_range
        self.stop_words = stop_words

        # save the vectorizer of this object, we can use it later to load test data
        self.cvectorizer = None # type: typing.Optional[CountVectorizer]

        # call parent's init method that will call read_data_from_source
        super(CodeStyloUnigramFeatures, self).__init__(inputdata=inputdata, trainobject=trainobject)

    # @Overwrite
    def read_data_from_source(self, inputdata, trainobject):

        unigrammatrix, colnames, authors, iids = self.__get_wordunigrams(verbose=False, inputdata=inputdata, trainobject=trainobject)
        return unigrammatrix, colnames, authors, iids


    def __get_wordunigrams(self, verbose:bool, inputdata: str, trainobject: typing.Optional['CodeStyloUnigramFeatures']) \
            -> typing.Tuple[sparse.csr_matrix, list, np.ndarray, np.ndarray]:
        """
        Extracts the word unigrams from all files in given directory

        :return: the unigram feature matrix (scipy sparse csr_matrix), the vectorizer object,
            the document labels (numpy array)
        """

        documents = []
        documents_labels = []
        documents_authors = []


        # I. If we have a source file directly given, use it directly.
        if inputdata.endswith("cpp"):
            with open(inputdata, "r", encoding='ISO-8859-1') as fh:
                documents.append(fh.read())
                documents_labels.append(os.path.basename(inputdata))
                documents_authors.append(os.path.basename(os.path.dirname(inputdata)))
        else:
            # II. We have a directory where each subdirectory contains the program files
            # Go over each programmer's directory and for each file:
            programmers = [os.path.join(inputdata, o) for o in os.listdir(inputdata) if os.path.isdir(os.path.join(inputdata, o))]
            if verbose:
                print("No. programmers: {0}".format(len(programmers)))

            if self.noprogrammers is not None:
                assert len(programmers) == self.noprogrammers

            for pro in programmers:
                progfiles = [f for f in os.listdir(pro) if os.path.isfile(os.path.join(pro, f)) and f.endswith("cpp")]

                if self.nocodesperprogrammer is not None:
                    assert len(progfiles) == self.nocodesperprogrammer

                for progfile in progfiles:
                    with open(os.path.join(pro, progfile), "r", encoding='ISO-8859-1') as fh:
                        documents.append(fh.read())
                        documents_labels.append(progfile)
                        documents_authors.append(os.path.basename(pro))


        # IV. Vectorize the input, if a CodeStylo object is given, use its vectorizer.
        if trainobject is None:
            self.cvectorizer = CountVectorizer(encoding="ISO-8859-1", analyzer="word", binary=self.binary,
                                               lowercase=False, stop_words=self.stop_words,
                                               ngram_range=self.ngram_range)
            unigrammatrix = self.cvectorizer.fit_transform(documents).astype(np.float32)
            feature_names = self.cvectorizer.get_feature_names()
        else:
            unigrammatrix = trainobject.cvectorizer.transform(documents).astype(np.float32)
            feature_names = trainobject.cvectorizer.get_feature_names()


        # V. Sort features w.r.t. to iids
        feature_matrix, iids, authors = utils_authorship.sortmatrix(matrix1=sparse.csr_matrix(unigrammatrix), matrix1ids=np.array(documents_labels),
                                                                    matrix1authors=np.array(documents_authors))

        # Convert each feature to a FeatureName object to save its properties
        feature_names = [FeatureName(colname=x, coltype="continous", colorigin="unigram")
                         for x in feature_names]

        return feature_matrix, feature_names, authors, iids



    # @Overwrite
    def gettfidffeatures(self, trainobject: typing.Optional['CodeStyloFeatures']):

        featurematrix = copy.deepcopy(self.featurematrix)
        colnames = copy.deepcopy(self.colnames)

        if self.tf:
            for x in colnames:
                x.settfidf(tf=self.tf, idf=self.idf)
            if trainobject is None:
                tfidftransformer = TfidfTransformer(norm="l2", use_idf=self.idf)
                featurematrix = tfidftransformer.fit_transform(featurematrix).astype(np.float32)
                self.tfidftransformer = tfidftransformer
            else:
                featurematrix = trainobject.tfidftransformer.transform(featurematrix).astype(np.float32)

        return featurematrix, colnames