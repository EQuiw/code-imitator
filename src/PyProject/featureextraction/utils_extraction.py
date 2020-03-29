import typing

import numpy as np

from featureextraction.CodeStyloARFFFeatures import CodeStyloARFFFeatures
from featureextraction.CodeStyloJoernFeatures import CodeStyloJoernFeatures
from featureextraction.CodeStyloUnigramFeatures import CodeStyloUnigramFeatures
from featureextraction.CodeStyloLexemFeatures import CodeStyloLexemFeatures
from featureextraction.CodeStyloFeatures import CodeStyloFeatures
from ConfigurationLearning.ConfigurationLearning import ConfigurationLearning


def extract_train_test_features(config_learning: ConfigurationLearning,
                                ) -> typing.List[CodeStyloFeatures]:
    """
    A simple helper function that loads the feature matrix
    :param config_learning: a config object that sets the various learning settings
    :return: a list of code stylo objects
    """
    # I. Get Arff features from java implementation
    arffmatrix_train = CodeStyloARFFFeatures(inputdata=config_learning.arffile, removelog=True)

    # II. Get WordUnigramTF features
    if config_learning.use_lexems is not True:
        unigrammmatrix_train = CodeStyloUnigramFeatures(inputdata=config_learning.datasetpath,
                                                        nocodesperprogrammer=config_learning.probsperprogrammer,
                                                      noprogrammers=config_learning.no_of_programmers,
                                                        binary=False, tf=True, idf=False,
                                                      ngram_range=(1,1), stop_words=config_learning.stop_words,
                                                        trainobject=None)
    else:
        unigrammmatrix_train = CodeStyloLexemFeatures(inputdata=config_learning.joerndats,
                                                      trainobject=None, tf=True, idf=False, verbose=True)

    # III. Get joern features
    joernmatrix_train = CodeStyloJoernFeatures(inputdata=config_learning.joerndats,
                                               get_lexical_features=config_learning.use_lexical_features, verbose=True,
                                               tf=True, tfidf=True, trainobject=None)


    def check(unigrammmatrix, joernmatrix, arffmatrix):
        # Check that rows correspond to same file-author pair, 'astype' only used so that type hints do not show an error
        assert np.sum((unigrammmatrix.iids != arffmatrix.iids).astype(np.bool)) == 0
        assert np.sum((unigrammmatrix.iids != joernmatrix.iids).astype(np.bool)) == 0
        assert np.sum((unigrammmatrix.authors != arffmatrix.authors).astype(np.bool)) == 0
        assert np.sum((unigrammmatrix.authors != joernmatrix.authors).astype(np.bool)) == 0
        # had some trouble with this column/feature for 2 authors, just check it...
        colnames_simple = np.array([x.colname for x in joernmatrix.colnames])
        print(np.max(joernmatrix.featurematrix.toarray()[:, np.where(colnames_simple == "max_depth_ast_node")[0]]))

    check(unigrammmatrix_train, joernmatrix_train, arffmatrix_train)

    return [arffmatrix_train, unigrammmatrix_train, joernmatrix_train]



