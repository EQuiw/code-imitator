"""
    Test for learning models

    If Path Error: you may need to adapt the path in Configuration.py from 'config.ini' to its full absolute path,
    if you have problems with PYPATH...

    TODO - add CCS version, but so far, output is always slightly different, check seeds in learning process...

"""

from featureextractionV2.StyloFeaturesProxy import StyloFeaturesProxy
from featureextractionV2.StyloFeatures import StyloFeatures
from classification import StratifiedKFoldProblemId
import os
import typing
import ConfigurationGlobalLearning as Config
from ConfigurationLearning.ConfigurationLearning import ConfigurationLearning
from ConfigurationLearning.ConfigurationLearningRNN import ConfigurationLearningRNN
import featureextractionV2.utils_extraction
from classification.NovelAPI.utils_classification import perform_standard_classification_for_split


PROBLEM_ID_LOADED = "3264486_5736519012712448"

import unittest



class TestFeatureExtraction(unittest.TestCase):

    def setUp(self):
        """
        Runs before any test.
        """
        pass


    def test_usenix_rf(self):
        """
        Test Caliskan et al. -- Usenix with RF approach.
        """

        configuration_learning: ConfigurationLearning = ConfigurationLearning(
            repo_path=Config.repo_path,
            dataset_features_dir=os.path.join(Config.repo_path, "data/dataset_2017"),
            suffix_data="_2017_8_formatted_macrosremoved",
            learnmodelspath=None,
            use_lexems=False,
            use_lexical_features=False,
            stop_words=Config.stop_words_codestylo,
            probsperprogrammer=Config.probsperprogrammer,
            no_of_programmers=204,
            noofparallelthreads=8,
            hyperparameters=
            {
            "n_estimators": [204],
            "max_features": [0.1, "log2"],
            "max_depth": [10, 25, 50],  # 50
            "min_samples_leaf": [2, 10],
            }
        )

        features_merged: StyloFeaturesProxy = featureextractionV2.utils_extraction.extract_link_train_test_usenix_features(
            config_learning=configuration_learning)

        c1, c2, c3, c4, c5 = TestFeatureExtraction.learn_process(features_merged=features_merged,
                           learn_config=configuration_learning,
                           learn_method="RF")

        self.assertAlmostEqual(c1, 0.882352941176, delta=10e-5)
        self.assertAlmostEqual(c2, 0.675606, delta=10e-5)
        self.assertAlmostEqual(c3, 0.72316664, delta=10e-5)
        self.assertAlmostEqual(c4, 0.0432594, delta=10e-5)
        self.assertAlmostEqual(c5, 22.0, delta=10e-5)


    # def test_ccs18_lstm(self):
    #     """
    #     Test Abuhamad et al. -- CCS18 with LSTM approach.
    #     """
    #
    #     configuration_learning: ConfigurationLearningRNN = ConfigurationLearningRNN(
    #         repo_path=Config.repo_path,
    #         dataset_features_dir=os.path.join(Config.repo_path, "data/dataset_2017"),
    #         suffix_data="_2017_8_formatted_macrosremoved",
    #         learnmodelspath=Config.learnmodelspath,
    #         use_lexems=False,
    #         use_lexical_features=False,
    #         stop_words=Config.stop_words_codestylo,
    #         probsperprogrammer=Config.probsperprogrammer,
    #         noofparallelthreads=8,
    #         scale=True,
    #         cv_optimize_rlf_params=False,
    #         cv_use_rnn_output=True,
    #         hyperparameters={
    #               "RNN_epochs": [200], #350], #50],
    #               "RNN_nounits": [32, 256], #, feature_dim],
    #               "RNN_dropout": [0.6],
    #               "RNN_lstmlayersno": [3],
    #               "RNN_denselayersno": [3],
    #               "RNN_l2reg": [0.00001],
    #               "RNN_denseneurons": [0.45]
    #               }
    #     )
    #
    #     unigrammmatrix_train = CodeStyloUnigramFeatures(inputdata=configuration_learning.datasetpath,
    #                                                     nocodesperprogrammer=configuration_learning.probsperprogrammer,
    #                                                     noprogrammers=204, binary=False, tf=True, idf=True,
    #                                                     ngram_range=(1, 2), stop_words=configuration_learning.stop_words,
    #                                                     trainobject=None) # take just uni- bi-grams
    #
    #     features_merged: CodeStyloMergedFeatures = CodeStyloMergedFeatures(
    #         [unigrammmatrix_train])
    #
    #     c1, c2, c3 = self.learn_process(features_merged=features_merged,
    #                        learn_config=configuration_learning,
    #                        learn_method="RNN")
    #
    #     self.assertAlmostEqual(c1, 0.485294117647) # 0.475490196078)
    #     self.assertAlmostEqual(c2, 0.0193488, delta=10e-5)
    #     self.assertAlmostEqual(c3, 0.01498, delta=10e-5)



    @staticmethod
    def learn_process(features_merged: StyloFeatures,
                      learn_method: str,
                      learn_config: typing.Union[ConfigurationLearning, ConfigurationLearningRNN]):
        skf2 = StratifiedKFoldProblemId.StratifiedKFoldProblemId(iids=features_merged.getiids(), n_splits=8, shuffle=True,
                                                                 random_state=411,
                                                                 nocodesperprogrammer=learn_config.probsperprogrammer)

        for train_index, test_index in skf2.split(None, None):
            curproblemid = "_".join(features_merged.getiids()[test_index[0]].split("_")[0:2])
            if curproblemid == PROBLEM_ID_LOADED:

                # I. Do classification
                accuracy, curtestlearnsetup = perform_standard_classification_for_split(
                    features_merged=features_merged,
                    train_index=train_index,
                    test_index=test_index,
                    problem_id_test=curproblemid,
                    configuration_learning=learn_config,
                    modelsavedir=None,
                    threshold_sel=1.5,
                    learn_method=learn_method,
                    skf2=skf2
                )

                # II. Extract values and return them for checking...
                currentaccuracy = accuracy[curproblemid]

                print(currentaccuracy)
                print(curtestlearnsetup.data_final_test.getfeaturematrix().mean())
                print(curtestlearnsetup.data_final_train.getfeaturematrix().mean())
                print(curtestlearnsetup.data_final_test.getfeaturematrix()[:,:10].mean())
                print(curtestlearnsetup.data_final_train.getfeaturematrix().max())

                return currentaccuracy, \
                       curtestlearnsetup.data_final_test.getfeaturematrix().mean(), \
                       curtestlearnsetup.data_final_train.getfeaturematrix().mean(), \
                       curtestlearnsetup.data_final_test.getfeaturematrix()[:, :10].mean(), \
                       curtestlearnsetup.data_final_train.getfeaturematrix().max()


if __name__ == '__main__':
    unittest.main()