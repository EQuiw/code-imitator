import os
import typing


class ConfigurationLearning:

    def __init__(self, repo_path: str,
                 dataset_features_dir: str,
                 suffix_data: str,
                 learnmodelspath: typing.Optional[str],
                 use_lexems: bool,
                 stop_words: typing.List[str],
                 use_lexical_features: bool,
                 probsperprogrammer: typing.Optional[int],
                 no_of_programmers: typing.Optional[int],
                 noofparallelthreads: int,
                 hyperparameters: typing.Optional[dict]):
        """
        Basic Configuration Class for Learning Experiments...
        :param repo_path: the path to the repository...
        :param dataset_features_dir: the path to the dataset directory, containing the dataset
        :param suffix_data: a suffix to determine which version of the dataset is wanted, e.g. the raw data,
        or the formatted data, or the formatted_macrosremoved data
        :param learnmodelspath: path where classification models will be saved, and other stuff from
        learning process. If we do not want to save anything, set it to None.
        :param use_lexems: do we use the Scikit API to extract n-grams (words) or Clang's Tokenizer to extract lexems.
        If False, we use Scikit, If True, we use Clang's tokenizer. Consider that we currently just support unigrams
        for Clang...
        :param stop_words: stop words for unigrams...
        :param use_lexical_features: also extract the lexical features (however, they are already part of the AST
        features)
        :param probsperprogrammer: number of problems (=challenges) per programmer; can be used for some consistency checks
        :param no_of_programmers: number of expected developers; can be used for some consistency checks
        :param noofparallelthreads: number of parallel threads, passed to Scikit, to learn the classifiers...
        :param hyperparameters: dict, specifying the learning hyperparameters.
        If None, the classifier may use some default parameters.
        But consider that these may not be the best parameters...
        Our default parameters are actually just designed to test the classifier quickly...
        """
        self.suffix_data = suffix_data
        self.repo_path = repo_path
        self.dataset_features_dir = dataset_features_dir

        self.datasetpath = os.path.join(dataset_features_dir, "dataset" + suffix_data)
        self.exampledatasetpath = os.path.join(dataset_features_dir, "example_dataset" + suffix_data)
        self.arffile = os.path.join(dataset_features_dir, "libtoolingfeatures" + suffix_data,
                                    "lexical_features.arff")
        self.joerndats = os.path.join(dataset_features_dir, "libtoolingfeatures" + suffix_data)
        self.learnmodelspath = learnmodelspath

        self.use_lexems = use_lexems
        self.use_lexical_features = use_lexical_features
        self.stop_words = stop_words

        self.probsperprogrammer = probsperprogrammer
        self.no_of_programmers = no_of_programmers
        self.noofparallelthreads = noofparallelthreads

        self.hyperparameters = hyperparameters


    def __str__(self):
        output = ""
        for k, v in self.__dict__.items():
            output += str(k) + ":" + str(v) + "\n"

        return output

    def change_suffix(self, novel_suffix: str):
        """
        Convenience function.
        Changes all paths where we had set suffix_data
        :param novel_suffix: novel suffix_data
        """
        self.suffix_data = novel_suffix

        self.datasetpath = os.path.join(self.dataset_features_dir, "dataset" + novel_suffix)
        self.exampledatasetpath = os.path.join(self.dataset_features_dir, "example_dataset" + novel_suffix)
        self.arffile = os.path.join(self.dataset_features_dir, "libtoolingfeatures" + novel_suffix,
                                    "lexical_features.arff")
        self.joerndats = os.path.join(self.dataset_features_dir, "libtoolingfeatures" + novel_suffix)