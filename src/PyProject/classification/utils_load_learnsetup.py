### Utils for loading the previously saved LearnSetup ###
# While RLF and SVM is really easy (we just need to load the pickle file),
# the DNN with keras is just a little bit more complicated. Here, we need to
# load the LearnSetup and the keras model and then combine them again.
import classification.LearnSetups.LearnSetup
import os
import pickle
import typing


def load_learnsetup(learnmodelspath: str, feature_method: str, learn_method: str, problem_id: str, threshold_sel: typing.Union[int, float])\
        -> classification.LearnSetups.LearnSetup:
    """
        Loads the learn setup.
    :param learnmodelspath: path where models are located
    :param feature_method: the used feature method
    :param learn_method: the used learn method
    :param problem_id: the id of current test set
    :param threshold_sel: used threshold
    :return: LearnSetup object
    """

    dirwithmodel = feature_method + "_" + learn_method
    modelfile = os.path.join(learnmodelspath, dirwithmodel,
                             "model_" + problem_id + "_" + learn_method + "_" +
                             str(threshold_sel) + ".pck")

    if learn_method == "SVM" or learn_method == "RF":
        with open(modelfile, "rb") as curf:
            testlearnsetup = pickle.load(curf)

    elif learn_method == "DNN" or learn_method == "RNN":
        with open(modelfile, "rb") as curf:
            testlearnsetup = pickle.load(curf)

        import keras.models
        kerasmodelpath = os.path.join(learnmodelspath, dirwithmodel,
                                      "keras_model_" + problem_id + "_" + learn_method
                                      + "_" + str(threshold_sel) + ".pck")
        dnnmodel = keras.models.load_model(filepath=kerasmodelpath)

        if learn_method == "DNN":
            testlearnsetup.clf = dnnmodel
        else:
            testlearnsetup.add_rnn(clf=dnnmodel)

    else:
        raise Exception("Unsupported chosen learn setup")

    return testlearnsetup









