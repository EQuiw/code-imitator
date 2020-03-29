import Configuration as Config
import os
import typing
from abc import abstractmethod
from evasion.AttackLogging.Attack_Logging import Logger
from evasion.AttackMode import AttackMode
from evasion.Author import Author
import copy
from evasion.Transformers.BasicTransformer import BasicTransformer
import subprocess


class AddTemplateTransformer(BasicTransformer):
    """
    Responsible for transformations that are based on code-info tools, such as var names, fct names...
    It calls a code-info tool for a source file to collect more information.

    This transformer memorizes its actions so that it does not try to add s.th.
    that has been added before.

    Instructions:
    1. Write an own code-info tool.
        Examples are the tools in LibToolingAST/codeinfo, e.g. list all headers, list all variable names, ...
    2. Adapt config_transformeroptions.csv
    3. Create new class that inherits from this class
        Overwrite parse_include_args.
    4. Implement _parse_includes: This method will parse all lines from the code-info tool
        Use the includecmdargs to pass some command line options to the code-info tool
        Use parse_include_args to pass some commands for parsing, e.g. if we only want to keep a string
        if it is present in at least x% of all code files.

    """

    def __init__(self, transformer: str, option: str, uniqueid: str, fillcmdlineoption: str, transformersdir: str,
                 sourceauthor: Author, targetauthor: Author,
                 attack_mode: AttackMode,
                 attackdir: str, logger: Logger, includeinfopath: str,
                 includecmdargs: typing.List[str], **parse_include_args):
        """
        Instantiate AddTemplateTransformer.
        :param transformer: the transformer that this class will call to change source code
        :param option: its options
        :param uniqueid: the unique id for transformer
        :param fillcmdlineoption: its cmd line options
        :param transformersdir: its directory
        :param sourceauthor: source author
        :param targetauthor: target author (= source author if dodging attack)
        :param attack_mode: set true if we currently perform an impersonation attack, if we have no
                target_authiids (= example files of author), we will try some default values at least.
        :param attackdir: the current attack directory
        :param logger: the logger
        :param includeinfopath: the path where the code-info tool is located
        :param includecmdargs: cmd args that will be passed to the code-info tool
        :param parse_include_args: the args that can be passed to method _parse_includes to parse the results
        from the code-info tool
        """

        super(AddTemplateTransformer, self).__init__(transformer, option, uniqueid, fillcmdlineoption, transformersdir)

        self.src_authiid: str = sourceauthor.authiid
        self.attackdir: str = attackdir
        self.logger: Logger = logger
        self.attack_mode: AttackMode = attack_mode

        # path to include-info preprocessor
        self.includeinfopath: str = includeinfopath
        # in white-box attack, we can also specify the include we want
        self.toinclude: typing.Optional[str] = None

        includes_source_ll = self._extract_includes(directory=attackdir, srcfiles=[sourceauthor.authiid], cmdargs=includecmdargs)
        self.includes_source = self._parse_includes(includes_source_ll, **parse_include_args)


        if attack_mode == AttackMode.IMPERSONATION_WITH_EXAMPLE_FILES or\
            attack_mode == AttackMode.IMPERSONATION_WITHOUT_EXAMPLE_FILES:
            assert sourceauthor.true_class != targetauthor.true_class # just small check

            if attack_mode == AttackMode.IMPERSONATION_WITH_EXAMPLE_FILES and targetauthor.auth_example_iids is None:
                self.logger.error("No example file(s) for author {}. I will use default values.".format(sourceauthor.authiid))
                includes_target = self._get_default_target_values()

            elif attack_mode == AttackMode.IMPERSONATION_WITH_EXAMPLE_FILES and targetauthor.auth_example_iids is not None:
                targetdir = os.path.join(Config.exampledatasetpath, targetauthor.author)
                includes_target_ll = self._extract_includes(directory=targetdir, srcfiles=targetauthor.auth_example_iids, cmdargs=includecmdargs)
                includes_target = self._parse_includes(includes_target_ll, **parse_include_args)
            else:
                # some default values
                includes_target = self._get_default_target_values()

            # remove commom elements: S \ T for source, T \ S for target
            self.includes_target = [x for x in includes_target if x not in self.includes_source]
            # remove also in source all occurences that are in includes_target, as we would
            # loose similarity by removing them...
            self.includes_source = [x for x in self.includes_source if x not in includes_target]

            self.logger.logger.debug("Element Listing for {}:".format(self.transformer))
            self.logger.logger.debug("\tTarget Elements:" + str(self.includes_target))

        elif attack_mode == AttackMode.DODGING:
            assert sourceauthor.true_class == targetauthor.true_class # just small check
            self.includes_target = []
        else:
            raise Exception("Unknown attack mode")


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

    #@Overwrite
    def check_valid(self):
        """
        Checks if can be called once more.
        :return: true if so.
        """
        return len(self.includes_target) > 0 or self.toinclude is not None


    @abstractmethod
    def _parse_includes(self, includes: typing.List[typing.List[str]], **keyword_args) -> typing.List[str]:
        """
        Process includes list of list and return list of includes.
        :param includes: list of list
        :param **keyword_args: a variable number of args that could be passed to fct.
        :return: list
        """
        pass


    @abstractmethod
    def _get_default_target_values(self):
        pass


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


