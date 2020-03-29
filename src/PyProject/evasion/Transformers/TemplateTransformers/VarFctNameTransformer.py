import random
import typing
import numpy as np
import Configuration as Config
from types import SimpleNamespace
import os

from evasion.AttackLogging.Attack_Logging import Logger
from evasion.AttackMode import AttackMode
from evasion.Author import Author
from evasion.Transformers.TemplateTransformers.AddTemplateTransformer import AddTemplateTransformer



class VarFctNameTransformer(AddTemplateTransformer):

    def __init__(self, transformer: str, option: str, uniqueid: str, fillcmdlineoption: str, transformersdir: str,
                 sourceauthor: Author, targetauthor: Author,
                 attack_mode: AttackMode,
                 attackdir: str, logger: Logger, includeinfopath: str):

        if uniqueid.endswith(":function"):
            includecmdargs: list = ["-listing=fctnames"]
            self.fctname_mode = True
        elif uniqueid.endswith(":variable"):
            includecmdargs: list = ["-listing=varnames"]
            self.fctname_mode = False
        else:
            raise Exception("Unsupported unique id for VarFctNameTransformer")

        parse_include_args = {'min_coverage': 0.55}
        super(VarFctNameTransformer, self).__init__(transformer, option, uniqueid, fillcmdlineoption, transformersdir,
                 sourceauthor, targetauthor,
                 attack_mode,
                 attackdir, logger, includeinfopath, includecmdargs, **parse_include_args
        )

        # ** Settings for white-box **
        # we redefine here self.toinclude from a single string to a tuple with two strings,
        #   it saves the from- and into decl-name that we could pass
        self.toinclude = SimpleNamespace(from_declname_passed=None, into_declname_passed=None)

        # history of rewritings, relevant for white-box setting, so that we do not pass the same name again...
        # in black-box setting, we simply remove the selected name from set of possible names..
        self.into_declname_history: typing.List[str] = []
        self.from_declname_history: typing.List[str] = []


        # ** Extract more information**
        # Check that the target names do not already exist. To this end, we need to extract all declaration names
        all_decl_names_ll = self._extract_includes(directory=attackdir, srcfiles=[sourceauthor.authiid], cmdargs=["-listing=all_decl_names"])
        all_decl_names = self._parse_includes(all_decl_names_ll, **parse_include_args)
        self.includes_target = [x for x in self.includes_target if x not in all_decl_names]

        # Now consider only source names that are common in previous source author files
        sourcesdir = os.path.join(Config.datasetpath, sourceauthor.author)
        includes_sources_ll = self._extract_includes(directory=sourcesdir, srcfiles=sourceauthor.all_authiids_train, cmdargs=includecmdargs)
        kw_args = {'min_coverage': 0.25}
        includes_sources_all = self._parse_includes(includes=includes_sources_ll, **kw_args)

        self.includes_source: list = sorted(list(set.intersection(set(includes_sources_all), set(self.includes_source))))
        self.logger.logger.debug("\tFinal Src Names:" + str(self.includes_source))



    # @Overwrite
    def _parse_includes(self, includes: typing.List[typing.List[str]], **keyword_args) -> typing.List[str]:

        # kw_args may have 'min_coverage' param, if not, use default mode...
        if 'min_coverage' in keyword_args:
            returned_includes = []
            for x in [y for x in includes for y in x]:
                ratio = np.sum(np.array([1 for y in includes if x in y])) / len(includes)
                if ratio >= keyword_args["min_coverage"]:
                    returned_includes.append(x)
        else:
            returned_includes = [y for x in includes for y in x]

        # keep order of list, remove same strings
        used = set()
        returned_includes = [x.strip() for x in returned_includes if x not in used and (used.add(x) or True)]
        return returned_includes


    # @Overwrite
    def _get_default_target_values(self):
        if self.fctname_mode is False:
            return ["tc", "i", "j", "a", "b", "c", "d", "t", "T", "r", "s", "x", "y", "n", "p", "q", "v", "N", "ans"]
        else:
            return ["get", "solve"]


    # @Overwrite
    def check_valid(self):
        return len(self.includes_target) > 0 or len(self.includes_source) > 0 \
               or self.toinclude.from_declname_passed is not None or self.toinclude.into_declname_passed is not None

    # @Overwrite
    def obtain_unique_last_state_id(self) -> str:
        """
        We need to overwrite the parent method.
        For VarFctName Transformer, we have a very ugly special case.
        Assume we have no from or into name, then we let it empty and let the transformer decide
        what it can take.
        from_declname="" -into_declname="solve" -seed=4351
        from_declname="" -into_declname="solve" -seed=2211
        are thus different transformers.
        But if we have:
        from_declname="compute" -into_declname="solve" -seed=4351
        from_declname="compute" -into_declname="solve" -seed=2211
        These are the same transformers!
        :return: unique state id
        """
        _, _, transformer_options, _ = self.load_information_about_last_call()
        we_need_seed: bool = False
        for x in transformer_options:
            if x == "-from_declname=\"" + "" + "\"" or "-into_declname=\"" + "" + "\"":
                we_need_seed = True

        if we_need_seed is False:
            state_id: str = self.uniqueid + "_".join([x for x in transformer_options if not x.startswith("-seed=")])
        else:
            state_id: str = self.uniqueid + "_".join([x for x in transformer_options])

        return state_id

    #@Overwrite
    def handle_special_case(self, seed: int) -> typing.List[str]:
        np.random.seed(seed + 34)
        random.seed(seed + 33)

        # iterate over all options, separated by semicolon ;
        newcmdline = []
        # we set from_ and into_declname to None, to just call the nametransformer once.. we check their value later
        from_declname = None
        into_declname = None

        for currentfilloption in self.fillcmdlineoption.split(";"):
            if currentfilloption == "seed":
                newcmdline.append("-seed=" + str(np.random.randint(0, 5000)))

            elif currentfilloption == "from_declname":
                if from_declname is None:
                    from_declname, into_declname = self.__chooseFromAndIntoName()
                newcmdline.append("-from_declname=\"" + from_declname + "\"")

            elif currentfilloption=="into_declname":
                if into_declname is None:
                    from_declname, into_declname = self.__chooseFromAndIntoName()
                newcmdline.append("-into_declname=\"" + into_declname + "\"")

            else:
                raise Exception("No valid filloption specified")


        return newcmdline


    def __chooseFromAndIntoName(self) -> typing.Tuple[str, str]:
        """
        Determine from_declname and into_declname for name transforming
        :return: a tuple with from and into name.
        """

        # a. variable declaration
        from_declname: str = ""
        into_declname: str = ""

        # From
        if self.toinclude.from_declname_passed is not None:
            # white box has priority
            from_declname = self.toinclude.from_declname_passed
            self.toinclude.from_declname_passed = None
            self.from_declname_history.append(from_declname)
        else:
            # choose name from pool of possible names
            if len(self.includes_source) > 0:
                chosenelem: int = random.randint(0, len(self.includes_source) - 1)
                from_declname = self.includes_source[chosenelem]
                self.from_declname_history.append(from_declname)

        if from_declname in self.includes_source:
            self.includes_source.remove(from_declname)


        # Into
        if self.toinclude.into_declname_passed is not None:
            # white box has priority
            into_declname = self.toinclude.into_declname_passed
            self.toinclude.into_declname_passed = None
            self.into_declname_history.append(into_declname)
        else:
            # choose name from pool of possible names
            if len(self.includes_target) > 0:
                chosenelem: int = random.randint(0, len(self.includes_target) - 1)
                into_declname = self.includes_target[chosenelem]
                self.into_declname_history.append(into_declname)

        if into_declname in self.includes_target:
            self.includes_target.remove(into_declname)

        return from_declname, into_declname


    # @Overwrite
    def pass_target_feature_value(self, feature_value: str, direction: str):
        assert direction == "Increase" or direction == "Decrease"
        assert self.toinclude.into_declname_passed is None and self.toinclude.from_declname_passed is None

        spltstr = "_".join(feature_value.split("_")[1:])
        possible_var_name: str = feature_value.split("_")[0]

        if len(possible_var_name) != 1:
            # so far, only working for single letters, t and T and so on... TODO
            return
        if possible_var_name.isdigit():
            return

        if spltstr == "unigram" or spltstr.startswith("code_in_ast_leaves_"):
            # if direction is increase, decrease
            if direction == "Increase":
                if possible_var_name in self.includes_source or possible_var_name in self.into_declname_history:
                    # we do not pass feature value if var name is already present in source file as variable or fct name
                    # or if we have already rewritten some variable into given feature value
                    return
                self.toinclude.into_declname_passed = possible_var_name
            else:
                if possible_var_name not in self.includes_source or possible_var_name in self.from_declname_history:
                    return
                self.toinclude.from_declname_passed = possible_var_name

            self.logger.debug_details("Name Transformer--Whitebox: Try to {} : {}".format(direction, feature_value)) # todo
