import numpy as np
import sys
import os
import classification.utils_load_learnsetup
import classification.LearnSetups.LearnSetup

### Here, we analyze the model features from RF w.r.t to feature importance   ###
### We save all features, sorted w.r.t to rank, in output files in output dir ###

############################################################# ##########################################################
import ConfigurationGlobalLearning as Config
threshold_sel = 800
learn_method = "RNN"
feature_method: str = ["Usenix", "CCS18"][1]

PROBLEM_IDS = ["3264486_5736519012712448",  "8294486_5654117850546176",  "3264486_5654742835396608",
  "5304486_5760761888505856",  "3264486_5633382285312000",  "5304486_5697460110360576",
 "8294486_5681755159789568",  "8294486_5630967708385280"]

output_dir = "/tmp/model_features_rnn/"
os.makedirs(output_dir) if not os.path.exists(output_dir) else print("Use existing dir for models", file=sys.stderr)


def get_features(testlearnsetupx: classification.LearnSetups.LearnSetup):
    return testlearnsetupx.data_final_test.getcolnames()


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

    feats = get_features(testlearnsetupx=testlearnsetup)
    print("Feats:", len(feats))

    for feat_v_name in feats:
        all_feature_names.add(feat_v_name)


all_feature_names = np.sort(np.array(list(all_feature_names)))
with open(os.path.join(output_dir, "all_features_unigram_set.log"), "w") as text_file:
    for feat_v in all_feature_names:
        if "_unigram_" in feat_v:
            print("%s" % feat_v, file=text_file)

