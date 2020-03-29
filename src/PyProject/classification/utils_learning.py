"""
File: Contains all methods that we use to classify authors for a given feature matrix.
"""
from sklearn import svm
from sklearn.ensemble import RandomForestClassifier
from sklearn import preprocessing
import sklearn.feature_selection
from sklearn.model_selection import ParameterGrid
from sklearn.base import clone
import numpy as np
from classification import StratifiedKFoldProblemId

import typing
import pickle
import os

import classification.LearnSetup
import classification.LearnSetupRLF
import classification.LearnSetupSVM
from ConfigurationLearning.ConfigurationLearning import ConfigurationLearning
from ConfigurationLearning.ConfigurationLearningRNN import ConfigurationLearningRNN


from featureextraction.CodeStyloMergedFeatures import CodeStyloMergedFeatures


def __tfidf_feature_selection(train_obj, test_obj, config_learning, threshold):
    """
    Preprocessing Steps.
    1. Tf-(idf) transformation
    2. Feature Selection
    :param train_obj:
    :param test_obj:
    :param config_learning:
    :param threshold:
    :return:
    """

    train_obj.update_tfidffeatures(trainobject=None)
    test_obj.update_tfidffeatures(trainobject=train_obj)

    featsel = sklearn.feature_selection.mutual_info_classif(X=train_obj.featurematrix, y=train_obj.labels,
                                                            discrete_features="auto",
                                                            copy=True, random_state=17)

    # TODO we should refactor this to avoid the double usage of threshold.
    if threshold <= 10:
        sel_feat_indices = np.where(featsel > threshold)[0]
    else:
        sel_feat_indices = (-featsel).argsort()[:threshold]
    print("Length of features:", len(sel_feat_indices))

    train_obj.update_columns(index=sel_feat_indices, trainobject=None)
    test_obj.update_columns(index=None, trainobject=train_obj)

    return train_obj, test_obj


def do_local_train_test_split(train_obj, trainproblemlength, config_learning, threshold):

    skflocal = StratifiedKFoldProblemId.StratifiedKFoldProblemId(iids=train_obj.iids, n_splits=3,
                                                                 shuffle=True, random_state=411,
                                                                 nocodesperprogrammer=trainproblemlength)

    listoftraintestsplits = []
    for train_index, test_index in skflocal.split(None, None):
        trainfiles: CodeStyloMergedFeatures = train_obj[train_index]
        testfiles: CodeStyloMergedFeatures = train_obj[test_index]

        trainfiles, testfiles = __tfidf_feature_selection(train_obj=trainfiles, test_obj=testfiles,
                                                          config_learning=config_learning, threshold=threshold)

        listoftraintestsplits.append([trainfiles.featurematrix, testfiles.featurematrix, trainfiles.labels, testfiles.labels])

    return listoftraintestsplits



def __save_learnsetup(modelsavedir: str, curproblem: str, learn_method: str, threshold: float,
                      testlearnsetup: classification.LearnSetup):
    """
    Small helper function to save the testlearnsetup to disk.
    """

    if modelsavedir is not None:
        modelfile = os.path.join(modelsavedir, "model_" + curproblem  + "_" + learn_method + "_" + str(threshold) + ".pck")
        pickle.dump(testlearnsetup, file=open(modelfile, 'wb'))


def __save_keras_model(modelsavedir: str, curproblem: str, learn_method: str, threshold: float,
                      keras_model, keras_hist):
    if modelsavedir is not None:
        kerasmodelpath = os.path.join(modelsavedir, "keras_model_" + curproblem
                                      + "_" + learn_method + "_" + str(threshold) + ".pck")
        keras_model.model.save(kerasmodelpath)
        if keras_hist is not None:
            histfile = os.path.join(modelsavedir, "keras_model_hist_" +
                                    curproblem + "_" + learn_method + "_" + str(threshold) + ".pck")
            pickle.dump(keras_hist, file=open(histfile, 'wb'))


def do_learn(train_obj: CodeStyloMergedFeatures,
             test_obj: CodeStyloMergedFeatures,
             config_learning: typing.Union[ConfigurationLearning, ConfigurationLearningRNN],
             modelsavedir: typing.Optional[str],
             problemid_test: str,
             threshold:float=1.75, learn_method:str="RF",
             trainproblemlength: int = None):
    """
    Learn and evaluate. Just it.
    :param train_obj: train samples
    :param test_obj: test samples
    :param config_learning: specifying the parameters for feature extraction
    :param modelsavedir: either None, then the model will not be saved, or path to location where model can be stored.
    :param problemid_test: specifies the id of the current problem that test_obj represents.
    :param threshold: a threshold for feature selection
    :param learn_method: RF, SVM, DNN
    :param trainproblemlength: if None, we use a 2-fold CV for grid search, otherwise we use a 2-fold problem-oriented CV.
    :return: acc. and estimator
    """
    listoftraintestsplits = do_local_train_test_split(train_obj=train_obj, config_learning=config_learning,
                              threshold=threshold, trainproblemlength=trainproblemlength)

    print(">Whole train set: TRAIN:", train_obj.featurematrix.shape[0], "TEST:", test_obj.featurematrix.shape[0])
    train_obj, test_obj = __tfidf_feature_selection(train_obj=train_obj, test_obj=test_obj,
                                                    config_learning=config_learning,
                                                                             threshold=threshold)

    return learn_with_cv(train_obj=train_obj, test_obj=test_obj, config_learning=config_learning,
               modelsavedir=modelsavedir, problemid_test=problemid_test,
               threshold=threshold, learn_method=learn_method,
               listoftraintestsplits=listoftraintestsplits)


def learn_with_cv(train_obj: CodeStyloMergedFeatures,
                  test_obj: CodeStyloMergedFeatures,
                  config_learning: typing.Union[ConfigurationLearning, ConfigurationLearningRNN],
               modelsavedir: typing.Optional[str],
               problemid_test: str,
               threshold: float, learn_method: str,
               listoftraintestsplits: list
               ):

    x_train, x_test = train_obj.featurematrix, test_obj.featurematrix
    y_train, y_test = train_obj.labels, test_obj.labels

    # *** Learn Method Random Forest ***
    if learn_method == "RF":
        acc, clf = random_forest_learning(x_train=x_train, y_train=y_train, x_test=x_test, y_test=y_test,
                                          listoftraintestsplits=listoftraintestsplits,
                                          config_learning = config_learning)
        testlearnsetup = classification.LearnSetupRLF.LearnSetupRLF(data_final_train=train_obj, data_final_test=test_obj,
                                                              rlf=clf)
        __save_learnsetup(modelsavedir=modelsavedir, curproblem=problemid_test, learn_method=learn_method,
                          threshold=threshold, testlearnsetup=testlearnsetup)

    # *** Linear SVM ***
    elif learn_method == "SVM":
        acc, clf, sc = svm_learning(x_train=x_train, y_train=y_train, x_test=x_test, y_test=y_test,
                                listoftraintestsplits=listoftraintestsplits, config_learning=config_learning)
        testlearnsetup = classification.LearnSetupSVM.LearnSetupSVM(data_final_train=train_obj,
                                                                    data_final_test=test_obj,
                                                                    clf=clf,
                                                                    stdscaler=sc)
        __save_learnsetup(modelsavedir=modelsavedir, curproblem=problemid_test, learn_method=learn_method,
                          threshold=threshold, testlearnsetup=testlearnsetup)

    # *** Fully Connected Neural Network ***
    elif learn_method == "DNN":

        from classification.LearnSetupDNN import LearnSetupDNN
        import classification.utils_learning_dnn as utils_learning_dnn

        acc, clf, sc = utils_learning_dnn.neural_network_learning(x_train=x_train, y_train=y_train,
                                                                  x_test=x_test, y_test=y_test,
                                                                  listoftraintestsplits=listoftraintestsplits,
                                                                  config_learning=config_learning,
                                                                  num_classes=len(test_obj.iids))

        testlearnsetup = LearnSetupDNN(data_final_train=train_obj, data_final_test=test_obj,
                                                              clf=None, stdscaler=sc)
        __save_learnsetup(modelsavedir=modelsavedir, curproblem=problemid_test, learn_method=learn_method,
                          threshold=threshold, testlearnsetup=testlearnsetup)
        # In addition, we need to save the Keras model, as it cannot be pickled.
        __save_keras_model(modelsavedir=modelsavedir, curproblem=problemid_test, learn_method=learn_method,
                          threshold=threshold, keras_model=clf, keras_hist=None)

    # *** Learn RNN (in our case, LSTM) ***
    elif learn_method == "RNN":
        assert isinstance(config_learning, ConfigurationLearningRNN)

        from classification.LearnSetupRNNRF import LearnSetupRNNRF
        import classification.utils_learning_rnn as utils_learning_rnn

        dnn_acc, clf, sc, rlf, rf_acc, rnnhist = utils_learning_rnn.r_neural_network_learning(x_train=x_train,
                                                                                              y_train=y_train,
                                                                                              x_test=x_test, y_test=y_test,
                                                                                              listoftraintestsplits=listoftraintestsplits,
                                                                                              config_learning=config_learning,
                                                                                              num_classes=len(test_obj.iids)
                                                                                              )

        testlearnsetup = LearnSetupRNNRF(data_final_train=train_obj, data_final_test=test_obj,
                                                              clf=None, rlf=rlf, stdscaler=sc)
        testlearnsetup.use_rlf = False if config_learning.cv_use_rnn_output is True else True

        __save_learnsetup(modelsavedir=modelsavedir, curproblem=problemid_test, learn_method=learn_method,
                          threshold=threshold, testlearnsetup=testlearnsetup)
        # In addition, we need to save the Keras model, as it cannot be pickled.
        __save_keras_model(modelsavedir=modelsavedir, curproblem=problemid_test, learn_method=learn_method,
                          threshold=threshold, keras_model=clf, keras_hist=rnnhist)
        acc = dnn_acc if config_learning.cv_use_rnn_output is True else rf_acc

    else:
        raise Exception("Choose correct learning method")


    return acc, testlearnsetup



def customized_grid_search(param_grid: dict, clf, listoftraintestsplits):
    """
    Customized grid search, that avoids problem that we have CodeStyloObjects, not matrices; where each sub-object
    needs own e.g. tf-idf.
    TODO replace by scikit grid search, and pass iterable with train-test-splits to cv argument.
    """

    accuracy_per_param: list = []
    params_list: list = [params for params in ParameterGrid(param_grid)]
    for params in params_list:
        cv_results = []
        #print(params)

        for x_train_cv, x_test_cv, y_train_cv, y_test_cv in listoftraintestsplits:
            #print(x_train_cv.shape)

            clf_copy = clone(clf)
            clf_copy.set_params(**params)
            clf_copy.fit(x_train_cv, y_train_cv)
            ypred_cv = clf_copy.predict(x_test_cv)
            cmps: np.ndarray = (y_test_cv == ypred_cv)
            theaccuracy: np.float64 = np.sum(cmps) / np.shape(ypred_cv)[0]
            cv_results.append(theaccuracy)
        print("{1} (mean:{2}) by {0}".format(params, cv_results, np.mean(np.array(cv_results))))
        accuracy_per_param.append((np.mean(np.array(cv_results)), np.sqrt(np.var(np.array(cv_results)))))

    best_param_index: int = np.argmax(np.array([x[0] for x in accuracy_per_param]))
    print("Best param:", params_list[best_param_index], " with ", accuracy_per_param[best_param_index])

    return params_list[best_param_index], accuracy_per_param[best_param_index]


def random_forest_learning(x_train, y_train, x_test, y_test, listoftraintestsplits, config_learning):

    if config_learning.hyperparameters is None:
        param_grid = {"n_estimators": [204, 250, 300, 350],
                  "max_features": [0.1, 0.2, 0.3, 0.4, 0.5, "log2", "sqrt"],
                  "max_depth": [10, 15, 20, 25, 30, 40, 50], #50
                  "min_samples_leaf": [2, 4, 6, 8, 10, 12, 14],
                  }
    else:
        param_grid = config_learning.hyperparameters


    best_params, best_params_acc = customized_grid_search(param_grid=param_grid,
                                                          clf = RandomForestClassifier(random_state=31,
                                                          n_jobs=config_learning.noofparallelthreads),
                                                          listoftraintestsplits=listoftraintestsplits)

    # now train on final object
    rlf_best = RandomForestClassifier(random_state=31, n_jobs=config_learning.noofparallelthreads)
    rlf_best.set_params(**best_params)
    rlf_best.fit(x_train, y_train)
    ypred = rlf_best.predict(x_test)
    cmps: np.ndarray = (y_test == ypred)
    theaccuracy: np.float64 = np.sum(cmps) / np.shape(ypred)[0]

    print("RF-Acc:", theaccuracy)

    return theaccuracy, rlf_best



def svm_learning(x_train, y_train, x_test, y_test, listoftraintestsplits, config_learning):

    # A. Preprocessing
    for i in range(len(listoftraintestsplits)):

        sc = preprocessing.StandardScaler().fit(listoftraintestsplits[i][0].todense())
        listoftraintestsplits[i][0] = sc.transform(listoftraintestsplits[i][0].todense())
        listoftraintestsplits[i][1] = sc.transform(listoftraintestsplits[i][1].todense())

    sc = preprocessing.StandardScaler().fit(x_train.todense())
    x_train = sc.transform(x_train.todense())
    x_test = sc.transform(x_test.todense())

    # B. Grid search to get best params
    if config_learning.hyperparameters is None:
        param_grid = {"C": [0.0001, 0.001, 0.01, 0.1, 1, 10, 100, 1000, 10000]}
    else:
        param_grid = config_learning.hyperparameters

    # use cv splits to find best params
    best_params, best_params_acc = customized_grid_search(param_grid=param_grid,
                                                          clf=svm.LinearSVC(random_state=31),
                                                          listoftraintestsplits=listoftraintestsplits)

    # now train on final object
    clf_best = svm.LinearSVC(random_state=31)
    clf_best.set_params(**best_params)
    clf_best.fit(x_train, y_train)
    ypred = clf_best.predict(x_test)
    cmps: np.ndarray = (y_test == ypred)
    theaccuracy: np.float64 = np.sum(cmps) / np.shape(ypred)[0]

    print("SVM-Acc:", theaccuracy)
    return theaccuracy, clf_best, sc

