"""
    Test for feature extraction
"""

from featureextraction.CodeStyloARFFFeatures import *
from featureextraction.CodeStyloMergedFeatures import *
from featureextraction import utils_extraction
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
            dataset_features_dir=os.path.join(Config.repo_path, "data/dataset_2017"),
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
        arffmatrix = CodeStyloARFFFeatures(inputdata=configuration_learning.arffile, removelog=True)
        iids = arffmatrix.iids
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
        features_list = utils_extraction.extract_train_test_features(config_learning=configuration_learning)

        arffmatrix_train, unigrammmatrix_train, joernmatrix_train = features_list
        features_merged: CodeStyloMergedFeatures = CodeStyloMergedFeatures(
            [unigrammmatrix_train, joernmatrix_train])  # arffmatrix_train

        # C. Merge the objects into one matrix / feature representation
        self.data_final_train = features_merged[train_index]
        self.data_final_test = features_merged[test_index]

        # set up tf-idf
        self.data_final_train.update_tfidffeatures(trainobject=None)
        self.data_final_test.update_tfidffeatures(trainobject=self.data_final_train)

        print("jo-cl", joernmatrix_train.featurematrix.mean(), "should be: 0.0985883")

        # with lexems
        configuration_learning_lex = copy.deepcopy(configuration_learning)
        configuration_learning_lex.use_lexems = True
        features_list2 = utils_extraction.extract_train_test_features(config_learning=configuration_learning_lex)

        arffmatrix_train2, unigrammmatrix_train2, joernmatrix_train2 = features_list2
        features_merged2: CodeStyloMergedFeatures = CodeStyloMergedFeatures(
            [unigrammmatrix_train2, joernmatrix_train2])  # arffmatrix_train
        self.data_final_train_lexems = features_merged2[train_index]
        self.data_final_test_lexems = features_merged2[test_index]


    def test_traintestset(self):
        """
        test for train set and test set
        """
        # as test will call each method that begins with test, we use the name settrain and settest for functions
        # we use one test for both, since test class will call set_up for each test what is not necessary.
        self.__settrain()
        self.__settest()
        self.__settraintestlexems()

    def __settrain(self):
        # A. train set
        minmaxvals = (np.min(self.data_final_train.featurematrix), np.max(self.data_final_train.featurematrix))
        self.assertAlmostEqual(minmaxvals[0], 0.0, delta=10e-8)
        self.assertAlmostEqual(minmaxvals[1], 33.0, delta=10e-8)

        self.assertAlmostEqual(np.mean(self.data_final_train.featurematrix), 0.0196194, delta=10e-6)
        self.assertAlmostEqual(self.data_final_train.codestyloobject_list[1].featurematrix.mean(), 0.103251,
                               delta=10e-6)

        xnms = [str(x) for x in self.data_final_train.colnames]
        xnms_str = ''.join(xnms)
        self.assertEqual(hashlib.md5(xnms_str.encode()).hexdigest(), '6b9cd31568ea0d37af38665b5dd91cf7')


    def __settest(self):
        # B. test set
        minmaxvals = (np.min(self.data_final_test.featurematrix), np.max(self.data_final_test.featurematrix))
        self.assertAlmostEqual(minmaxvals[0], 0.0, delta=10e-8)
        self.assertAlmostEqual(minmaxvals[1], 22.0, delta=10e-8)

        self.assertAlmostEqual(np.mean(self.data_final_test.featurematrix), 0.0159245, delta=10e-6)

        xnms = [str(x) for x in self.data_final_test.colnames]
        xnms_str = ''.join(xnms)
        self.assertEqual(hashlib.md5(xnms_str.encode()).hexdigest(), '6b9cd31568ea0d37af38665b5dd91cf7')

    def __settraintestlexems(self):

        sum_lex_test = self.data_final_test_lexems.featurematrix.sum()
        self.assertAlmostEqual(self.data_final_train_lexems.featurematrix.mean(), 0.104147, delta=10e-6)
        self.assertAlmostEqual(self.data_final_test_lexems.featurematrix.mean(), 0.0650224, delta=10e-6)
        self.assertAlmostEqual(sum_lex_test, 281155.84, delta=10e-1)

if __name__ == '__main__':
    unittest.main()
