from featureextractionV2.StyloFeaturesProxy import StyloFeaturesProxy
from featureextractionV2.StyloFeatures import StyloFeatures
from classification import StratifiedKFoldProblemId
from featureextractionV2 import utils_extraction

# import importlib
import os
import sys
import numpy as np
import argparse

from ConfigurationLearning.ConfigurationLearningRNN import ConfigurationLearningRNN
import ConfigurationGlobalLearning as Config
import classification.NovelAPI.utils_classification

############ Input
parser = argparse.ArgumentParser(description='Start Attack')
parser.add_argument('problemid', type=str, nargs=1,
                    help='the problem id')
parser.add_argument('gpu', type=str, nargs=1,
                    help='the gpu to be used')
args = parser.parse_args()
PROBLEM_ID_LOADED = args.problemid[0]
# PROBLEM_ID_LOADED = "8294486_5681755159789568"
GPU_LOADED = args.gpu[0]
# GPU_LOADED = "0"
print("Loaded:", PROBLEM_ID_LOADED, " with GPU:", GPU_LOADED)

############### Variable Definition ##############

configuration_learning: ConfigurationLearningRNN = ConfigurationLearningRNN(
    repo_path=Config.repo_path,
    dataset_features_dir=os.path.join(Config.repo_path, "data/dataset_2017"),
    suffix_data="_2017_8_formatted_macrosremoved",
    learnmodelspath=Config.learnmodelspath,
    use_lexems=False,
    use_lexical_features=False,
    stop_words=Config.stop_words_codestylo,
    probsperprogrammer=Config.probsperprogrammer,
    no_of_programmers = 204,
    noofparallelthreads=8,
    scale=True,
    cv_optimize_rlf_params=False,
    cv_use_rnn_output=True,
    hyperparameters={
                      "RNN_epochs": [100, 200, 300, 350, 450, 500], #350], #50],
                      "RNN_nounits": [32, 128, 196, 256, 288], #, feature_dim],
                      "RNN_dropout": [0.6],
                      "RNN_lstmlayersno": [3],
                      "RNN_denselayersno": [3],
                      "RNN_l2reg": [0.00001],
                      "RNN_denseneurons": [0.45]
                      }
)

threshold_sel: int = 800
learn_method: str = "RNN"
os.environ["CUDA_VISIBLE_DEVICES"] = GPU_LOADED  # SELECT GPU if available


# Directory where model files will be stored, set None if you do not want to save anything, or specify a path.
feature_method = "CCS18"
if configuration_learning.learnmodelspath is not None:
    modelsavedir = os.path.join(configuration_learning.learnmodelspath, feature_method + "_" + learn_method)
    os.makedirs(modelsavedir) if not os.path.exists(modelsavedir) else print("Use existing dir for models", file=sys.stderr)
else:
    modelsavedir = None


############## Get lexical, layout and syntactic features ##############
assert feature_method == "CCS18"
assert configuration_learning.use_lexems is not True
unigrammmatrix_train: StyloFeatures = utils_extraction.extract_train_test_unigram(
        config_learning=configuration_learning, tf=True, idf=True, ngram_range=(1, 3))

features_merged: StyloFeaturesProxy = StyloFeaturesProxy(codestyloreference=unigrammmatrix_train)


############## Split dataset into train - test set with our our grouped stratified k-fold ##############
skf2 = StratifiedKFoldProblemId.StratifiedKFoldProblemId(iids=features_merged.getiids(), n_splits=8, shuffle=True,
                                                         random_state=411,
                                                         nocodesperprogrammer=configuration_learning.probsperprogrammer)
print("No splits:", skf2.get_n_splits())


############## Do training + testing on each split ##############
accuracy = {}

for train_index, test_index in skf2.split(None, None):
    curproblemid = "_".join(features_merged.getiids()[test_index[0]].split("_")[0:2])
    if curproblemid == PROBLEM_ID_LOADED:

        accuracy, _ = classification.NovelAPI.utils_classification.perform_standard_classification_for_split(
            features_merged=features_merged,
            train_index=train_index,
            test_index=test_index,
            problem_id_test=curproblemid,
            configuration_learning=configuration_learning,
            modelsavedir=modelsavedir,
            threshold_sel=threshold_sel,
            learn_method=learn_method,
            skf2=skf2
        )


print(accuracy)
accuracies = np.array([x for x in accuracy.values()])
print(np.mean(accuracies))
print(np.sqrt(np.var(accuracies)))
