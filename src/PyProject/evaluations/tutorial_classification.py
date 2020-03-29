# This file provides a short tutorial about the usage of our API for authorship attribution.
# We will use a simple Random Forest with N-gram features (unigram, bigram and trigrams).
# This feature set corresponds to the feature set from Abuhamad et al. (CCS'18).

import os
import typing


# Let's start with the challenge 3264486_5736519012712448
problem_id = "3264486_5736519012712448"
# specify here the path to the repository.
repo_path = "<path-to-the-authorship-evasion-repo>"


# Further parameters:
# we use the following dataset.
datasetpath = os.path.join(repo_path, "data", "dataset_2017", "dataset_2017_8_formatted_macrosremoved")
# we specify some stop words, see ConfigurationGlobalLearning.py
stop_words_codestylo = ["txt", "in", "out", "attempt0", "attempt", "attempt1", "small", "output", "input"]
# We assume 8 files per author
probsperprogrammer = 8
# we assume a dataset of 204 authors in total
no_programmers = 204


### Get features
# The class 'StyloFeatures' stores all relevant information for the classification, such as the feature matrix,
#   the column names and the authors / unique labels. It hides all the complexity. We have different feature
#   classes under it; all classes are implemented by following/adjusting the Decorator Design Pattern.
#
# Look at tutorial_classification_2.py for a deeper introduction to the feature API!

from featureextractionV2.StyloFeaturesProxy import StyloFeaturesProxy
from featureextractionV2.StyloFeatures import StyloFeatures
from featureextractionV2.StyloUnigramFeatures import StyloUnigramFeatures
from featureextractionV2.FeatureNames import FeatureName

# by using ngram_range from 1 to 3: we load unigram, bigram and trigrams.
unigrammmatrix_train = StyloUnigramFeatures(inputdata=datasetpath,
                                            nocodesperprogrammer=probsperprogrammer,
                                            noprogrammers=no_programmers,
                                            binary=False, tf=True, idf=True,
                                            ngram_range=(1, 3), stop_words=stop_words_codestylo,
                                            trainobject=None)
features_merged: StyloFeaturesProxy = StyloFeaturesProxy(codestyloreference=unigrammmatrix_train)

# now let's look how we can get some information about the features, the authors and so on.
features_merged.getfeaturematrix()  # returns the feature matrix

# returns a list of FeatureNames objects. Each object stores some more information about the respective feature.
colnamesraw: typing.List[FeatureName] = features_merged.getcolnamesraw()
print("{}, {}, {}".format(colnamesraw[0].colname, colnamesraw[0].colorigin, colnamesraw[0].coltype))  # e.g.

# get the author names, the full iids, and the converted labels for each row of the feature matrix
features_merged.getauthors()
features_merged.getiids()
features_merged.getlabels()


### Learning
from classification import StratifiedKFoldProblemId
import sklearn.feature_selection
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score


# Let's make a stratified and grouped k-fold.
# We want the same number of files from each author in the training set (=stratified),
# and the test set should only contain files from challenges that are not present in the training set (=grouped).
skf2 = StratifiedKFoldProblemId.StratifiedKFoldProblemId(iids=features_merged.getiids(), n_splits=8, shuffle=True,
                                                         random_state=411, nocodesperprogrammer=probsperprogrammer)
print("No splits:", skf2.get_n_splits())


# Now let's iterate over all possible splits, but we only want to do the learning stuff here for one challenge/problem.
# So let's get the split for the challenge id that we defined above.
used_train_index, used_test_index = None, None
for train_index, test_index in skf2.split(None, None):
    curproblemid = "_".join(features_merged.getiids()[test_index[0]].split("_")[0:2])
    if curproblemid == problem_id:
        used_train_index = train_index
        used_test_index = test_index
        break


# 1. We split the dataset into a train- and test set
# It is always important that we first split the dataset, and then apply the tf-idf transformation.
trainfiles: StyloFeatures = features_merged[used_train_index] # the operator [] allows row-wise selection.
testfiles: StyloFeatures = features_merged[used_test_index]

# 2. We do a tf-idf transformation
trainfiles.createtfidffeatures(trainobject=None)

# we pass the trainfiles object to the testfiles object, in this way, we apply the tf-idf parameters
# from the training set on the test set. This is quite important to avoid data snooping.
testfiles.createtfidffeatures(trainobject=trainfiles)

# 3. Next, feature selection is used.
# Let's get the scores
featsel = sklearn.feature_selection.mutual_info_classif(X=trainfiles.getfeaturematrix(),
                                                        y=trainfiles.getlabels(),
                                                        discrete_features="auto",
                                                        copy=True, random_state=17)
# We select 800 features here, which corresponds to the reported ratios from Abuhamad et al., CCS'18.
sel_feat_indices = (-featsel).argsort()[:800]

# Now sub-select the columns
trainfiles.selectcolumns(index=sel_feat_indices, trainobject=None)

# Again, it is important to pass the trainfiles object to the test set.
testfiles.selectcolumns(index=None, trainobject=trainfiles)


# 4. Let's compute a simple Random Forest
# (!!! Again, we do not test hyperparameters in this tutorial. You should do that, look at train_models_parallel.py !!!)
rlf = RandomForestClassifier(random_state=31)
rlf.fit( trainfiles.getfeaturematrix(), trainfiles.getlabels())
ypred = rlf.predict(testfiles.getfeaturematrix())
print("Accuracy:", accuracy_score(y_true=testfiles.getlabels(), y_pred=ypred))
# I get 86.76% accuracy. With a better hyperparameter selection, we get a higher accuracy.

