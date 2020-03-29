from featureextraction.CodeStyloJoernFeatCl import CodeStyloJoernFeatCl
from featureextraction.CodeStyloFeatures import CodeStyloFeatures
import numpy as np
import typing
import os


class CodeStyloLexemFeatures(CodeStyloJoernFeatCl):
    """
    This class creates lexem features.
    """

    def __init__(self, inputdata: typing.Union[str, list], verbose,
                 tf: bool, idf: bool,
                 trainobject: typing.Optional['CodeStyloLexemFeatures']) -> None:
        """
                Constructor for Lexem Features
        :param inputdata: Either string or list.
        If string, path to .dat file (lexems_features.dat).
        If list, then a list of already loaded features.
        :param verbose: set true if more process information should be printed
        :param tf: tf
        :param idf: idf
        :param trainobject: if this object is a test set object, pass code stylo lexem feature object from training set.
        """

        self.tf = tf
        self.idf = idf

        # call parent's init method that will call read_data_from_source
        if isinstance(inputdata, str):
            inputdata = os.path.join(inputdata, "lexems_features.dat")
        super(CodeStyloLexemFeatures, self).__init__(inputdata=inputdata, verbose=verbose, trainobject=trainobject,
                                                     featureclassidentifier="unigram")

    # @Overwrite
    def read_data_from_source(self, inputdata: typing.Union[str, list], trainobject: typing.Optional['CodeStyloLexemFeatures']):

        self._print_verbose(inputdata)
        self.featurematrix, self.colnames, self.authors, self.iids = self._extract_ast_nodes(inputdata=inputdata,
                                                                                             trainobject=trainobject,
                                                                                             bigram=False)
        assert self.featurematrix.shape[1] == len(self.colnames)
        return self.featurematrix, self.colnames, self.authors, self.iids


    # @Overwrite
    def gettfidffeatures(self, trainobject: typing.Optional['CodeStyloFeatures']):

        ctrainobj = None if trainobject is None else trainobject
        featmatrix, colnames = self.apply_tf_idf_normalization(tf=self.tf, idf=self.idf, trainobject=ctrainobj)
        return featmatrix, colnames


