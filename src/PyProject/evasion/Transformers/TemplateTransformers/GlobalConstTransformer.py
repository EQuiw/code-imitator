import typing
import math
import random
import numpy as np
# from abc import ABC, abstractmethod
from evasion.AttackLogging.Attack_Logging import Logger
from evasion.AttackMode import AttackMode
from evasion.Author import Author
from evasion.Transformers.TemplateTransformers.AddTemplateTransformer import AddTemplateTransformer


class GlobalConstTransformer(AddTemplateTransformer):

    def __init__(self, transformer: str, option: str, uniqueid: str, fillcmdlineoption: str, transformersdir: str,
                 sourceauthor: Author, targetauthor: Author,
                 attack_mode: AttackMode,
                 attackdir: str, logger: Logger, includeinfopath: str):

        includecmdargs: list = ["-listing=global_consts"]
        parse_include_args = {'min_coverage': 0.55}
        super(GlobalConstTransformer, self).__init__(transformer, option, uniqueid, fillcmdlineoption, transformersdir,
                 sourceauthor, targetauthor,
                 attack_mode,
                 attackdir, logger, includeinfopath, includecmdargs, **parse_include_args
        )

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
        return [
            "INF##const int INF = 1000000000;",
            "MOD##const int MOD = 1000000007;",
            "EPS##const double EPS = 1e-9;",
            "eps##const double eps = 1e-9;",
            "PI##const long double PI = 3.1415926535897932384626433832795;",
            "MAXN##const int MAXN = 1005;",
            "mod##const int mod = 1000000007;"
        ]


    # @Overwrite
    def handle_special_case(self, seed: int) -> typing.List[str]:
        newcmdline = []
        np.random.seed(seed + 34)
        random.seed(seed + 33)

        # A. Process cmd line options (except headers)
        percentageofincludes = None # how many typedefs do we want to add?

        for currentfilloption in self.fillcmdlineoption.split(";"):
            if "percofincludes" in currentfilloption:
                percentageofincludes = float(currentfilloption.split("=")[1])
            else:
                raise Exception("No valid filloption specified")

        # Check: following should not be true, otherwise check_valid was not called properly
        if len(self.includes_target) == 0 and self.toinclude is None:
            self.logger.logger.error("include-global-const: notargets == 0 and toinclude is not set!")
            raise Exception("include-global-const: notargets == 0 and toinclude is not set!")

        # B. get elements
        assert percentageofincludes is not None
        num_to_select = math.ceil(len(self.includes_target) * percentageofincludes)
        assert 1 <= num_to_select <= len(self.includes_target)

        # choose randomly, but keep the order in the list.
        list_of_random_items = [self.includes_target[i] for i in
                                    sorted(random.sample(range(len(self.includes_target)), num_to_select))]

        newcmdline.extend(["-global_const=\"" + x + "\"" for x in list_of_random_items])
        # cleaning...
        for x in list_of_random_items:
            self.includes_target.remove(x)

        return newcmdline