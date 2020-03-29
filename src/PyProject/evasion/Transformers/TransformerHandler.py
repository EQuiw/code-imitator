import Configuration as Config
import os
import pandas
import typing
from evasion.AttackLogging.Attack_Logging import Logger
import copy
from evasion.Transformers.TransformerBase import TransformerBase
from evasion.Transformers.BasicTransformer import BasicTransformer
from evasion.Transformers.Ext_IWYUTransformer import ExternalIncludeWhatYouUseTransformer

from evasion.Transformers.TemplateTransformers.AddTemplateTransformer import AddTemplateTransformer
from evasion.Transformers.TemplateTransformers.TypedefNameTransformer import TypedefNameTransformer
from evasion.Transformers.TemplateTransformers.IncludeAddTransformer import IncludeAddTransformer
from evasion.Transformers.TemplateTransformers.VarFctNameTransformer import VarFctNameTransformer
from evasion.Transformers.TemplateTransformers.GlobalConstTransformer import GlobalConstTransformer
from evasion.Author import Author
from evasion.AttackMode import AttackMode


class TransformerHandler:
    """
    This class is the interface to the transformers based on clang that are callable from shell.

    This class determines the possible transformations by scanning the directory where each transformer executable
    should be. This class can return the next possible transformer during the evasion attack.
    Moreover, for special cases such as variable renaming, it determines the possible var names and provides
    the usable varrename transformer.

    If you get an exception with "loaded table contains...", then clean cmake-build dir., compile all transformers again
    """

    def __init__(self, sourceauthor: Author, targetauthor: Author, attackdir: str, attack_mode: AttackMode, logger: Logger):

        if not os.path.exists(Config.transformersdir):
            raise Exception("transformersdir does not exist")

        self.logger: Logger = logger
        self.attackdir = attackdir

        # create a list that contains a transformer object that encapsulates a possible code transformation
        self.transformerslist: typing.List['TransformerBase'] = self.__load_config_transformeroptions_csv(
            pathdf=Config.transformercsvfile, transformersdir=Config.transformersdir, attack_mode=attack_mode,
            codeinfodir=Config.codeinfodir, sourceauthor=sourceauthor, targetauthor=targetauthor)

        externaltransf: typing.List['TransformerBase'] = self.__load_external_transformers(
                                                                pathdf=Config.externaltransformercsvfile)
        self.transformerslist.extend(externaltransf)


        self.logger.logger.debug("Loaded transformers:" + str([x.uniqueid for x in self.transformerslist]))


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


    def get_random_transformation(self, seed: int) -> TransformerBase:
        """
        Get an arbitrary next transformation.
        :param seed: a seed
        :return: the transformer as transformer object.
        """
        raise NotImplementedError()
        # return self.__get_next_equal_transformerindex(seed=seed)


    def get_specified_transformation_per_index(self, index:int) -> TransformerBase:
        """
        Get the next transformation that is specified based on index.
        :param index: the index for transformer list
        :return: the transformer as transformer object.
        """
        return self.transformerslist[index]


    def get_specified_transformation_per_uniqueid(self, uniqueid: str) -> TransformerBase:
        """
        Get the next transformer based on its unique name.
        :param uniqueid: the name that was specified in transformer csv.
        :return: the transformer as transformer object.
        """
        for tr in self.transformerslist:
            if tr.uniqueid == uniqueid:
                return tr
        raise Exception("Transformer Name not found")


    def update_check_number_available_transformers(self) -> int:
        """
        Checks how many transformers are valid, removes them from table if unvalid and returns the number of usable
        transformers.
        :return: no of usable transformers
        """

        unvalidtransformers = [x.check_valid() for x in self.transformerslist]
        for i in reversed(range(0, len(unvalidtransformers))):
            if not unvalidtransformers[i]:
                del self.transformerslist[i]

        return len(self.transformerslist)


    def get_transformer_uniqueids(self) -> typing.List[str]:
        """
        get a list of the respective unique names of each transformer
        :return:
        """
        return [x.uniqueid for x in self.transformerslist]


    def get_addtemplate_transformer_indices(self) -> typing.List[int]:

        retlist: typing.List[int] = []
        for i, tr in enumerate(self.transformerslist):
            if isinstance(tr, AddTemplateTransformer):
                retlist.append(i)
        return retlist


    def __get_transformer_list(self, transformersdir: str) -> typing.Dict[str, str]:
        """
        Reads the possible (compiled) clang-based transformers that we can call.
        It looks for executables that are in transformersdir (e.g. the cmake-build-release dir) and
        end with "transformer". This is a naming convention that we use to find all transformer executables.
        :param transformersdir: the cmake-build-directory.
        :return: a dict of callable transformers (each saved as its name as key and its path as value)
        """

        # transformers = [f for f in os.listdir(transformersdir) if os.path.isfile(os.path.join(transformersdir, f))]
        # transformers = [x for x in transformers if x.endswith("transformer")]

        transformers = {}
        for root, directories, filenames in os.walk(transformersdir):
            for filename in filenames:
                if filename.endswith("transformer"):
                    # check
                    if filename in transformers:
                        raise Exception("Two transformers (maybe in different dir's) with same name?")
                    # add
                    transformers[filename] = root

        return transformers


    def __load_config_transformeroptions_csv(self, pathdf: str, transformersdir: str,
                                             codeinfodir: str,
                                             attack_mode: AttackMode,
                                             sourceauthor: Author, targetauthor: Author
                                             ) -> typing.List['TransformerBase']:
        """
        Load data frame from config_transformeroptions.csv.
        :param pathdf: the path to config_transformeroptions.csv.
        :param: transformersdir: path to dir where we find compiled transformers that are callable. Is used to check that loaded
        table does not contain any transformer that was not compiled.
        :param codeinfodir: path to dir where code-info tools are located.
        :param attack_mode: the attack mode (dodging, impersonation with or without example file(s))
        :param sourceauthor: source author
        :param targetauthor: target author
        :return: a list of transformers
        """

        # load
        transformerdict: typing.Dict[str, str] = self.__get_transformer_list(
            transformersdir=transformersdir)
        df: pandas.DataFrame = pandas.read_csv(pathdf)
        df = df.fillna("")

        # check & debug
        if not set(df.transformer).issubset(set(transformerdict.keys())):
            raise Exception("Loaded table contains a transformer that was not compiled")


        # convert to python objects
        transformerobjects: typing.List['TransformerBase'] = []
        for index, row in df.iterrows():
            if row['Python-class'] == "base":
                transformerobjects.append(BasicTransformer(transformer=row['transformer'],
                                                           option=row['option'], uniqueid=row['uniqueid'],
                                                           fillcmdlineoption=row['fillcmdlineoptions'],
                                                           transformersdir=transformerdict[row['transformer']]))

            elif row['Python-class'].startswith("AddTemplateTransformer"):
                tr: AddTemplateTransformer = self.__create_AddTemplateTransformers(row=row,
                                                                                   transformerdict=transformerdict,
                                                                                   attack_mode=attack_mode,
                                                                                   sourceauthor=sourceauthor,
                                                                                   targetauthor=targetauthor,
                                                                                   codeinfodir=codeinfodir)
                transformerobjects.append(tr)

            else:
                tr = self.__load_further_transformers(row=row,
                                                      transformerdict=transformerdict,
                                                      attack_mode=attack_mode,
                                                      sourceauthor=sourceauthor,
                                                      targetauthor=targetauthor,
                                                      codeinfodir=codeinfodir)
                transformerobjects.append(tr)


        assert len(transformerobjects) == df.shape[0]
        return transformerobjects


    def __create_AddTemplateTransformers(self, row, transformerdict, attack_mode: AttackMode,
                                         sourceauthor: Author, targetauthor: Author, codeinfodir):
        """
        Create various transformers that follow the AddTemplateTransformer structure.
        All these transformers first create a set of information, memorize their actions and pass these information
        to the respective Clang transformer. For example, the include-add transformer first extracts common
        headers from the dataset, and then passes possible headers to the clang-transformer.
        :param row: row information from config_trnasformeroptions.csv
        :param transformerdict: ...
        :param attack_mode: if impersonation attack (with / without example file(s)) or dodging attack
        :param sourceauthor: Source Author
        :param targetauthor: Target Author
        :param codeinfodir: the path to the tool in codeinfo in clang, that returns the dataset information.
        :return: an transformer that inherits from AddTemplateTransformer.
        """
        if row['Python-class'].endswith("/TypedefNameTransformer"):

            tr: TypedefNameTransformer = TypedefNameTransformer(transformer=row['transformer'],
                                                                option=row['option'],
                                                                uniqueid=row['uniqueid'],
                                                                fillcmdlineoption=row['fillcmdlineoptions'],
                                                                transformersdir=transformerdict[row['transformer']],
                                                                sourceauthor=sourceauthor,
                                                                targetauthor=targetauthor,
                                                                attack_mode=attack_mode,
                                                                attackdir=self.attackdir,
                                                                logger=self.logger,
                                                                includeinfopath=os.path.join(
                                                                    codeinfodir, row['Specific-Arguments']))
        elif row['Python-class'].endswith("/IncludeAddTransformer"):
            tr: IncludeAddTransformer = IncludeAddTransformer(transformer=row['transformer'],
                                                              option=row['option'],
                                                              uniqueid=row['uniqueid'],
                                                              fillcmdlineoption=row['fillcmdlineoptions'],
                                                              transformersdir=transformerdict[row['transformer']],
                                                              sourceauthor=sourceauthor,
                                                              targetauthor=targetauthor,
                                                              attack_mode=attack_mode,
                                                              attackdir=self.attackdir,
                                                              logger=self.logger,
                                                              includeinfopath=os.path.join(codeinfodir,
                                                                  row['Specific-Arguments']))
        elif row['Python-class'].endswith("/VarFctNameTransformer"):
            tr: VarFctNameTransformer = VarFctNameTransformer(transformer=row['transformer'],
                                                              option=row['option'],
                                                              uniqueid=row['uniqueid'],
                                                              fillcmdlineoption=row['fillcmdlineoptions'],
                                                              transformersdir=transformerdict[row['transformer']],
                                                              sourceauthor=sourceauthor,
                                                              targetauthor=targetauthor,
                                                              attack_mode=attack_mode,
                                                              attackdir=self.attackdir,
                                                              logger=self.logger,
                                                              includeinfopath=os.path.join(codeinfodir,
                                                                        row['Specific-Arguments']))
        elif row['Python-class'].endswith("/GlobalConstTransformer"):
            tr: GlobalConstTransformer = GlobalConstTransformer(transformer=row['transformer'],
                                                              option=row['option'],
                                                              uniqueid=row['uniqueid'],
                                                              fillcmdlineoption=row['fillcmdlineoptions'],
                                                              transformersdir=transformerdict[row['transformer']],
                                                              sourceauthor=sourceauthor,
                                                              targetauthor=targetauthor,
                                                              attack_mode=attack_mode,
                                                              attackdir=self.attackdir,
                                                              logger=self.logger,
                                                              includeinfopath=os.path.join(codeinfodir,
                                                                                           row['Specific-Arguments']))
        else:
            raise Exception("Unvalid AddTemplateTransformerClass chosen")
        return tr


    def __load_further_transformers(self, row, transformerdict, attack_mode: AttackMode,
                                         sourceauthor: Author, targetauthor: Author, codeinfodir):
        """
        Load further special transformers such as IncludeSortTransformer.
        """

        if row['Python-class'] == "IncludeSortTransformer":
            raise Exception("Do not use this transformer")
            # tr = IncludeSortTransformer(transformer=row['transformer'],
            #                        option=row['option'],
            #                        uniqueid=row['uniqueid'],
            #                        fillcmdlineoption=row['fillcmdlineoptions'],
            #                        transformersdir=transformerdict[row['transformer']],
            #                        sourceauthor=sourceauthor,
            #                        targetauthor=targetauthor,
            #                        attack_mode=attack_mode,
            #                        attackdir=self.attackdir,
            #                        logger=self.logger,
            #                        includeinfopath=os.path.join(codeinfodir, row['Specific-Arguments']))
            # return tr

        else:
            raise Exception("Unvalid transformer class specified in csv file")



    def __load_external_transformers(self, pathdf: str) -> typing.List['TransformerBase']:
        """
        Loads external transformers that were implemented outside of LibTooling.
        :return: a list of transformer objects
        """

        df: pandas.DataFrame = pandas.read_csv(pathdf)
        df = df.fillna("")
        transformerobjects: typing.List['TransformerBase'] = []

        for index, row in df.iterrows():
            if row['Python-class'] == "ExternalIncludeWhatYouUseTransformer":
                try:
                    transformerobjects.append(ExternalIncludeWhatYouUseTransformer(transformer=row['transformer'],
                                                           option=row['option'], uniqueid=row['uniqueid'],
                                                           fillcmdlineoption=row['fillcmdlineoptions']))
                except Exception as e:
                    # external transformer is not available, we continue with attack simply,
                    # we just don't use this transformer..
                    print(e)
            else:
                raise Exception("Unvalid transformer class specified in csv file")


        return transformerobjects