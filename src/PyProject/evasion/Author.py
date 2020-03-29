import numpy as np
import os
import typing
import random

import Configuration as Config
import classification.LearnSetups.LearnSetup


class AuthorException(Exception):
    pass


class Author:
    """
    In principle, similar to a struct, just saves the information about a source or target author.
    """

    def __init__(self, author: str, learnsetup: classification.LearnSetups.LearnSetup.LearnSetup):

        self.author = author
        self.authrows = np.where(learnsetup.data_final_test.getauthors() == self.author)[0][0]
        self.authiid = learnsetup.data_final_test.getiids()[self.authrows]
        self.true_class =  learnsetup.data_final_test.getlabels()[self.authrows]

        # get all source files for author in training set
        source_authrows = np.where(learnsetup.data_final_train.getauthors() == self.author)[0]
        self.all_authiids_train = learnsetup.data_final_train.getiids()[source_authrows]

        # get all example files for author that were not used during training / testing
        self.auth_example_iids = self.__collect_example_files()


    def __collect_example_files(self) -> typing.Optional[typing.List[str]]:
        """
        Collect example files for author if they exist.
        """

        dirlist = [item for item in os.listdir(Config.exampledatasetpath)
                   if os.path.isdir(os.path.join(Config.exampledatasetpath, item))]
        if self.author in dirlist:
            mypath = os.path.join(Config.exampledatasetpath, self.author)
            ex_files = [f for f in os.listdir(mypath) if os.path.isfile(os.path.join(mypath, f))]

            # in config, we set up how many files we want to have...
            ex_files.sort()
            random.seed(83 + len(ex_files))
            ex_files = random.sample(ex_files, Config.no_of_example_files)

            assert len(ex_files) == Config.no_of_example_files # just small check
        else:
            ex_files = None
        return ex_files


    def check_is_correct(self, learnsetup: classification.LearnSetups.LearnSetup.LearnSetup, verbose: bool = True):

        iscorrect: bool = learnsetup.predict(feature_vec=learnsetup.data_final_test.getfeaturematrix()[self.authrows, :])\
                          == self.true_class

        if verbose is True:
            print("Check is correct identified:", self.authiid, " with row:", self.authrows)
            scorepred = learnsetup.predict_proba(feature_vec=learnsetup.data_final_test.getfeaturematrix()[self.authrows, :],
                                                 target_class=self.true_class)
            print(str(iscorrect) + " with: " + str(scorepred))

        if not iscorrect:
            raise AuthorException("Author is misclassified")
