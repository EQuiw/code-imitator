from abc import ABC, abstractmethod
from evasion.EvasionAlgorithm import EvasionAlgorithm
from evasion.AttackMode import AttackMode
import typing
import configparser
import os


class AttackSettings(ABC):

    def __init__(self, evasion_algorithm: EvasionAlgorithm):
        self.evasion_algorithm: EvasionAlgorithm = evasion_algorithm

    @staticmethod
    @abstractmethod
    def load_settings_from_file(path: str, attack_mode: AttackMode):
        pass

    def dump(self, path: str):
        """
        Dump all settings in a readable text file.
        :param path: path where file will be saved
        """
        with open(os.path.join(path, "settings.txt"), "w+") as text_file:
            for attr, value in self.__dict__.items():
                print("{}: {}".format(attr, value), file=text_file)




class MCTSClassicSettings(AttackSettings):

    def __init__(self, max_outer_iterations: int,
                 max_inner_iterations: int,
                 number_of_sequences_in_random_playout_0: int,
                 number_of_sequences_in_random_playout_further: int,
                 path_length_in_random_playout: int,
                 repeat_template_transformers: int,
                 attack_mode: AttackMode,
                 early_stop: typing.Optional[int]):
        """
        Set up the MCTS Settings...
        :param max_outer_iterations:
        :param max_inner_iterations:
        :param number_of_sequences_in_random_playout_0:
        :param number_of_sequences_in_random_playout_further:
        :param path_length_in_random_playout:
        :param repeat_template_transformers:
        :param attack_mode:
        :param early_stop:
        """
        super(MCTSClassicSettings, self).__init__(EvasionAlgorithm.MCTS_Classic)

        self.max_outer_iterations = max_outer_iterations
        self.max_inner_iterations = max_inner_iterations
        self.number_of_sequences_in_random_playout_0 = number_of_sequences_in_random_playout_0
        self.number_of_sequences_in_random_playout_further = number_of_sequences_in_random_playout_further
        self.path_length_in_random_playout = path_length_in_random_playout
        self.repeat_template_transformers = repeat_template_transformers
        self.attack_mode = attack_mode
        self.early_stop = early_stop


    @staticmethod
    def load_settings_from_file(path: str, attack_mode: AttackMode) -> 'MCTSClassicSettings':
        config = configparser.ConfigParser()
        config.read(path)

        max_outer_iterations = int(config["AMCTS"]["max_outer_iterations"])
        max_inner_iterations = int(config["AMCTS"]["max_inner_iterations"])
        no_seq_random_playout_0 = int(config["AMCTS"]["number_of_sequences_in_random_playout_0"])
        no_seq_random_playout_f = int(config["AMCTS"]["number_of_sequences_in_random_playout_further"])
        path_length_in_random_playout = int(config["AMCTS"]["path_length_in_random_playout"])
        early_stop = int(config["AMCTS"]["early_stop"])

        repeat_template_transformers = int(config["AMCTS"]["repeat_template_transformers"])

        return MCTSClassicSettings(
            max_outer_iterations=max_outer_iterations,
            max_inner_iterations=max_inner_iterations,
            number_of_sequences_in_random_playout_0=no_seq_random_playout_0,
            number_of_sequences_in_random_playout_further=no_seq_random_playout_f,
            path_length_in_random_playout=path_length_in_random_playout,
            repeat_template_transformers=repeat_template_transformers,
            attack_mode=attack_mode,
            early_stop=early_stop
        )


class SimAnnealingSettings(AttackSettings):

    def __init__(self, max_iterations, early_stop, sim_annealing, sim_annealing_params, attack_mode):
        super(SimAnnealingSettings, self).__init__(EvasionAlgorithm.SimAnnealing)

        self.max_iterations = max_iterations
        self.early_stop = early_stop
        self.simulated_annealing = sim_annealing
        self.simulated_annealing_params = sim_annealing_params
        self.attack_mode = attack_mode


    @staticmethod
    def load_settings_from_file(path: str, attack_mode: AttackMode) -> 'SimAnnealingSettings':
        config = configparser.ConfigParser()
        config.read(path)

        max_iterations = int(config["SIMANNEALING"]["max_iterations"])
        simulated_annealing = bool(config["SIMANNEALING"]["simulated_annealing"])
        simulated_annealing_k = int(config["SIMANNEALING"]["simulated_annealing_k"])
        simulated_annealing_ateachiteration = int(config["SIMANNEALING"]["simulated_annealing_ateachiteration"])
        simulated_annealing_decay = float(config["SIMANNEALING"]["simulated_annealing_decay"])
        early_stop = int(config["SIMANNEALING"]["early_stop"])

        return SimAnnealingSettings(
            max_iterations = max_iterations,
            early_stop = early_stop,
            sim_annealing=simulated_annealing,
            sim_annealing_params=(simulated_annealing_k, simulated_annealing_ateachiteration, simulated_annealing_decay),
            attack_mode=attack_mode
        )
