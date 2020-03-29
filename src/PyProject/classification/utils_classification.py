from featureextraction.CodeStyloMergedFeatures import CodeStyloMergedFeatures
from classification.LearnSetup import LearnSetup
from ConfigurationLearning.ConfigurationLearning import ConfigurationLearning
from classification import StratifiedKFoldProblemId, utils_learning

import pickle
import os
import numpy as np
import typing


def perform_standard_classification_for_split(features_merged: CodeStyloMergedFeatures,
                                              train_index: np.ndarray,
                                              test_index: np.ndarray,
                                              problem_id_test: str,
                                              configuration_learning: ConfigurationLearning,
                                              modelsavedir: typing.Optional[str],
                                              threshold_sel: typing.Union[int, float],
                                              learn_method: str,
                                              skf2: StratifiedKFoldProblemId,
                                              ) -> typing.Tuple[dict, LearnSetup]:
    """
    Convenience Function.
    Perform classification task with given train- test split where test set contains one challenge/problem.
    If modelsavedir is given, it will save the model, the accuracy value and the configuration file
    into this directory.
    :param features_merged: feature matrix object
    :param train_index: indices of training objects
    :param test_index: indices of test objects
    :param problem_id_test: the unique challenge/problem ID of the test set
    :param configuration_learning: config
    :param modelsavedir: directory where the model, accuracy value and config file will be saved. If none, nothing
    will be saved.
    :param threshold_sel: threshold for feature selection. Okay, here it is a little bit sloppy.
    If you chose a value smaller than 10, we use threshold_sel to select all features whose mutual info. score
    is larger than threshold; if threshold_sel is larger than 10, it must be an integer and then we
    take the X best features with X = threshold_sel. Look at __tfidf_feature_selection in utils_learning.py.

    :param learn_method: learning method, "RF", "SVM", "DNN", and "RNN" are supported.
    :param skf2: StratifiedKFoldProblemId object.
    :return: accuracy as dict (so that problem id from test set is directly available), and LearnSetup.
    (Both are also stored in modelsavedir, if modelsavedir is not None)
    """
    accuracies = {}

    # I. Load features
    trainfiles: CodeStyloMergedFeatures = features_merged[train_index]
    testfiles: CodeStyloMergedFeatures = features_merged[test_index]

    # II. Learning
    problemid_test_learn = "_".join(testfiles.iids[0].split("_")[0:2])
    assert problem_id_test == problemid_test_learn

    currentaccuracy, curtestlearnsetup = utils_learning.do_learn(train_obj=trainfiles,
                                                                 test_obj=testfiles,
                                                                 config_learning=configuration_learning,
                                                                 modelsavedir=modelsavedir,
                                                                 problemid_test=problemid_test_learn,
                                                                 threshold=threshold_sel,
                                                                 learn_method=learn_method,
                                                                 trainproblemlength=len(skf2.get_n_problems()[0]))

    # III. save accuracy dict, overwrite it in each iteration.
    accuracies[problemid_test_learn] = currentaccuracy
    if modelsavedir is not None:
        accfile = os.path.join(modelsavedir,
                               "acc_" + learn_method + "_" + str(threshold_sel) + "__" + problemid_test_learn + ".pck")
        pickle.dump(accuracies, file=open(accfile, 'wb'))

    # IV. Save configuration in a readable text file (use str method of config class), added after Version 0.2
    if modelsavedir is not None:
        with open(os.path.join(modelsavedir, "configuration_" + str(threshold_sel) + "__" + problemid_test_learn + ".txt"),
                  "w") as text_file:
            print(str(configuration_learning), file=text_file)

    return accuracies, curtestlearnsetup