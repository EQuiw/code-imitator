## Collect the x authors or author pairs that are valid
## for all problems across all learning models (USENIX-RF and CSS-RNN)

from featureextractionV2 import StyloARFFFeatures as a
from evasion.AttackEval import AttackEvalImpersonation, AttackEvalAbstract
import pickle
import os
import classification.utils_load_learnsetup
import classification.LearnSetups.LearnSetup
import collections

Learn_Feature_Choice = collections.namedtuple('Learn_Feature_Choice', 'learn_method feature_method threshold_sel')

############################################################# ##########################################################
import ConfigurationGlobalLearning as Config

# We aggregate the following three parameters into a named tuple Learn_Feature_Choice:
# threshold_sel: float = 1.25
# learn_method: str = ["RF", "SVM", "DNN"][0] # <<< Choose
# feature_method: str = ["Usenix", "CCS18"][0] # <<< Choose

learn_feature_methods = [Learn_Feature_Choice("RF", "Usenix", 1.0), Learn_Feature_Choice("RNN", "CCS18", 800)]

arffile = os.path.join(Config.repo_path, "data/dataset_2017/libtoolingfeatures_2017_8_formatted_macrosremoved/lexical_features.arff")
arffmatrix = a.StyloARFFFeatures(inputdata = arffile, removelog=True)
iids = arffmatrix.getiids()
del arffmatrix, arffile

problemids: set = set([x.split("_")[0] + "_" + x.split("_")[1] for x in iids])
assert len(problemids) == Config.probsperprogrammer

## load for each problem the possible authors that are correctly classified, remind we have only about 90% accuracy
authors_4problemid = {}
for problemid in problemids:

    ## load each classification model, e.g. usenix-rf and rnn-css.
    for setting in learn_feature_methods:
        print("** Load Problem ID: {} in setting {}".format(problemid, str(setting)))

        testlearnsetup: classification.LearnSetups.LearnSetup.LearnSetup = classification.utils_load_learnsetup.load_learnsetup(
            learnmodelspath=Config.learnmodelspath,
            feature_method=setting.feature_method,
            learn_method=setting.learn_method,
            problem_id=problemid,
            threshold_sel=setting.threshold_sel)

        attackeval: AttackEvalAbstract = AttackEvalImpersonation(testlearnsetup=testlearnsetup,
                                                             attack_dir="",
                                                             no_authors=None,
                                                             selected_authors=None,
                                                             verbose=False,
                                                             seed=31)

        authors_4problemid[problemid+str(setting)] = set(attackeval.possible_authors.keys())


## get the largest intersection of all ##
common = [*set.intersection(*authors_4problemid.values())]

print("Len:", len(common))
print("->", sorted(common))

commonx = common[0:20]

## Save the set so that we can load the author pairs later at attack time
authorspairs = []
for i, authorx in enumerate(commonx):
    for j, authory in enumerate(commonx):
        if i != j:
            authorspairs.append((authorx, authory))

print(authorspairs)


authorpairdirs = os.path.join(Config.learnmodelspath, "authorpairs")
os.makedirs(authorpairdirs) if not os.path.exists(authorpairdirs) else print("--")

for setting in learn_feature_methods:
    feature_methodx = setting.feature_method
    learn_methodx = setting.learn_method
    threshold_selx = setting.threshold_sel
    modelfile = os.path.join(authorpairdirs, "authorpairsforimpersonation" + "AllProblems" + "_" + feature_methodx +
                             "_" + learn_methodx + "_" + str(threshold_selx) + ".pck")
    print(modelfile)
    pickle.dump(authorspairs, file=open(modelfile, 'wb'))
