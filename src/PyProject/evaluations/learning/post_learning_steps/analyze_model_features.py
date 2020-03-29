import numpy as np
import sys
import os
import classification.utils_load_learnsetup
import classification.LearnSetups.LearnSetup

### Here, we analyze the model features from RF w.r.t to feature importance   ###
### We save all features, sorted w.r.t to rank, in output files in output dir ###

############################################################# ##########################################################
import ConfigurationGlobalLearning as Config
threshold_sel = 1.0
learn_method = "RF"
feature_method: str = ["Usenix", "CCS18"][0] # <<< Choose

PROBLEM_IDS = ["3264486_5736519012712448",  "8294486_5654117850546176",  "3264486_5654742835396608",
  "5304486_5760761888505856",  "3264486_5633382285312000",  "5304486_5697460110360576",
 "8294486_5681755159789568",  "8294486_5630967708385280"]

output_dir = "/tmp/model_features/"
os.makedirs(output_dir) if not os.path.exists(output_dir) else print("Use existing dir for models", file=sys.stderr)


def get_feature_ranking(testlearnsetup: classification.LearnSetups.LearnSetup):

    ranking = []
    #print("*"*60+"\nFeature ranking:")
    importances = testlearnsetup.clf.feature_importances_
    std = np.std([tree.feature_importances_ for tree in testlearnsetup.clf.estimators_], axis=0)
    indices = np.argsort(importances)[::-1]
    for f in range(min(testlearnsetup.data_final_train.getfeaturematrix().shape[1], 10050)):
        ccolname = testlearnsetup.data_final_train.getcolnames()[indices[f]]
        # col = testlearnsetup.data_final_train.colnames[indices[f]]
        #if col.colorigin == "unigram":
        current_ranking_value = (f + 1, indices[f],
                   testlearnsetup.data_final_train.getcolnames()[indices[f]],
                   importances[indices[f]])
        #print("%d. feature %d [%s] (%f)" % current_ranking_value )
        ranking.append(current_ranking_value)
    return ranking


all_feature_names = set()
for PROBLEM_ID in PROBLEM_IDS:
    print(PROBLEM_ID)

    testlearnsetup: classification.LearnSetups.LearnSetup.LearnSetup = classification.utils_load_learnsetup.load_learnsetup(
        learnmodelspath=Config.learnmodelspath,
        feature_method=feature_method,
        learn_method=learn_method,
        problem_id=PROBLEM_ID,
        threshold_sel=threshold_sel)

    # Data Check: check whether nan are there
    print(np.min(testlearnsetup.data_final_train.getfeaturematrix()), np.max(testlearnsetup.data_final_train.getfeaturematrix()),
        np.min(testlearnsetup.data_final_test.getfeaturematrix()), np.max(testlearnsetup.data_final_test.getfeaturematrix()))

    feats = get_feature_ranking(testlearnsetup=testlearnsetup)
    print("Feats:", len(feats))

    # save in txt file in output dir
    with open(os.path.join(output_dir, PROBLEM_ID), "w") as text_file:
        for feat_v in feats:
            print("%d. feature %d [%s] (%f)" % feat_v, file=text_file)

    for feat_v in feats:
        all_feature_names.add(feat_v[2])


all_feature_names = np.sort(np.array(list(all_feature_names)))
with open(os.path.join(output_dir, "all_features_set.log"), "w") as text_file:
    for feat_v in all_feature_names:
        print("%s" % feat_v, file=text_file)

with open(os.path.join(output_dir, "all_features_unigram_set.log"), "w") as text_file:
    for feat_v in all_feature_names:
        if "_unigram_" in feat_v:
            print("%s" % feat_v, file=text_file)

