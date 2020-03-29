from featureextraction import CodeStyloFeatures
from featureextraction.FeatureNames import FeatureName
from sklearn.feature_extraction import DictVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
import numpy as np
import os
from scipy import sparse
import utils_authorship
import typing
import json
import copy
from abc import ABC, abstractmethod


class CodeStyloJoernFeatCl(CodeStyloFeatures.CodeStyloFeatures, ABC):


    def __init__(self, inputdata: typing.Union[str, list], verbose:bool,
                 trainobject: typing.Optional['CodeStyloJoernFeatCl'], featureclassidentifier: str):
        """
        Class that represents features from clang- or joern

        * Be careful *
        This class has two tf-idf-transformer that may be set later.
        The first represents features with tf-transformation,
        the second represents features with tf-idf-transformation.
        This is so, since some classes, such as ast-node-types, have tf and tf-idf features (see
        Caliskan et al., USENIX.).

        :param inputdata: string with path to .dat file or list with features
        :param verbose: print more progress information
        :param trainobject: training object
        :param featureclassidentifier: string with feature class, e.g. ast_node_bigrams
        """

        self.verbose: bool = verbose
        self.featureclassidentifier: str = featureclassidentifier

        # save the vectorizer of this object, we can use it later to load test data
        self.cvectorizer = None  # type: typing.Optional[DictVectorizer]

        # save 2nd tf-idf-transformer, since some feature classes have tf and tf-idf transformation
        self.tfidftransformer2nd = None

        super(CodeStyloJoernFeatCl, self).__init__(inputdata=inputdata, trainobject=trainobject)



    def gettfidffeatures(self, trainobject: typing.Optional['CodeStyloFeatures']):
        raise NotImplementedError()


    @abstractmethod
    def read_data_from_source(self, inputdata, trainobject) \
            -> typing.Tuple[sparse.csr_matrix, list, np.ndarray, np.ndarray]:
        pass



    def _extract_ast_nodes(self, inputdata, trainobject, bigram: bool) \
            -> typing.Tuple[sparse.csr_matrix, list, np.ndarray, np.ndarray]:
        """
        Extracts AST single/bigram features from a json input file.
        File format of json. For each author one line, each line has the pattern: <name> <id_id> <json array>
        :param inputdata: string or list. Path to .dat file or list with features
        :param trainobject: already fitted trainobject
        :param: bigram: set true if each feature in the json array is a list of two features = bigram or not.
        :return: feature_matrix (csr sparse), feature names, author names, iid's (the last three as np.arrays)
        """

        if not isinstance(inputdata, str) and not isinstance(inputdata, list):
            raise Exception("Unvalid inputdata type")

        if isinstance(inputdata, str):
            with open(inputdata, "r", encoding='ISO-8859-1') as f:
                ast_node_lines = [line.rstrip('\n') for line in f]
        else:
            ast_node_lines = [line.rstrip('\n') for line in inputdata]

        features = []
        authors = []
        iids = []

        for cl in range(len(ast_node_lines)):
            try:
                decoded = json.loads(''.join(ast_node_lines[cl].split(" ")[2:]))

                assert len(decoded) > 1
                authors.append(ast_node_lines[cl].split(" ")[0])
                iids.append(ast_node_lines[cl].split(" ")[1])

                features.append({})
                for cfeat in decoded:
                    if bigram:
                        fname = str(cfeat[0][0] + "_" + cfeat[0][1])
                    else:
                        fname = str(cfeat[0])
                    fval = cfeat[1]
                    features[cl][fname] = np.float32(fval)

            except Exception as e:
                import sys
                print("Error in file, in row:", cl, file=sys.stderr)
                print("{0}".format(e), file=sys.stderr)
                raise e


        # B. Vectorize the input, if a CodeStylo object is given, use its vectorizer.
        if trainobject is None:
            self.cvectorizer = DictVectorizer(sparse=True)
            feature_matrix = self.cvectorizer.fit_transform(features).astype(np.float32)
            feature_names = np.array(self.cvectorizer.get_feature_names())
        else:
            feature_matrix = trainobject.cvectorizer.transform(features).astype(np.float32)
            feature_names = np.array(trainobject.cvectorizer.get_feature_names())

        authors = np.array(authors)
        iids = np.array(iids)

        # sort the matrix w.r.t ids
        feature_matrix, iids, authors = utils_authorship.sortmatrix(matrix1=feature_matrix, matrix1ids=iids,
                                                                    matrix1authors=authors)

        feature_names = [FeatureName(colname=x, coltype="continous", colorigin=self.featureclassidentifier)
                         for x in feature_names]

        # D. tf-idf transf.
        # feature_matrix, feature_names = self._apply_tf_idf_normalization(featmatrix= feature_matrix,
        #                                                                  featurenames=feature_names)

        return feature_matrix, feature_names, authors, iids



    def apply_tf_idf_normalization(self, tf: bool, idf: bool, trainobject: typing.Optional['CodeStyloJoernFeatCl']):

        featurematrix = copy.deepcopy(self.featurematrix)
        colnames = copy.deepcopy(self.colnames)

        if tf:
            for x in colnames:
                x.settfidf(tf=tf, idf=idf)
            if trainobject is None:
                tfidftransformer = TfidfTransformer(norm="l2", use_idf=idf)
                featurematrix = tfidftransformer.fit_transform(featurematrix).astype(np.float32)
                if idf is False:
                    self.tfidftransformer = tfidftransformer
                else:
                    self.tfidftransformer2nd = tfidftransformer
            else:
                if idf is False:
                    featurematrix = trainobject.tfidftransformer.transform(featurematrix).astype(np.float32)
                else:
                    featurematrix = trainobject.tfidftransformer2nd.transform(featurematrix).astype(np.float32)

        return featurematrix, colnames



    def _print_verbose(self, inputdata: str) -> None:
        """
        Printing the progress of read_data_from_source if verbose is true and input is string (probably file path)
        :param inputdata: to print.
        """
        if self.verbose and isinstance(inputdata, str):
            print("Extracting... " + inputdata)




class ASTNodeFeature(CodeStyloJoernFeatCl):

    def __init__(self, inputdata: typing.Union[str, list], verbose: bool, bigrams: bool,
                 trainobject: typing.Optional['CodeStyloJoernFeatCl'], featureclassidentifier: str):


        self.bigrams: bool = bigrams
        self.verbose: bool = verbose
        super(ASTNodeFeature, self).__init__(inputdata=inputdata, verbose=verbose,
                                             trainobject=trainobject, featureclassidentifier=featureclassidentifier)


    def read_data_from_source(self, inputdata, trainobject):
        self._print_verbose(inputdata)
        self.featurematrix, self.colnames, self.authors, self.iids = self._extract_ast_nodes(inputdata=inputdata,
                                                                                             trainobject=trainobject,
                                                                                             bigram=self.bigrams)

        # Check and finish
        assert self.featurematrix.shape[1] == len(self.colnames)

        # we return all objects just for compability with parent class, in this way, we ensure that these fields
        # have to be created by read_data_from_source ;)
        return self.featurematrix, self.colnames, self.authors, self.iids


class ASTMaxPropertyFeature(CodeStyloJoernFeatCl):

    def __init__(self, inputdata: typing.Union[str, list], verbose: bool,
                 trainobject: typing.Optional['CodeStyloJoernFeatCl'],  featureclassidentifier: str):

        self.verbose: bool = verbose
        super(ASTMaxPropertyFeature, self).__init__(inputdata=inputdata, verbose=verbose,
                                                    trainobject=trainobject, featureclassidentifier=featureclassidentifier)


    # @Overwrite
    def read_data_from_source(self, inputdata, trainobject):

        self.featurematrix, self.colnames, self.authors, self.iids = self.__extract_max_depth_ast_node(inputdata)
        return self.featurematrix, self.colnames, self.authors, self.iids


    def __extract_max_depth_ast_node(self, inputdata):
        """
        Extracts the max depth of each ast node per file-programmer
        File format of json. For each author one line, each line has the pattern: <name> <id_id> <max-depth>
        Uses param: curfilepath: the path to the json file
        :return: features, authors, iids
        """

        if not isinstance(inputdata, str) and not isinstance(inputdata, list):
            raise Exception("Unvalid inputdata type")

        if isinstance(inputdata, str):
            with open(inputdata, "r") as f:
                ast_node_lines = [line.rstrip('\n') for line in f]
        else:
            ast_node_lines = [line.rstrip('\n') for line in inputdata]

        features = []
        authors = []
        iids = []

        for cl in range(len(ast_node_lines)):
            try:
                features.append(ast_node_lines[cl].split(" ")[2])
                authors.append(ast_node_lines[cl].split(" ")[0])
                iids.append(ast_node_lines[cl].split(" ")[1])
            except Exception as e:
                import sys
                print("Error in file in row:", cl, file=sys.stderr)
                print("{0}".format(e), file=sys.stderr)
                raise e


        # sort entries
        authors = np.array(authors)
        iids = np.array(iids)
        feature_matrix = sparse.csr_matrix(np.array(features, dtype=np.float32)).transpose()
        feature_matrix, iids, authors = utils_authorship.sortmatrix(matrix1=feature_matrix, matrix1ids=iids,
                                                                    matrix1authors=authors)

        # D. tf-idf transf.
        featurename: FeatureName = FeatureName(colname=self.featureclassidentifier, coltype="continous",
                                               colorigin=self.featureclassidentifier)
        # feature_matrix, feature_names = self._apply_tf_idf_normalization(featmatrix=feature_matrix,
        #                                                                  featurenames=[featurename])

        return feature_matrix, [featurename], authors, iids
