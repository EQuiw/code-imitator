"""
    Test for feature extraction with new API2.
"""

from featureextractionV2.StyloFeaturesProxy import StyloFeaturesProxy
from featureextractionV2.StyloARFFFeatures import StyloARFFFeatures
from featureextractionV2 import utils_extraction

from classification import StratifiedKFoldProblemId
import ConfigurationGlobalLearning as Config
from ConfigurationLearning.ConfigurationLearning import ConfigurationLearning

import numpy as np
import unittest
import hashlib
import os
import copy


class TestFeatureExtraction(unittest.TestCase):

    def setUp(self):
        """
        Runs before any test.
        """

        configuration_learning: ConfigurationLearning = ConfigurationLearning(
            repo_path=Config.repo_path,
            dataset_features_dir=os.path.join(Config.repo_path, "data/dataset_2017/libtoolingfeatures_for_public_testing/"),
            suffix_data="_2017_8_formatted_macrosremoved",
            learnmodelspath=Config.learnmodelspath,
            use_lexems=False,
            use_lexical_features=False,
            stop_words=Config.stop_words_codestylo,
            probsperprogrammer=Config.probsperprogrammer,
            no_of_programmers=204,
            noofparallelthreads=8,
            hyperparameters=None
        )

        # A. First, get the author iids so that we have a unique key for each source file. To this end, we simply load
        # the whole dataset (but just the arff features).
        arffmatrix = StyloARFFFeatures(inputdata=configuration_learning.arffile, removelog=True)
        iids = arffmatrix.getiids()
        del arffmatrix

        # B. Split dataset into train - test set

        # Our adapted stratified k-fold
        skf2 = StratifiedKFoldProblemId.StratifiedKFoldProblemId(iids=iids, n_splits=8, shuffle=True,
                                    random_state=411, nocodesperprogrammer=configuration_learning.probsperprogrammer)

        train_index, test_index = None, None
        for train_index, test_index in skf2.split(None, None):
            if iids[test_index][0].startswith("3264486_5736519012712448"):
                break

        # use a small helper function that represents a default set of settings
        features_merged: StyloFeaturesProxy = utils_extraction.extract_link_train_test_usenix_features(
            config_learning=configuration_learning)

        self.assertAlmostEqual(float(features_merged.codestyloreference.codestyloreference.getfeaturematrix().mean()),
                               0.0929152, delta=10e-6) # float cmd just for type hints

        # C. Merge the objects into one matrix / feature representation
        self.data_final_train = features_merged[train_index]
        self.data_final_test = features_merged[test_index]

        # set up tf-idf
        self.data_final_train.createtfidffeatures(trainobject=None)
        self.data_final_test.createtfidffeatures(trainobject=self.data_final_train)

        # with lexems
        configuration_learning_lex = copy.deepcopy(configuration_learning)
        configuration_learning_lex.use_lexems = True
        features_merged2: StyloFeaturesProxy = utils_extraction.extract_link_train_test_usenix_features(
            config_learning=configuration_learning_lex)

        self.data_final_train_lexems = features_merged2[train_index]
        self.data_final_test_lexems = features_merged2[test_index]


        # with lexical features and arff
        configuration_learning_lexical = copy.deepcopy(configuration_learning)
        configuration_learning_lex.use_lexical_features = True
        features_merged3: StyloFeaturesProxy = utils_extraction.extract_link_train_test_usenix_all(
            config_learning=configuration_learning_lexical)

        self.data_final_train_lexicals = features_merged3[train_index]
        self.data_final_test_lexicals = features_merged3[test_index]



    def test_traintestset(self):
        """
        test for train set and test set
        """
        # as test will call each method that begins with test, we use the name settrain and settest for functions
        # we use one test for both, since test class will call set_up for each test what is not necessary.
        self.__settrain()
        self.__settest()
        self.__settraintestlexems()
        self.__settraintestlexicalsarff()

    def __settrain(self):
        # A. train set
        minmaxvals = (np.min(self.data_final_train.getfeaturematrix()), np.max(self.data_final_train.getfeaturematrix()))
        self.assertAlmostEqual(minmaxvals[0], 0.0, delta=10e-8)
        self.assertAlmostEqual(minmaxvals[1], 33.0, delta=10e-8)

        self.assertAlmostEqual(self.data_final_train.getfeaturematrix().mean(), 0.019612662, delta=10e-6)
        # self.assertAlmostEqual(self.data_final_train.codestyloreference.codestyloreference.getfeaturematrix().mean(), 0.103251,
        #                        delta=10e-6)

        xnms = self.data_final_train.getcolnames()
        xnms_str = ''.join(xnms)
        self.assertEqual(hashlib.md5(xnms_str.encode()).hexdigest(), '01012c6f3a8f9b45d75e745842c34947')

    def __settest(self):
        # B. test set
        minmaxvals = (np.min(self.data_final_test.getfeaturematrix()), np.max(self.data_final_test.getfeaturematrix()))
        self.assertAlmostEqual(minmaxvals[0], 0.0, delta=10e-8)
        self.assertAlmostEqual(minmaxvals[1], 22.0, delta=10e-8)

        self.assertAlmostEqual(self.data_final_test.getfeaturematrix().mean(), 0.0159195, delta=10e-6)

        xnms = self.data_final_test.getcolnames()
        xnms_str = ''.join(xnms)
        self.assertEqual(hashlib.md5(xnms_str.encode()).hexdigest(), '01012c6f3a8f9b45d75e745842c34947')

    def __settraintestlexems(self):

        sum_lex_test = self.data_final_test_lexems.getfeaturematrix().sum()
        self.assertAlmostEqual(self.data_final_train_lexems.getfeaturematrix().mean(), 0.099126689, delta=10e-6)
        self.assertAlmostEqual(self.data_final_test_lexems.getfeaturematrix().mean(), 0.060499839, delta=10e-6)
        self.assertAlmostEqual(sum_lex_test, 360545.88, delta=10e-1)
        self.assertAlmostEqual(self.data_final_test_lexems.codestyloreference._featurematrix.mean(), 0.061677273)

    def __settraintestlexicalsarff(self):
        self.assertAlmostEqual(self.data_final_train_lexicals.getfeaturematrix().mean(), 0.088408329, delta=10e-6)
        self.assertAlmostEqual(self.data_final_test_lexicals.getfeaturematrix().mean(), 0.055086121, delta=10e-6)

        xnms = [str(x) for x in self.data_final_test_lexicals.getauthors()]
        xnms_str = ''.join(xnms)
        self.assertEqual(hashlib.md5(xnms_str.encode()).hexdigest(), 'dcaf35c2164876e580a1c40ff94376da')


if __name__ == '__main__':
    unittest.main()
