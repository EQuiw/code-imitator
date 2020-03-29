# This file provides a short tutorial about the usage of our API for authorship attribution.
# Here, you get more explanations about the feature API.
# In addition, we will use a configuration object and call the learning API properly (with cross-validation on
#   different hyperparameters).

import os
import typing
import numpy as np
import copy

from ConfigurationLearning.ConfigurationLearning import ConfigurationLearning
from classification import StratifiedKFoldProblemId
import classification.NovelAPI.utils_classification


# Let's start with the challenge 3264486_5736519012712448
problem_id = "3264486_5736519012712448"
# specify here the path to the repository.
repo_path = "<path-to-the-authorship-evasion-repo>"


learnmodelspath = "/dev/shm/" # let's save the learning model to a ramdisk on ubuntu, adapt it if you need.
stop_words_codestylo = ["txt", "in", "out", "attempt0", "attempt", "attempt1", "small", "output", "input"]
probsperprogrammer = 8
no_programmers = 204


# We will use here a Config object to store all necessary values.
# Consider: we use a reduced number of hyperparameters in this tutorial.
configuration_learning: ConfigurationLearning = ConfigurationLearning(
    repo_path=repo_path,
    dataset_features_dir=os.path.join(repo_path, "data/dataset_2017"),
    suffix_data="_2017_8_formatted_macrosremoved",
    learnmodelspath=learnmodelspath,
    use_lexems=False,
    use_lexical_features=False,
    stop_words=stop_words_codestylo,
    probsperprogrammer=probsperprogrammer,
    no_of_programmers = no_programmers,
    noofparallelthreads=8,
    hyperparameters={"n_estimators": [350],
                     "max_features": ["sqrt"],
                     "max_depth": [20, 25],  # 50
                     "min_samples_leaf": [6, 8],
                     }
)

# ! Now we use the feature setup from Caliskan et al., so that we have to use different feature classes.
learn_method: str = ["RF"][0]
feature_method: str = ["Usenix", "CCS18"][0]
# Use a float value to define that we keep all features where mutual information > threshold_sel.
# Alternatively, you can use an int to specify how many fixed features you want to have, e.g. threshold_sel = 800.
threshold_sel: typing.Union[int, float] = 1.0

# create the final subdir where we save the model
modelsavedir = os.path.join(configuration_learning.learnmodelspath, feature_method + "_" + learn_method)
os.makedirs(modelsavedir) if not os.path.exists(modelsavedir) else print("dir already existed")


### Get features
from featureextractionV2.StyloFeaturesProxy import StyloFeaturesProxy
from featureextractionV2.StyloFeatures import StyloFeatures
from featureextractionV2.utils_extraction import extract_train_test_arff, extract_train_test_unigram, \
    extract_train_test_clang

# So for Caliskan et al., we have layout, lexical and syntactic features.
# The layout features + some lexical features are present in the ARFF feature set.
# More lexical features can be obtained by creating a StyloUnigramFeatures object.
# And all AST features can be obtained by using clang.
# Note: in our paper, we do not consider layout features. Moreover, the clang feature set contains the lexical
# features from the arff feature set; as a result, we did not load the arff feature set during our evaluation.

# Now get all the different types of features == it means, we get the respective features from different sources,
# arff features from the arff file, unigram from Python directly, and all clang from the clang extractions.

# A. ARFF features
arffmatrix_train: StyloFeatures = extract_train_test_arff(config_learning=configuration_learning)
# let's look at the column names, and the shape of the feature matrix
print(arffmatrix_train.getcolnames(), "\n Shape:", arffmatrix_train.getfeaturematrix().shape)

# B. Unigram features (only unigrams here in contrast to Abuhamad et al.)
unigrammmatrix_train: StyloFeatures = extract_train_test_unigram(config_learning=configuration_learning,
                                                      tf=True, idf=False, ngram_range=(1,1))
print(unigrammmatrix_train.getcolnames()[:10], " ... \n Shape:", unigrammmatrix_train.getfeaturematrix().shape)

# C. Clang-based features
# We get here a list of StyloFeatures, where each comes from a different file, such as ast_node_bigram.dat.
clangmatrices_train: typing.List[StyloFeatures] = extract_train_test_clang(config_learning=configuration_learning)

# Now its getting tricky. Caliskan et al. specified that they used TF-IDF features.
# However, for example, for the AST-Node-Types feature set, they create two versions:
# 1) a TF-only feature set, and 2) a TF-IDF feature set.
# The method extract_train_test_clang calls StyloClangFeaturesGenerator which copies the feature matrix to this end.
# It creates two feature sets.
#
# The first saves tf=true and idf=False internally, the second saves tf=true and idf=True internally.
# Both feature matrices are identical before you call the method 'createtfidffeatures'. The method createtfidffeatures
# will create the tf and tf+idf versions, respectively.


# Now let's look at it.
# The two matrices are located at index 1 and 2.
# The last two bool values indicate the tf and idf option:
print(clangmatrices_train[1].getunique_key(), "//", clangmatrices_train[2].getunique_key())
# check feature matrices are identical
print(np.sum(clangmatrices_train[1].getfeaturematrix() != clangmatrices_train[2].getfeaturematrix()))

# let's copy the list to explain some important issues
clangmatrices_train_copy = copy.deepcopy(clangmatrices_train)

# now if we call tf-idf on both matrices, the first will perform a tf transformation, the second a tf+idf transformation
clangmatrices_train_copy[1].createtfidffeatures(trainobject=None) # ignore the trainobject param for the moment
clangmatrices_train_copy[2].createtfidffeatures(trainobject=None)

# they are now not identical anymore.
print(np.sum(clangmatrices_train_copy[1].getfeaturematrix() != clangmatrices_train_copy[2].getfeaturematrix()))

# Why do we need all this stuff? Well, we need to avoid data snooping. If we perform the td-idf transformation
# at the time where we create the feature matrices, and then split the data later into training, validation and test sets,
# we would use knowledge that we do not have in practice. That's why we load the feature matrices, split them
# and then call createtfidffeatures to get the final feature matrices!


# Finally, we need to link all the individual feature matrices!
# Look at the Decorater design pattern to understand more about that.
# We adapted it slightly for our needs during the evasion attack.

arffmatrix_train.setnextstylo(codestyloreference=unigrammmatrix_train)
unigrammmatrix_train.setnextstylo(codestyloreference=clangmatrices_train[0])

# Last, let's link all clang objects
for ix in range(1, len(clangmatrices_train)):
    clangmatrices_train[ix - 1].setnextstylo(clangmatrices_train[ix])




# In this way, we create a chain of feature objects, where:
# arffmatrix_train -> unigrammmatrix_train -> clangmatrix1 -> clangmatrix2 -> ... -> clangmatrixn
# If we call now arffmatrix_train.getfeaturematrix(), it will build a large feature matrix by combining all feature matrices
# from the chained feature objects.

print(arffmatrix_train.getfeaturematrix().shape) # shows (1632, 29141)
# we get a feature matrix with 1632 rows (8 challenges * 204 authors) and 29141 features
# The feature matrix contains the arff features, the unigram features and the clang features now.

# Usually, but not necessary, we pass the first object in the chain to StyloFeaturesProxy.
# The idea is that this class could implement some caching later, to speed up the retrieval of the feature matrix...
features_merged: StyloFeatures = StyloFeaturesProxy(codestyloreference=arffmatrix_train)



### Learning

############## Split dataset into train - test set with our our grouped stratified k-fold ##############
skf2 = StratifiedKFoldProblemId.StratifiedKFoldProblemId(iids=features_merged.getiids(), n_splits=8, shuffle=True,
                                                         random_state=411,
                                                         nocodesperprogrammer=configuration_learning.probsperprogrammer)


############## Do training + testing on each split ##############
accuracy = {}

for train_index, test_index in skf2.split(None, None):
    curproblemid = "_".join(features_merged.getiids()[test_index[0]].split("_")[0:2])

    if curproblemid == problem_id:
        # The following function splits the dataset accordingly, does some cross validation, and returns the learn model.
        # It saves the model and config file into modelsavedir if not None.
        accuracy, learnmodel = classification.NovelAPI.utils_classification.perform_standard_classification_for_split(
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

        print(accuracy)  # I get 88.7% accuracy with this simple set of hyperparameters.
