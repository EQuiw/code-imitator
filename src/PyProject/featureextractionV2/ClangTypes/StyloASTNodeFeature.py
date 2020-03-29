import typing

from featureextractionV2.ClangTypes.StyloClangFeaturesAbstract import StyloClangFeaturesAbstract

from featureextractionV2.FeatureNames import FeatureName
from sklearn.feature_extraction import DictVectorizer
import numpy as np
from scipy import sparse
import utils_authorship
import json



class StyloASTNodeFeature(StyloClangFeaturesAbstract):
    """
    Represents AST-node-like features.
    """

    def __init__(self,
                 inputdata: typing.Union[str, list],
                 verbose:bool,
                 trainobject: typing.Optional['StyloClangFeaturesAbstract'],
                 featureclassidentifier: str, tf: bool, idf: bool,
                 bigrams: bool
                 ):

        # save the vectorizer of this object, we can use it later to load test data
        self.cvectorizer = None  # type: typing.Optional[DictVectorizer]
        self.bigrams: bool = bigrams

        super(StyloASTNodeFeature, self).__init__(inputdata=inputdata, verbose=verbose, tf=tf, idf=idf,
                                             trainobject=trainobject, featureclassidentifier=featureclassidentifier)


    def getunique_key(self) -> str:
        return "_".join([self.featureclassidentifier, str(self.bigrams), str(self.tf), str(self.idf)])


    def read_data_from_source(self, inputdata, trainobject):
        self._print_verbose(inputdata)
        self._featurematrix, self._colnames, self._authors, self._iids = self._extract_ast_nodes(inputdata=inputdata,
                                                                                             trainobject=trainobject,
                                                                                             bigram=self.bigrams)

        # Check and finish
        assert self._featurematrix.shape[1] == len(self._colnames)

        # we return all objects just for compability with parent class, in this way, we ensure that these fields
        # have to be created by read_data_from_source ;)
        return self._featurematrix, self._colnames, self._authors, self._iids




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


