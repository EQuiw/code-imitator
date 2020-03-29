## Collect the x authors or author pairs that are valid for all problems ##
## This is the weaker version of collect-authorspairs-allmodels.py, as we collect all problems for one model!

from featureextractionV2 import StyloARFFFeatures as a
from evasion.AttackEval import AttackEvalImpersonation, AttackEvalAbstract
import pickle
import os
import classification.utils_load_learnsetup
import classification.LearnSetups.LearnSetup

############################################################# ##########################################################
import ConfigurationGlobalLearning as Config

threshold_sel: float = 1.0
learn_method: str = ["RF", "SVM", "DNN"][0] # <<< Choose
feature_method: str = ["Usenix", "CCS18"][0] # <<< Choose

arffile = os.path.join(Config.repo_path, "data/dataset_2017/libtoolingfeatures_2017_8_formatted_macrosremoved/lexical_features.arff")
arffmatrix = a.StyloARFFFeatures(inputdata = arffile, removelog=True)
iids = arffmatrix.getiids()
del arffmatrix, arffile

problemids: set = set([x.split("_")[0] + "_" + x.split("_")[1] for x in iids])
assert len(problemids) == Config.probsperprogrammer

## load for each problem the possible authors that are correctly classified, remind we have only about 90% accuracy
authors_4problemid = {}
for problemid in problemids:
    print("** Load Problem ID: {}".format(problemid))

    testlearnsetup: classification.LearnSetups.LearnSetup.LearnSetup = classification.utils_load_learnsetup.load_learnsetup(
        learnmodelspath=Config.learnmodelspath,
        feature_method=feature_method,
        learn_method=learn_method,
        problem_id=problemid,
        threshold_sel=threshold_sel)

    attackeval: AttackEvalAbstract = AttackEvalImpersonation(testlearnsetup=testlearnsetup,
                                                         attack_dir="",
                                                         no_authors=None,
                                                         selected_authors=None,
                                                         verbose=False,
                                                         seed=31)

    authors_4problemid[problemid] = set(attackeval.possible_authors.keys())


## get the largest intersection of all ##
common = [*set.intersection(*authors_4problemid.values())]

print("Len:", len(common))
print("->", sorted(common))


commonx = common[0:20]


# If we load a previous collected author set where we need only a few new authors due to a new model,
# then add the necessary ones and check if all previous are still in all models..
# If you just follow this script here in collect_authorpairs.py, the following check is not necessary.
for a in commonx:
    if a not in common:
        print(a)


## Save the set so that we can load the author pairs later at attack time
authorspairs = []
for i, authorx in enumerate(commonx):
    for j, authory in enumerate(commonx):
        if i != j:
            authorspairs.append((authorx, authory))

print(authorspairs)


authorpairdirs = os.path.join(Config.learnmodelspath, "authorpairs")
os.makedirs(authorpairdirs) if not os.path.exists(authorpairdirs) else print("--")

modelfile = os.path.join(authorpairdirs, "authorpairsforimpersonation" + "AllProblems" + "_" + feature_method +
                         "_" + learn_method + "_" + str(threshold_sel) + ".pck")
pickle.dump(authorspairs, file=open(modelfile, 'wb'))
