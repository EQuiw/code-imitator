import typing

import numpy as np

from ConfigurationLearning.ConfigurationLearning import ConfigurationLearning

from featureextractionV2.StyloFeatures import StyloFeatures
from featureextractionV2.StyloFeaturesProxy import StyloFeaturesProxy
from featureextractionV2.StyloARFFFeatures import StyloARFFFeatures
from featureextractionV2.StyloUnigramFeatures import StyloUnigramFeatures
from featureextractionV2.ClangTypes.StyloClangFeaturesGenerator import StyloClangFeaturesGenerator
from featureextractionV2.ClangTypes.StyloLexemFeaturesGenerator import StyloLexemFeatureGenerator



def extract_train_test_arff(config_learning: ConfigurationLearning) -> StyloFeatures:
    # I. Get Arff features from java implementation
    arffmatrix_train = StyloARFFFeatures(inputdata=config_learning.arffile, removelog=True)
    return arffmatrix_train


def extract_train_test_unigram(config_learning: ConfigurationLearning, tf: bool, idf: bool,
                               ngram_range: tuple) -> StyloFeatures:
    # II. Get WordUnigramTF features
    if config_learning.use_lexems is not True:
        unigrammmatrix_train = StyloUnigramFeatures(inputdata=config_learning.datasetpath,
                                                    nocodesperprogrammer=config_learning.probsperprogrammer,
                                                    noprogrammers=config_learning.no_of_programmers,
                                                    binary=False, tf=tf, idf=idf,
                                                    ngram_range=ngram_range, stop_words=config_learning.stop_words,
                                                    trainobject=None)
    else:
        unigrammmatrix_train = StyloLexemFeatureGenerator(inputdata=config_learning.joerndats,
                                                          trainobject=None, tf=True, idf=False,
                                                          verbose=True).styloobject
    return unigrammmatrix_train


def extract_train_test_clang(config_learning: ConfigurationLearning) -> typing.List[StyloFeatures]:
    """
    III. Get joern/clang features
    It returns a list of different clang-based feature objects, as we have a feature object for AST Nodes,
    one for AST Node Bigrams, and so on... They are not linked to each other,
    look at 'extract_link_train_test_usenix_features' how to do that (quite simple).
    """
    clangmatrices_train = StyloClangFeaturesGenerator(inputdata=config_learning.joerndats,
                                                    get_lexical_features=config_learning.use_lexical_features,
                                                    verbose=True,
                                                    trainobject=None)
    return clangmatrices_train.styloobjects_list



def extract_link_train_test_usenix_features(config_learning: ConfigurationLearning) -> StyloFeaturesProxy:
    """
    Creates a feature object that can be directly used. It contains all features from Caliskan et al., USENIX
    *that we used*. It does *not* contain the ARFF feature set, and thus NO layout features.
    The individual feature objects are loaded and linked to each other.
    :param config_learning: configuration
    :return: StyloFeatures object.
    """

    # load feature sets
    unigrammmatrix_train = extract_train_test_unigram(config_learning=config_learning,
                                                      tf=True, idf=False, ngram_range=(1,1))
    clangmatrices_train = extract_train_test_clang(config_learning=config_learning)

    # now link all elements to form one feature object; we use a list to extract the clangmatrices_train list.
    styloelements: typing.List[StyloFeatures] = [unigrammmatrix_train, *clangmatrices_train]
    for ix in range(1, len(styloelements)):
        styloelements[ix-1].setnextstylo(styloelements[ix])

    features_merged = StyloFeaturesProxy(codestyloreference=styloelements[0])
    return features_merged



def extract_link_train_test_usenix_all(config_learning: ConfigurationLearning) -> StyloFeaturesProxy:
    """
    Creates a feature object that can be directly used. It contains all features from Caliskan et al., USENIX.
    It *also* contains the ARFF feature set, and thus layout features.
    The individual feature objects are loaded and linked to each other.
    :param config_learning: configuration
    :return: StyloFeatures object.
    """
    # load all feature sets
    arffmatrix_train = extract_train_test_arff(config_learning=config_learning)
    unigrammmatrix_train = extract_train_test_unigram(config_learning=config_learning,
                                                      tf=True, idf=False, ngram_range=(1,1))
    clangmatrices_train = extract_train_test_clang(config_learning=config_learning)

    # aggregate into one list
    styloelements: typing.List[StyloFeatures] = [arffmatrix_train, unigrammmatrix_train, *clangmatrices_train]

    # now link all elements to form one feature object
    for ix in range(1, len(styloelements)):
        styloelements[ix - 1].setnextstylo(styloelements[ix])

    features_merged = StyloFeaturesProxy(codestyloreference=styloelements[0])

    # perform a short check
    def check(unigrammmatrix, joernmatrix, arffmatrix):
        # Check that rows correspond to same file-author pair, 'astype' only used so that type hints do not show an error
        assert np.sum((unigrammmatrix.getiids() != arffmatrix.getiids()).astype(np.bool)) == 0
        assert np.sum((unigrammmatrix.getiids() != joernmatrix.getiids()).astype(np.bool)) == 0
        assert np.sum((unigrammmatrix.getauthors() != arffmatrix.getauthors()).astype(np.bool)) == 0
        assert np.sum((unigrammmatrix.getauthors() != joernmatrix.getauthors()).astype(np.bool)) == 0
        # had some trouble with this column/feature for 2 authors, just check it...
        colnames_simple = np.array([x.colname for x in joernmatrix.getcolnamesraw()])  # TODO remove me.
        print(np.max(joernmatrix.getfeaturematrix().toarray()[:, np.where(colnames_simple == "max_depth_ast_node")[0]]))
    check(unigrammmatrix_train, clangmatrices_train[0], arffmatrix_train)

    return features_merged
