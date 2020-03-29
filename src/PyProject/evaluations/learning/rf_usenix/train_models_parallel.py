from featureextraction import utils_extraction
from featureextraction.CodeStyloMergedFeatures import CodeStyloMergedFeatures
from featureextraction.CodeStyloUnigramFeatures import CodeStyloUnigramFeatures
from classification import StratifiedKFoldProblemId

# import importlib
import os
import sys
import numpy as np
import evasion.utils_launch_attacks
from ConfigurationLearning.ConfigurationLearning import ConfigurationLearning
import ConfigurationGlobalLearning as Config
import classification.utils_classification

############### Input ##############
parser = evasion.utils_launch_attacks.getProblemIDParser()
args = parser.parse_args()
PROBLEM_ID_LOADED = args.problemid[0]

############### Variable Definition ##############

configuration_learning: ConfigurationLearning = ConfigurationLearning(
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
    hyperparameters={"n_estimators": [204, 250, 300, 350],
                     "max_features": [0.1, 0.2, 0.3, 0.4, 0.5, "log2", "sqrt"],
                     "max_depth": [10, 15, 20, 25, 30, 40, 50],  # 50
                     "min_samples_leaf": [2, 4, 6, 8, 10, 12, 14],
                     }
)


learn_method: str = ["RF", "SVM", "DNN"][0]
feature_method: str = ["Usenix", "CCS18"][0]
threshold_sel: float = [1.0, 800][0]

# Directory where model files will be stored, set None if you do not want to save anything, or specify a path.
if configuration_learning.learnmodelspath is not None:
    modelsavedir = os.path.join(configuration_learning.learnmodelspath, feature_method + "_" + learn_method)
    os.makedirs(modelsavedir) if not os.path.exists(modelsavedir) else print("Use existing dir for models", file=sys.stderr)
else:
    modelsavedir = None


############## Get lexical, layout and syntactic features ##############

if feature_method == "Usenix":
    features_list = utils_extraction.extract_train_test_features(config_learning=configuration_learning)
    arffmatrix_train, unigrammmatrix_train, joernmatrix_train = features_list
    features_merged: CodeStyloMergedFeatures = CodeStyloMergedFeatures([unigrammmatrix_train, joernmatrix_train])  # arffmatrix_train

elif feature_method == "CCS18":
    assert configuration_learning.use_lexems is not True
    unigrammmatrix_train = CodeStyloUnigramFeatures(inputdata=configuration_learning.datasetpath,
                                                    nocodesperprogrammer=configuration_learning.probsperprogrammer,
                                                    noprogrammers=configuration_learning.no_of_programmers,
                                                    binary=False, tf=True, idf=True,
                                                    ngram_range=(1, 3), stop_words=configuration_learning.stop_words,
                                                    trainobject=None)

    features_merged: CodeStyloMergedFeatures = CodeStyloMergedFeatures(
        [unigrammmatrix_train])  # joernmatrix_train # arffmatrix_train
else:
    raise Exception("feature_method")


############## Split dataset into train - test set with our our grouped stratified k-fold ##############
skf2 = StratifiedKFoldProblemId.StratifiedKFoldProblemId(iids=features_merged.iids, n_splits=8, shuffle=True,
                                                         random_state=411,
                                                         nocodesperprogrammer=configuration_learning.probsperprogrammer)
print("No splits:", skf2.get_n_splits())


############## Do training + testing on each split ##############
accuracy = {}

for train_index, test_index in skf2.split(None, None):
    curproblemid = "_".join(features_merged.iids[test_index[0]].split("_")[0:2])
    if curproblemid == PROBLEM_ID_LOADED:

        # the following method saves the model and config file into modelsavedir if given
        accuracy, _ = classification.utils_classification.perform_standard_classification_for_split(
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