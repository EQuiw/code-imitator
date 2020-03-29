import typing
import subprocess
import os
import copy
import Configuration as Config
from evasion.AttackLogging.Attack_Logging import Logger
from evasion.AttackMode import AttackMode
from evasion.Author import Author
from evasion.Transformers.BasicTransformer import BasicTransformer


class IncludeSortTransformer(BasicTransformer):
    """
    Sort the includes w.r.t to target.
    Consider that clang-format also sorts all includes within a block... so source
    and target will be similar (this transformer makes sense if author uses several blocks with includes
    where each block is separated by an empty line).
    """

    def __init__(self, transformer: str, option: str, uniqueid: str, fillcmdlineoption: str, transformersdir: str,
                 sourceauthor: Author, targetauthor: Author,
                 attack_mode: AttackMode,
                 attackdir: str, logger: Logger, includeinfopath: str):

        includecmdargs: list = []
        super(IncludeSortTransformer, self).__init__(transformer, option, uniqueid, fillcmdlineoption, transformersdir)

        self.src_authiid: str = sourceauthor.authiid
        self.target_author: Author = targetauthor
        self.attackdir: str = attackdir
        self.logger: Logger = logger
        self.attack_mode: AttackMode = attack_mode

        # path to include-info preprocessor
        self.includeinfopath: str = includeinfopath

        # get source includes
        includes_source_ll = self._extract_includes(directory=attackdir, srcfiles=[sourceauthor.authiid],
                                                    cmdargs=includecmdargs)
        self.includes_source = self._parse_includes(includes_source_ll)

        # get target includes
        if attack_mode == AttackMode.IMPERSONATION_WITH_EXAMPLE_FILES and targetauthor.auth_example_iids is not None:
            targetdir = os.path.join(Config.exampledatasetpath, targetauthor.author)
            includes_target_ll = self._extract_includes(directory=targetdir, srcfiles=targetauthor.auth_example_iids,
                                                        cmdargs=includecmdargs)
            self.includes_target = self._parse_includes(includes_target_ll)

            self.logger.logger.debug(
                "IncludeSortTransformer-auth-example-iids: {}:".format(targetauthor.auth_example_iids))
        else:
            self.includes_target = []


        # now we do not remove common elements as done in AddTemplateTransformers.
        # Here, we check what elements in source file need to be sorted w.r.t to target author
        # Our clang-transformer will remove these elements in source file and will add them in correct order
        #  at the beginning of the file... the other non-matching includes remain at the same position..
        self.new_includes_ordered = []
        for it in self.includes_target:
            if it in self.includes_source:
                self.new_includes_ordered.append(it)

        if len(self.new_includes_ordered) > 0:
            self.logger.logger.debug("Sort Listing for {}:".format(self.transformer))
            self.logger.logger.debug("\tSort Elements:" + str(self.new_includes_ordered))


    #@Overwrite
    def __deepcopy__(self, memo):
        """
        overrides deepcopy because we cannot make a deep copy of logger object...
        :param memo:
        :return:
        """
        cls = self.__class__
        result = cls.__new__(cls)
        memo[id(self)] = result

        # copy reference to logging object
        result.logger = self.logger
        # deep copy all except logger
        for k, v in self.__dict__.items():
            if k == 'logger':
                continue
            setattr(result, k, copy.deepcopy(v))

        return result


    # @Overwrite
    def check_valid(self):
        return self.attack_mode == AttackMode.IMPERSONATION_WITH_EXAMPLE_FILES\
                and self.target_author.auth_example_iids is not None and len(self.new_includes_ordered) > 0


    def _parse_includes(self, includes: typing.List[typing.List[str]], **keyword_args) -> typing.List[str]:
        # flatten list
        includes = [y for x in includes for y in x]

        # Remote #include directive from each include string, keep the order with the set
        used = set()
        includes = [x.split("#include")[1].strip() for x in includes if x not in used and (used.add(x) or True)]
        return includes


    # @Overwrite
    def handle_special_case(self, seed: int) -> typing.List[str]:
        """
        If some command line option requires that we fill it.
        We need to fill out the seed if necessary,
        and the library we want to add.
        :param seed: a seed
        :return: the filloption where the necessary fields are set.
        """

        if len(self.new_includes_ordered) == 0:
            raise Exception("include-sort: new_includes_ordered is empty")

        newcmd = "-sort-includes="
        for x in self.new_includes_ordered:
            preparedtoinclude = x.replace("\"", "").replace("\'", ""). \
                replace("<", "").replace(">", "")
            newcmd += preparedtoinclude + "##"

        return [newcmd]




    def _extract_includes(self, directory: str, srcfiles: typing.List[str], cmdargs: typing.List[str]) \
            -> typing.List[typing.List[str]]:
        """
        Calls the code-info tool
        :param directory: where source files are located
        :param srcfiles: the source files where we use the code-info tool
        :return: a list of list of includes (one list = includes for each srcfile in srcfiles).

        This function returns a list of list, because - in this way - we can either flatten the list and
        use them all, or we can look if a string occurs in at least x% of all files and use it then...
        Do all this stuff in _parse_includes that you have to overwrite.
        """

        includes: typing.List[typing.List[str]] = []

        # Collect all includes
        for srcfile in srcfiles:
            curincls = []

            cmdd_transform = [self.includeinfopath, os.path.join(directory, srcfile), *cmdargs, "--", *Config.flag_list]

            p = subprocess.run(cmdd_transform, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False, timeout=145)
            output, err = p.stdout, p.stderr

            if err == b'':
                # parse output, split at each newline and check that not simply empty string..
                for st in output.decode('utf-8').split("\n"):
                    if st != "":
                        curincls.append(st)
            else:
                self.logger.error("AddTemplateTransformer {} has produced error output\n\n{}".format(
                    self.transformer, err.decode("utf-8")))
                raise Exception("AddTemplateTransformer listing no output")

            includes.append(curincls)
        return includes

