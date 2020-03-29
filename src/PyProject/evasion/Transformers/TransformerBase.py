from abc import ABC, abstractmethod
import typing

class TransformerBase(ABC):
    """
    This class represents a single code transformer.
        It either represents a clang-based transformer or an external transformer.
        This class has abstract functions that need to be implemented.
    """

    def __init__(self, transformer: str, option: str, uniqueid: str, fillcmdlineoption: str):
        self.transformer: str = transformer

        self.option: typing.List[str] = []
        for selected_option in option.split(";"):
            self.option.append(selected_option)
        # filter empty entries such as '' -- they will cause problems later in subprocess
        self.option = list(filter(None, self.option))

        self.uniqueid: str = uniqueid
        self.fillcmdlineoption: str = fillcmdlineoption # needs to be filled at runtime


        # three variables to save some information about the last call each time.
        self.__last_cmdtransform = None
        self.__last_cmdtransform_simplified = None
        self.__last_options_filled = None
        self.__last_seed = None


    def _save_information_about_last_call(self, set_cmdtransform, set_cmdtransform_simplified, set_options, set_seed):
        # Call this method after each dotransformercall or getsubprocesscall
        self.__last_cmdtransform = set_cmdtransform
        self.__last_cmdtransform_simplified = set_cmdtransform_simplified
        self.__last_options_filled = set_options
        self.__last_seed = set_seed


    def load_information_about_last_call(self) -> typing.Tuple[str, str, list, int]:
        if self.__last_cmdtransform is None or self.__last_cmdtransform_simplified is None\
                or self.__last_options_filled is None or self.__last_seed is None:
            raise Exception("Save_information_about_last_call was not called at transformer. Wrong implementation?")
        return self.__last_cmdtransform, self.__last_cmdtransform_simplified, self.__last_options_filled, self.__last_seed


    def obtain_unique_last_state_id(self) -> str:
        _, _, transformer_options, _ = self.load_information_about_last_call()
        state_id: str = self.uniqueid + "_".join([x for x in transformer_options if not x.startswith("-seed=")])
        return state_id


    @abstractmethod
    def dotransformercall(self, source_file, target_file, seed) -> typing.Tuple:
        pass

    @abstractmethod
    def getsubprocesscall(self, source_file, seed) -> typing.Tuple:
        pass

    @abstractmethod
    def check_valid(self):
        pass


    @abstractmethod
    def handle_special_case(self, seed: int) -> typing.List[str]:
        """
        If some command line option requires that we fill it.
        We need to fill out the seed if necessary, or if declaration name transforming we need to choose the names.
        :param seed: a seed
        :return: the filloption where the necessary fields are set.
        """
        pass

    @abstractmethod
    def pass_target_feature_value(self, feature_value: str, direction: str) -> None:
        """
        In a white-box attack, we can pass the feature value that we'd like to change.
        If possible, a transformer can adapt its transformation call due to this information.
        For instance, an IncludeTransformer would not randomly select an include, but would
        select the include that would add the feature value.

        Do not use this method in a black-box setting.
        # TODO - we should remove this function, as we did not implement white-box attacks.
        :param feature_value: a string that specifies the feature that we want to change
        :param direction: a string that tells transformer if we want to increase or decrease
        the feature's value. Should be 'Increase' or 'Decrease'
        """