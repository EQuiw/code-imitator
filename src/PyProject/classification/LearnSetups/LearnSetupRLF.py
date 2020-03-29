import numpy as np
from sklearn.ensemble import RandomForestClassifier
from featureextractionV2.StyloFeatures import StyloFeatures
from classification.LearnSetups.LearnSetup import LearnSetup

class LearnSetupRLF(LearnSetup):
    """
    In principle, similar to a struct, just keeps the references to the ML objects.
    """

    def __init__(self,
                 data_final_train: 'StyloFeatures',
                 data_final_test: 'StyloFeatures',
                 rlf: RandomForestClassifier):

        super(LearnSetupRLF, self).__init__(data_final_train=data_final_train,
                                             data_final_test=data_final_test,
                                             clf=rlf)


    # @Overwrite
    def predict_proba(self, feature_vec: np.ndarray, target_class: int):

        assert feature_vec.shape[0] == 1
        # assert feature_vec.shape[1] >= self.max_sel_feat_indices
        assert feature_vec.shape[1] == self.data_final_train.getfeaturematrix().shape[1]

        scoreprednew = self.clf.predict_proba(feature_vec[0, :])[0][target_class]
        return scoreprednew


    # @Overwrite
    def predict(self, feature_vec: np.ndarray):

        assert feature_vec.shape[0] == 1
        # assert feature_vec.shape[1] >= self.max_sel_feat_indices
        assert feature_vec.shape[1] == self.data_final_train.getfeaturematrix().shape[1]

        classprednew = self.clf.predict(feature_vec[0, :])[0]
        return classprednew