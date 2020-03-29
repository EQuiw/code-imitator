import numpy as np
from featureextractionV2.StyloFeatures import StyloFeatures
from abc import ABC, abstractmethod


class LearnSetup(ABC):
    """
    In principle, similar to a struct, just keeps the references to the ML objects.
    """

    def __init__(self,
                 data_final_train: 'StyloFeatures',
                 data_final_test: 'StyloFeatures',
                 clf): #typing.Union[RandomForestClassifier, svm.SVC, KerasClassifier]
        self.data_final_test = data_final_test
        self.data_final_train = data_final_train
        self.clf = clf
        # self.sel_feat_indices = sel_feat_indices
        # self.max_sel_feat_indices = np.max(self.sel_feat_indices)


    @abstractmethod
    def predict_proba(self, feature_vec: np.ndarray, target_class: int):
        pass

    @abstractmethod
    def predict(self, feature_vec: np.ndarray):
        pass
