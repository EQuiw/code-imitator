import typing
import math
import random
import numpy as np
# from abc import ABC, abstractmethod
from evasion.AttackLogging.Attack_Logging import Logger
from evasion.AttackMode import AttackMode
from evasion.Author import Author
from evasion.Transformers.TemplateTransformers.AddTemplateTransformer import AddTemplateTransformer


class IncludeAddTransformer(AddTemplateTransformer):

    def __init__(self, transformer: str, option: str, uniqueid: str, fillcmdlineoption: str, transformersdir: str,
                 sourceauthor: Author, targetauthor: Author,
                 attack_mode: AttackMode,
                 attackdir: str, logger: Logger, includeinfopath: str):

        includecmdargs: list = []
        super(IncludeAddTransformer, self).__init__(transformer, option, uniqueid, fillcmdlineoption, transformersdir,
                 sourceauthor, targetauthor,
                 attack_mode,
                 attackdir, logger, includeinfopath, includecmdargs
        )


    # @Overwrite
    def _parse_includes(self, includes: typing.List[typing.List[str]], **keyword_args) -> typing.List[str]:
        # flatten list
        includes = [y for x in includes for y in x]

        # Remote #include directive from each include string, keep the order with the set
        used = set()
        includes = [x.split("#include")[1].strip() for x in includes if x not in used and (used.add(x) or True)]
        return includes


    # @Overwrite
    def _get_default_target_values(self):
        return ["<cassert>", "<algorithm>", "<cmath>", "<cstdio>", "<cstdlib>", "<cstring>",
                "<iostream>", "<map>", "<set>", "<vector>", "<string>", "<bits/stdc++.h>", "<stack>",
                "<bitset>", "<complex>", "<iomanip>", "<ctime>", "<list>", "<queue>", "<stdio.h>",
                "<utility>", "<sstream>", "<fstream>", "<numeric>", "<functional>", "<deque>",
                "<cctype>", "<climits>", "<iterator>", "<stdlib.h>", "<math.h>", "<unordered_map>"]

    # @Overwrite
    def handle_special_case(self, seed: int) -> typing.List[str]:
        """
        If some command line option requires that we fill it.
        We need to fill out the seed if necessary,
        and the library we want to add.
        :param seed: a seed
        :return: the filloption where the necessary fields are set.
        """

        # iterate over all options, separated by semicolon ;
        newcmdline = []
        np.random.seed(seed + 34)
        random.seed(seed + 33)

        assert "quoted_headers" in self.fillcmdlineoption or "angled_headers" in self.fillcmdlineoption

        # A. Process cmd line options (except headers)
        percentageofheaders: typing.Optional[float] = None # how many headers do we want to add

        for currentfilloption in self.fillcmdlineoption.split(";"):
            if currentfilloption=="angled_headers" or currentfilloption=="quoted_headers":
                pass # done later
            elif "percofheaders" in currentfilloption:
                percentageofheaders = float(currentfilloption.split("=")[1])
            else:
                raise Exception("No valid filloption specified")


        # B. Now process header information
        # Check: following should not be true, otherwise check_valid was not called properly
        if len(self.includes_target) == 0 and self.toinclude is None:
            self.logger.logger.error("include-add: notargets == 0 and toinclude is not set!")
            raise Exception("include-add: notargets == 0 and toinclude is not set!")

        # if include is already specified via pass_target_feature_value, use it otherwise choose from list
        if self.toinclude is None:
            # if percentageofheaders was not passed, per default, we choose one element.
            assert percentageofheaders is not None
            num_to_select = math.ceil(len(self.includes_target)*percentageofheaders)
            assert num_to_select <= len(self.includes_target)

            # choose randomly, but keep the order in the list.
            list_of_random_items = [self.includes_target[i] for i in sorted(random.sample(range(len(self.includes_target)), num_to_select))]
            newcmdline.extend(IncludeAddTransformer.__create_include(incl_list=list_of_random_items))
            # cleaning...
            for x in list_of_random_items:
                self.includes_target.remove(x)
        else:
            newcmdline.extend(IncludeAddTransformer.__create_include(incl_list=[self.toinclude]))
            # cleaning...
            if self.toinclude in self.includes_target:
                self.includes_target.remove(self.toinclude)
            self.toinclude = None

        return newcmdline


    @staticmethod
    def __create_include(incl_list):
        newcmdline = []
        for incl in incl_list:
            # prepare header:
            # Remove either " ... " or < ... >
            isangled = "<" in incl and ">" in incl
            preparedtoinclude = incl.replace("\"", "").replace("\'", ""). \
                replace("<", "").replace(">", "")
            if isangled:
                newcmdline.append("-angled_headers=" + preparedtoinclude)  # + "\"
            else:
                newcmdline.append("-quoted_headers=" + preparedtoinclude)  # + "\"
        return newcmdline



    # @Overwrite
    def pass_target_feature_value(self, feature_value: str, direction: str):

        # we get e.g. cstdio_unigram_tf_ as input, get the first part
        if feature_value.split("_")[1] == "unigram":
            possibleincludename: str = feature_value.split("_")[0]

            # Unfortunately, the feature unigram extraction removes parts such as .h or angles, and even the
            # path such as <bits/stdc++.h> ..
            # Therefore, we use the includes from target list to find out how the target looks like...
            # For instance, we get stdc and in target list, we find stdc.h,
            # then we know that 'toinclude' should be stdc.h
            matched_includes: typing.List[str] = [x for x in self.includes_target if possibleincludename in x]

            #curfile = os.path.join(Config.datasetpath, os.path.pardir, "includes.dat")
            #includes_all = [line.rstrip('\n') for line in open(curfile, "r", encoding='ISO-8859-1')]
            # TODO here also with current target file or with all includes ever seen
            # also provide this method for nametransformer.

            # we should only match one include
            if len(matched_includes) != 1:
                self.logger.error("IncludeAddTransformer: Matched zero or multiple values:{} ; {}".format(
                    feature_value, "---".join(matched_includes)
                ))
            else:
                self.toinclude = matched_includes[0]

