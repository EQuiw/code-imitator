import arff
from featureextractionV2.StyloFeaturesAbstract import StyloFeaturesAbstract
from featureextractionV2.FeatureNames import FeatureName
import numpy as np
from scipy import sparse
import utils_authorship
import typing


class StyloARFFFeatures(StyloFeaturesAbstract):
    """
    This class loads the ARFF features from the Java Implementation used by the Usenix paper.
    """

    def __init__(self, inputdata: str, removelog: bool) -> None:
        """
        Creates ARFF feature class
        :param inputdata: path to arff file
        :param removelog: if we should apply exp to each log-based feature.
        """

        # call parent's init method that will call read_data_from_source
        super(StyloARFFFeatures, self).__init__(inputdata=inputdata, tf=False, idf=False, trainobject=None)

        # ii) np.inf possible as log( some feature value is zero ) during feature extraction
        # I'll convert each log feature back by applying the inverse function
        if removelog is True:
            self._featurematrix, self._colnames = StyloARFFFeatures.convertlogback(self._featurematrix, self._colnames)


    def getunique_key(self) -> str:
        return "_".join(["arff"])

    # @Overwrite
    def read_data_from_source(self, inputdata: str, trainobject) -> typing.Tuple[sparse.csr_matrix, list, np.ndarray, np.ndarray]:

        # A. Load arff file obtained from java program
        dataset = StyloARFFFeatures.__import_arff_file(inputdata)

        # B. Convert the feature set to usable numpy array with float values
        # Two steps necessary: a) convert booleans to 0/1 b) remove label columns
        return StyloARFFFeatures.__extractfeaturematrix(dataset = dataset)

    @staticmethod
    def __import_arff_file(inputdata: str) -> typing.Dict[str, typing.Any]:
        """
        Reads the arff file via arff package
        :return: loaded arff features as dict
        """
        with open(inputdata) as fh:
            dataset = arff.load(fh)
        return dataset

    @staticmethod
    def __extractfeaturematrix(dataset: typing.Dict[str, typing.Any])\
                        -> typing.Tuple[sparse.csr_matrix, list, np.ndarray, np.ndarray]:
        """
        Extracts the feature matrix from the imported arff file.
        It converts the strings to floats, removes the author and iid column.
        :param dataset: the imported arff dataset, via import_arff_file method
        :return: the feature matrix, the column names, the separated author column, the separated iid column
        """
        # I. Extract features
        data = np.array(dataset['data'])
        column_names = np.array([x[0] for x in (dataset['attributes'])])
        iid = np.where(column_names == "instanceID")[0][0]
        author = np.where(column_names == "author")[0][0]
        authors = data[:, author]
        iids = data[:, iid]
        data = np.delete(data, [iid, author], axis=1)
        data = np.vectorize(utils_authorship.boolstr_to_floatstr)(data).astype(float)
        column_names = np.delete(column_names, [iid, author])

        # extract the types of the columns, convert them into a common format
        column_types = np.array([x[1] for x in (dataset['attributes'])])
        column_types = np.delete(column_types, [iid, author])
        column_types[np.where(column_types == "NUMERIC")[0]] = "continous"
        column_types[np.array([type(x) is list for x in column_types])] = "categorial"
        assert len((np.where((column_types != "categorial") & (column_types != "continous")))[0]) == 0


        # II. Sort features w.r.t. to iids
        feature_matrix, iids, authors = utils_authorship.sortmatrix(matrix1=sparse.csr_matrix(data), matrix1ids=iids,
                                                                    matrix1authors=authors)

        # Convert each feature to a FeatureName object to save its properties
        feature_names = [FeatureName(colname=x, coltype=y,
                                     colorigin="arff")
                         for x, y in zip(column_names, column_types)]

        return feature_matrix, feature_names, authors, iids


    @staticmethod
    def convertlogback(data: sparse.csr_matrix, column_names: typing.List[FeatureName]) \
            -> typing.Tuple[sparse.csr_matrix, typing.List[FeatureName]]:
        """
        Applies exp(.) to each feature column that starts with log.
        In this way, we reverse the logarithm scaling.
        :param data: the feature matrix
        :param column_names: the respective column names
        :return: data, column_names with exp(.) for all log values.
        """
        data = data.toarray()
        positive_indices = [x.colname.startswith("log") for x in column_names]
        for i, j in enumerate(positive_indices):
            if j is True:
                data[:, i] = np.exp(data[:, i])
                column_names[i].colname = column_names[i].colname.replace("log", "")
        return sparse.csr_matrix(data), column_names


