from evasion.Transformers.TransformerBase import TransformerBase
import Configuration as Config
import os
import subprocess
import typing
import shlex

# TODO, create own IWYU transformer that is not callable as bash script, this is only temorary!

class ExternalIncludeWhatYouUseTransformer(TransformerBase):

    def __init__(self, transformer: str, option: str, uniqueid: str, fillcmdlineoption: str):
        super(ExternalIncludeWhatYouUseTransformer, self).__init__(transformer, option, uniqueid, fillcmdlineoption)
        self.flags = Config.flag_list

        # Path to iwyu-executable
        # Each external transformer is just an option, so it may not be present.
        if Config.iwyu_dir is not None:
            self.iwyupath: str = Config.iwyu_dir
        else:
            raise Exception("IWYU_PATH not set. I'll skip external transformer: Include-what-you-use\n")


    #@Overwrite
    def dotransformercall(self, source_file, target_file, seed):

        # A. Call IWYU to get output what headers could be removed
        cmdd_transform, simplified_cmdd_transform = self.getsubprocesscall(source_file=source_file, seed=seed)

        cmdd_transform = shlex.split(" ".join(cmdd_transform))
        with open(target_file, 'w') as target:
            p = subprocess.run(cmdd_transform, stdout=target, stderr=subprocess.PIPE, shell=False, timeout=145)
        output, err = p.stdout, p.stderr
        if err != b'':
            return simplified_cmdd_transform, str(err)
        else:
            return simplified_cmdd_transform, None


    # @Overwrite
    def getsubprocesscall(self, source_file, seed) -> typing.Tuple:
        # cmdd_transform = [os.path.join(self.iwyupath, self.transformer),
        #                   source_file, *self.option, *self.flags]
        # TODO, is used in the long term, use a unique path for external transformers that lie somewhere else!
        bash_file = os.path.join(os.path.dirname(Config.externaltransformercsvfile), "iwyu_replace.sh")
        assert os.path.isfile(bash_file)

        cmdd_transform = ["bash", bash_file, source_file, self.iwyupath, *self.option, *self.flags]

        simplified_cmdd_transform = " ".join([self.transformer, source_file, *self.option, "..."])

        self._save_information_about_last_call(set_cmdtransform=cmdd_transform,
                                               set_cmdtransform_simplified=simplified_cmdd_transform,
                                               set_options=self.option, set_seed=seed)
        return cmdd_transform, simplified_cmdd_transform


    #@Overwrite
    def check_valid(self):
        return True

    #@Overwrite
    def handle_special_case(self, seed: int) -> str:
        pass

    # @Overwrite
    def pass_target_feature_value(self, feature_value: str, direction: str):
        pass