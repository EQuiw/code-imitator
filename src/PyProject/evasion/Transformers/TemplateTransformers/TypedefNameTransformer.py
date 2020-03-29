import typing
import math
import random
import numpy as np
# from abc import ABC, abstractmethod
from evasion.AttackLogging.Attack_Logging import Logger
from evasion.AttackMode import AttackMode
from evasion.Author import Author
from evasion.Transformers.TemplateTransformers.AddTemplateTransformer import AddTemplateTransformer


class TypedefNameTransformer(AddTemplateTransformer):

    def __init__(self, transformer: str, option: str, uniqueid: str, fillcmdlineoption: str, transformersdir: str,
                 sourceauthor: Author, targetauthor: Author,
                 attack_mode: AttackMode,
                 attackdir: str, logger: Logger, includeinfopath: str):

        includecmdargs: list = ["-listing=typedefs"]
        super(TypedefNameTransformer, self).__init__(transformer, option, uniqueid, fillcmdlineoption, transformersdir,
                 sourceauthor, targetauthor,
                 attack_mode,
                 attackdir, logger, includeinfopath, includecmdargs
        )

    # @Overwrite
    def _parse_includes(self, includes: typing.List[typing.List[str]], **keyword_args) -> typing.List[str]:
        # flatten list
        includes = [y for x in includes for y in x]

        # keep order of list, remove same strings
        used = set()
        includes = [x.strip() for x in includes if x not in used and (used.add(x) or True)]
        return includes


    # @Overwrite
    def _get_default_target_values(self):
        return [
            "long double##long double##ld##ld##",
            "long long##long long##ll##ll##",
            "long long##long long##LL##LL##",
            "pair<int, int>##pair<int, int>##ii##ii##(utility;pair),",
            "pair<int, int>##pair<int, int>##pii##pii##(utility;pair),",
            "pair<int, int>##pair<int, int>##PII##PII##(utility;pair),",
            "unsigned long long##unsigned long long##ull##ull##",
            "vector<int>##vector<int>##vi##vi##(vector;vector),",
            "vector<int>##vector<int>##VI##VI##(vector;vector),",
            "long double##long double##LD##LD##",
            "set<int>##set<int>##si##si##(set;set),",
            "vector<vector<int> >##vector<vector<int> >##vvi##vvi##(vector;vector),(vector;vector),"
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
            self.logger.logger.error("include-add: notargets == 0 and toinclude is not set!")
            raise Exception("include-typedef: notargets == 0 and toinclude is not set!")

        # B. get elements
        assert percentageofincludes is not None
        num_to_select = math.ceil(len(self.includes_target) * percentageofincludes)
        assert num_to_select <= len(self.includes_target)

        # choose randomly, but keep the order in the list.
        list_of_random_items = [self.includes_target[i] for i in
                                    sorted(random.sample(range(len(self.includes_target)), num_to_select))]

        newcmdline.extend(["-typedefs=\"" + x + "\"" for x in list_of_random_items])
        # cleaning...
        for x in list_of_random_items:
            self.includes_target.remove(x)

        return newcmdline