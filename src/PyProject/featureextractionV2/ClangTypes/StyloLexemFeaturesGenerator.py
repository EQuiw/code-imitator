from featureextractionV2.ClangTypes.StyloASTNodeFeature import StyloASTNodeFeature
from featureextractionV2.StyloFeaturesAbstract import StyloFeaturesAbstract
from featureextractionV2.StyloFeatures import StyloFeatures
from featureextractionV2.ClangTypes.StyloClangFeaturesAbstract import StyloClangFeaturesAbstract
import typing
import os


class StyloLexemFeatureGenerator:
    """
    This class creates lexem features.
    """

    def __init__(self, inputdata: typing.Union[str, list], verbose,
                 tf: bool, idf: bool,
                 trainobject: typing.Optional['StyloFeaturesAbstract']) -> None:
        """
        Constructor for Lexem Features
        :param inputdata: Either string or list.
        If string, path to .dat file (lexems_features.dat).
        If list, then a list of already loaded features.
        :param verbose: set true if more process information should be printed
        :param tf: tf
        :param idf: idf
        :param trainobject: At test-time, pass stylo lexem feature object from training set.
        """

        # call parent's init method that will call read_data_from_source
        if isinstance(inputdata, str):
            inputdata = os.path.join(inputdata, "lexems_features.dat")

        self.styloobject: StyloASTNodeFeature = StyloASTNodeFeature(inputdata=inputdata, verbose=verbose,
                                                                    trainobject=trainobject,
                                                                    featureclassidentifier="unigram", tf=tf, idf=idf,
                                                                    bigrams=False)

        self.lasttrainobj = trainobject


    @staticmethod
    def check_unique_keys_for_trainobject_comparison(trainobj: StyloFeatures):
        """
        Checks if train object has a matching unique key / feature class identifier that corresponds to this generator.
        This method is only used by evasion algorithms to check if a training object demands that we create
        clang objects from Caliskan et al.'s approach.
        :return: true/false
        """

        keys = ["unigram"]
        if isinstance(trainobj, StyloClangFeaturesAbstract):
            for key in keys:
                if trainobj.getunique_key().startswith(key):
                    return True
        return False
