import typing
from ConfigurationLearning.ConfigurationLearning import ConfigurationLearning


class ConfigurationLearningRNN(ConfigurationLearning):

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
                 hyperparameters: typing.Optional[dict],
                 scale: bool,
                 cv_optimize_rlf_params: bool,
                 cv_use_rnn_output: bool):
        """
        Configuration Class for Learning Experiments with RNNs. For most params, see ConfigurationLearning...
        :param repo_path:
        :param dataset_features_dir:
        :param suffix_data:
        :param learnmodelspath:
        :param use_lexems:
        :param stop_words:
        :param use_lexical_features:
        :param probsperprogrammer:
        :param noofparallelthreads:
        :param hyperparameters:
        :param scale: if true, we standardize the features
        :param cv_optimize_rlf_params: if true and we have an RF as 'last layer', then we also optimize the RLF
        params... and do not only use its standard values as proposed in Abuhamad et al., CCS18.
        :param cv_use_rnn_output: if true, we only use the RNN output, if false, we use RNN + RF. In our experiments,
        we got worse results with 204 developers and the RNN+RF combination.
        """

        super(ConfigurationLearningRNN, self).__init__(repo_path, dataset_features_dir,
                                                       suffix_data, learnmodelspath,
                                                       use_lexems, stop_words,
                                                       use_lexical_features, probsperprogrammer,
                                                       no_of_programmers,
                                                       noofparallelthreads, hyperparameters)

        self.scale = scale
        self.cv_optimize_rlf_params = cv_optimize_rlf_params
        self.cv_use_rnn_output = cv_use_rnn_output

        # Makes no sense to set cv_optimize_rlf_params to true if cv_use_rnn_output is true
        if cv_optimize_rlf_params is True and cv_use_rnn_output is True:
            raise Exception("Chosen that we want to optimize over RLF params, but we do not evaluate them")