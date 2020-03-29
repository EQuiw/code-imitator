import numpy as np
from featureextractionV2.StyloFeatures import StyloFeatures
from classification.LearnSetups.LearnSetup import LearnSetup
from sklearn import preprocessing
from keras.wrappers.scikit_learn import KerasClassifier
# from keras.utils.np_utils import to_categorical

class LearnSetupDNN(LearnSetup):
    """
    In principle, similar to a struct, just keeps the references to the ML objects.
    """

    def __init__(self,
                 data_final_train: 'StyloFeatures',
                 data_final_test: 'StyloFeatures',
                 clf: KerasClassifier,
                 stdscaler: preprocessing.StandardScaler):

        super(LearnSetupDNN, self).__init__(data_final_train=data_final_train,
                                             data_final_test=data_final_test,
                                             clf=clf)
        self.stdscaler = stdscaler


    # @Overwrite
    def predict_proba(self, feature_vec: np.ndarray, target_class: int):

        assert self.clf is not None
        assert feature_vec.shape[0] == 1
        assert feature_vec.shape[1] == self.data_final_train.getfeaturematrix().shape[1]

        featvec = self.stdscaler.transform(feature_vec[0, :].todense())
        scoreprednew = self.clf.predict_proba(featvec)[0][target_class]
        return scoreprednew


    # @Overwrite
    def predict(self, feature_vec: np.ndarray):

        assert self.clf is not None
        assert feature_vec.shape[0] == 1
        assert feature_vec.shape[1] == self.data_final_train.getfeaturematrix().shape[1]

        featvec = self.stdscaler.transform(feature_vec[0, :].todense())
        classprednew = np.argmax(self.clf.predict(featvec)[0])
        return classprednew