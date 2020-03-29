from featureextractionV2.StyloFeaturesAbstract import StyloFeaturesAbstract
from featureextractionV2.StyloFeatures import StyloFeatures
import typing
from abc import ABC


class StyloClangFeaturesAbstract(StyloFeaturesAbstract, ABC):


    def __init__(self, inputdata: typing.Union[str, list],
                 verbose:bool,
                 trainobject: typing.Optional['StyloClangFeaturesAbstract'],
                 featureclassidentifier: str, tf: bool, idf: bool):
        """
        Class that represents features from clang.

        :param inputdata: string with path to .dat file or list with features
        :param verbose: print more progress information
        :param trainobject: training object
        :param featureclassidentifier: string with feature class, e.g. ast_node_bigrams
        :param tf: tf transformation
        :param idf: idf for tf-idf
        """

        self.verbose: bool = verbose
        self.featureclassidentifier: str = featureclassidentifier


        super(StyloClangFeaturesAbstract, self).__init__(inputdata=inputdata,
                                                         tf=tf, idf=idf, trainobject=trainobject)


    def _print_verbose(self, inputdata: str) -> None:
        """
        Printing the progress of read_data_from_source if verbose is true and input is string (probably file path)
        :param inputdata: to print.
        """
        if self.verbose and isinstance(inputdata, str):
            print("Extracting... " + inputdata)


