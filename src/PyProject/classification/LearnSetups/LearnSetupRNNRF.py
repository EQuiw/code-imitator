import numpy as np
from featureextractionV2.StyloFeatures import StyloFeatures
from classification.LearnSetups.LearnSetup import LearnSetup
from sklearn import preprocessing
from sklearn.ensemble import RandomForestClassifier
from keras import backend as K
import keras


class LearnSetupRNNRF(LearnSetup):
    """
    In principle, similar to a struct, just keeps the references to the ML objects.
    """

    def __init__(self,
                 data_final_train: 'StyloFeatures',
                 data_final_test: 'StyloFeatures',
                 clf: keras.models.Sequential,
                 rlf: RandomForestClassifier,
                 stdscaler: preprocessing.StandardScaler):

        super(LearnSetupRNNRF, self).__init__(data_final_train=data_final_train,
                                             data_final_test=data_final_test,
                                             clf=clf)
        self.stdscaler = stdscaler
        self.rlf = rlf
        self.get_deep_features = None

        # we can decide if we want to use the clf output, or the subsequent rlf output.
        self.use_rlf = True


    def add_rnn(self, clf: keras.models.Sequential):
        """
        Adds the KerasClassifier's model afterwards, as it cannot be directly pickled.
        """
        assert self.clf is None

        self.clf = clf
        self.get_deep_features = K.function([self.clf.layers[0].input, K.learning_phase()],
                                       [self.clf.layers[-3].output])


    def __preprocess(self, feature_vec: np.ndarray):
        """
        Preprocess feature vector such that it has the right shape for RNN, then get its deep representation
        that can be feeded into the Random Forest Classifier.
        """
        assert self.clf is not None and self.get_deep_features is not None
        assert len(feature_vec.shape) == 2
        assert feature_vec.shape[0] == 1
        assert feature_vec.shape[1] == self.data_final_train.getfeaturematrix().shape[1]

        if self.stdscaler is not None:
            featvec = self.stdscaler.transform(feature_vec[0, :].todense())
        else:
            featvec = np.array(feature_vec[0, :].todense())

        featvec = featvec.reshape(featvec.shape[0], 1, featvec.shape[1])
        featvec_deep = self.get_deep_features([featvec, 0])[0]
        return featvec_deep, featvec


    # @Overwrite
    def predict_proba(self, feature_vec: np.ndarray, target_class: int):

        featvec_deep, featvec = self.__preprocess(feature_vec=feature_vec)
        if self.use_rlf:
            scoreprednew = self.rlf.predict_proba(featvec_deep)[0][target_class]
        else:
            scoreprednew = self.clf.predict_proba(featvec)[0][target_class]

        return scoreprednew


    # @Overwrite
    def predict(self, feature_vec: np.ndarray):

        featvec_deep, featvec = self.__preprocess(feature_vec=feature_vec)
        if self.use_rlf:
            classprednew = self.rlf.predict(featvec_deep)[0]
        else:
            classprednew = np.argmax(self.clf.predict(featvec)[0])

        return classprednew