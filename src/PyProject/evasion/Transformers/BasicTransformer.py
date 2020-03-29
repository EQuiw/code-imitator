import os
import subprocess
import typing
import shlex
import copy
import numpy as np

import Configuration as Config

from evasion.Transformers.TransformerBase import TransformerBase


class BasicTransformer(TransformerBase):

    def __init__(self, transformer: str, option: str, uniqueid: str, fillcmdlineoption: str,
                 transformersdir: str):
        super(BasicTransformer, self).__init__(transformer, option, uniqueid, fillcmdlineoption)

        # Path to clang-based transformer executables
        self.transformersdir = transformersdir
        self.flags = Config.flag_list


    #@Overwrite
    def dotransformercall(self, source_file, target_file, seed):
        return self._do_transformation(source_file=source_file, seed=seed, target_file=target_file)


    #@Overwrite
    def getsubprocesscall(self, source_file, seed) -> typing.Tuple:

        options: typing.List[str] = copy.deepcopy(self.option)
        if self.fillcmdlineoption != "":
            options.extend(self.handle_special_case(seed=seed))

        cmdd_transform = [os.path.join(self.transformersdir, self.transformer), source_file,
                          *options, "--", *self.flags]

        simplified_cmdd_transform = " ".join([self.transformer, source_file, *options, "--", "..."])

        self._save_information_about_last_call(set_cmdtransform=cmdd_transform,
                                               set_cmdtransform_simplified=simplified_cmdd_transform,
                                               set_options=options, set_seed = seed)
        return cmdd_transform, simplified_cmdd_transform


    def _do_transformation(self, source_file: str, seed, target_file: str):
        """
        Do transformation on source file
        :param source_file: the file that will be transformed. Pass its path here.
        :param seed, seed for transformer
        :param target_file: the path to the new transformed c/c++ file
        """

        cmdd_transform, simplified_cmdd_transform = self.getsubprocesscall(source_file=source_file,
                                                                           seed=seed)

        # Necessary, since Typedef Name Transformer requires "" around typedef args if used in bash file
        #   (as BBBatchAttackInstanceHandler), but subprocess will complain about them,
        #   thus we finally tokenize cmdd_transform again to make sure we do it right here.
        cmdd_transform = shlex.split(" ".join(cmdd_transform))
        with open(target_file, 'w') as target:
            p = subprocess.run(cmdd_transform, stdout=target, stderr=subprocess.PIPE, shell=False, timeout=145)
        output, err = p.stdout, p.stderr
        if err != b'':
            return simplified_cmdd_transform, str(err)
        else:
            return simplified_cmdd_transform, None


    #@Overwrite
    def check_valid(self):
        return True

    #@Overwrite
    def handle_special_case(self, seed: int) -> typing.List[str]:
        """
        If some command line option requires that we fill it.
        We need to fill out the seed if necessary, or if declaration name transforming we need to choose the names.
        :param seed: a seed
        :return: the filloption where the necessary fields are set.
        """

        # iterate over all options, separated by semicolon ;
        newcmdline = []

        for currentfilloption in self.fillcmdlineoption.split(";"):
            if currentfilloption == "seed":
                np.random.seed(seed + 34)
                newcmdline.append("-seed=" + str(np.random.randint(0, 5000)))
            elif currentfilloption == "all":
                newcmdline.append("-all=True")
            else:
                raise Exception("No valid filloption specified")

        return newcmdline

    # @Overwrite
    def pass_target_feature_value(self, feature_value: str, direction: str):
        pass