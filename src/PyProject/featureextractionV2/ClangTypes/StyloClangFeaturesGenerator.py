from featureextractionV2.ClangTypes.StyloClangFeaturesAbstract import StyloClangFeaturesAbstract
from featureextractionV2.ClangTypes.StyloASTNodeFeature import StyloASTNodeFeature
from featureextractionV2.ClangTypes.StyloASTMaxPropertyFeature import StyloASTMaxPropertyFeature
from featureextractionV2.StyloFeatures import StyloFeatures

import os
import typing



class StyloClangFeaturesGenerator:
    """
    This class creates the AST features from Caliskan et al., USENIX publication.

    Be careful. For feature groups where a TF and TF+IDF feature representation is wanted,
    we load the respective features, and then copy it once. For instance, the 'ast_node_types' features.
    Later if TF+IDF is called, we create the tf-representation for the first object,
    and the tf-idf for the second! We do so, since we cannot create a tf+idf here at
    creation time. We may split the dataset later into a training and test set,
    and if we did the tf here already, we would compute
    the tf+idf over the whole dataset which is an example of data snooping.
    """

    def __init__(self, inputdata: typing.Union[str, dict], get_lexical_features: typing.Optional[bool],
                 trainobject: typing.Optional['StyloClangFeaturesAbstract'],
                 verbose: bool = False) -> None:
        """
        Constructor for clang-based AST features.
        :param inputdata: Either string with path to directory with *dat files OR dict with lists of features
        for each feature class.

        IF dir is given, we will look for dat files created by our clang-based tool. In particular,
        we will look for the files: ast_node_bigram.dat, ast_node_types.dat, ast_node_types_avg_dep.dat,
        code_in_ast_leaves.dat, code_in_ast_leaves_avg_dep.dat, max_depth_ast_node.dat.
        :param get_lexical_features: set to true if we want to extract lexical features additionally.
        These features were re-implemented in our clang tool, since they were not properly extracted in the original
        Java implementation.
        :param trainobject: previous training object.
        :param verbose: set to true if you want to see some print messages indicating the progress
        """

        self.verbose = verbose
        self.get_lexical_features = get_lexical_features
        # self.tf = tf
        # self.tfidf = tfidf

        styloobjects_list, lasttrainobj = self.read_data_from_source(
            inputdata=inputdata, trainobject=trainobject)

        self.styloobjects_list: typing.List[StyloClangFeaturesAbstract] = styloobjects_list
        self.lasttrainobj: typing.Optional[StyloClangFeaturesAbstract] = lasttrainobj


    # def getunique_key(self) -> str:
    #     return "_".join(["clang-ast", self.tf, self.tfidf, self.get_lexical_features])

    def read_data_from_source(self, inputdata: typing.Union[str, dict],
                              trainobject: typing.Optional['StyloClangFeaturesAbstract']
                              ) -> typing.Tuple[typing.List[StyloClangFeaturesAbstract],
                                                typing.Optional['StyloClangFeaturesAbstract']]:

        final_styloobjects: typing.List[StyloClangFeaturesAbstract] = []

        if not isinstance(inputdata, str) and not isinstance(inputdata, dict):
            raise Exception("For Clang Code Stylo, use str or dict as input, not other types, such as list")

        # A. Get AST bigrams
        # Either we get the features as already loaded string from dict, or we have to load it from disk.
        # In the latter case, inputdata points to a directory where ast_node_bigram.dat is located.
        if isinstance(inputdata, dict):
            astnodeinput = inputdata["ast_node_bigram.dat"]
        else:
            astnodeinput = os.path.join(inputdata, "ast_node_bigram.dat")

        ctrainobj: typing.Optional[StyloClangFeaturesAbstract] = trainobject
        prevnode = StyloASTNodeFeature(inputdata=astnodeinput, verbose=self.verbose, bigrams=True, trainobject=ctrainobj,
                                   featureclassidentifier="ast_node_bigram", tf=True, idf=False)
        final_styloobjects.append(prevnode)

        # A-2. Get further AST features
        final_styloobjects, ctrainobj = self.__astnodes(inputdata=inputdata, ctrainobj=ctrainobj,
                                   final_styloobjects=final_styloobjects)


        # B. Get the depth feature
        if isinstance(inputdata, dict):
            maxdepthastnodeinput = inputdata["max_depth_ast_node.dat"]
        else:
            maxdepthastnodeinput = os.path.join(inputdata, "max_depth_ast_node.dat")

        ctrainobj = None if ctrainobj is None else ctrainobj.codestyloreference
        prevnode = StyloASTMaxPropertyFeature(inputdata=maxdepthastnodeinput, tf=False, idf=False,
                                                           verbose=self.verbose,
                                                           trainobject=ctrainobj,
                                                           featureclassidentifier="max_depth_ast_node")
        final_styloobjects.append(prevnode)

        # C. We may add the lexical features that we reimplemented via clang
        if self.get_lexical_features is None:
            # the following is actually only relevant for evasion. there, we need to determine if lexical features
            #   were used. We get it by using the next stylo reference and check if it contains lexical features.
            if trainobject is None:
                raise Exception("Cannot determine if lexical features were wanted. "
                            "Boolean value is None and training object is missing")
            temptr = ctrainobj.codestyloreference
            if temptr is not None and temptr.getunique_key().startswith("lexical_features"):
                self.get_lexical_features = True

        if self.get_lexical_features:
            final_styloobjects, ctrainobj = self.__lexicalfeatures(inputdata=inputdata, ctrainobj=ctrainobj,
                                              final_styloobjects=final_styloobjects)

        return final_styloobjects, ctrainobj


    def __astnodes(self,
                   inputdata: typing.Union[str, dict],
                   ctrainobj: typing.Optional['StyloClangFeaturesAbstract'],
                   final_styloobjects: typing.List[StyloClangFeaturesAbstract],
                   ) -> typing.Tuple[typing.List[StyloClangFeaturesAbstract],
                                                typing.Optional['StyloClangFeaturesAbstract']]:

        astnodefeaturepaths = ["ast_node_types.dat", "ast_node_types_avg_dep.dat",
                               "code_in_ast_leaves.dat", "code_in_ast_leaves_avg_dep.dat"]
        # tf and tf-idf such as in Caliskan et al.
        tfinstances = [True, False, True, False]
        idfinstances = [True, False, True, False]

        for cpath, ctf, cidf in zip(astnodefeaturepaths, tfinstances, idfinstances):
            # we will create one or two objects depending on the tf and idf list. If tf = True, and idf = False,
            # we create a tf-only object, if tf and idf are true, we create both a tf-only and tf-idf object.

            if isinstance(inputdata, dict):
                astnodeinput = inputdata[cpath]
            else:
                astnodeinput = os.path.join(inputdata, cpath)

            featureclassident: str = str(os.path.basename(cpath).split(sep=".dat")[0])  # str() makes typing check happy

            ctrainobj = None if ctrainobj is None else ctrainobj.codestyloreference
            prevnode: StyloASTNodeFeature = StyloASTNodeFeature(inputdata=astnodeinput, verbose=self.verbose,
                                                             bigrams=False, tf=ctf, idf=False,
                                                             trainobject=ctrainobj,
                                                             featureclassidentifier=featureclassident)
            final_styloobjects.append(prevnode)

            if cidf is True:
                assert ctf is True  #  we do not want to have a tf-idf without tf ...
                ctrainobj = None if ctrainobj is None else ctrainobj.codestyloreference
                prevnode = StyloASTNodeFeature(inputdata=astnodeinput, verbose=self.verbose,
                                            bigrams=False, tf=ctf, idf=cidf,
                                            trainobject=ctrainobj,
                                            featureclassidentifier=featureclassident)
                final_styloobjects.append(prevnode)

        return final_styloobjects, ctrainobj


    def __lexicalfeatures(self,
                   inputdata: typing.Union[str, dict],
                   ctrainobj: typing.Optional['StyloClangFeaturesAbstract'],
                   final_styloobjects: typing.List[StyloClangFeaturesAbstract],
                   ) -> typing.Tuple[typing.List[StyloClangFeaturesAbstract],
                                                typing.Optional['StyloClangFeaturesAbstract']]:

        if isinstance(inputdata, dict):
            lexicalfeaturesinput = inputdata["lexical_features.dat"]
        else:
            lexicalfeaturesinput = os.path.join(inputdata, "lexical_features.dat")

        ctrainobj = None if ctrainobj is None else ctrainobj.codestyloreference
        lexinode = StyloASTNodeFeature(inputdata=lexicalfeaturesinput,
                                       verbose=self.verbose, bigrams=False, tf=False, idf=False,
                                       trainobject=ctrainobj,
                                       featureclassidentifier="lexical_features")

        # for lexical features, we know how many columns we should have. test that.
        assert lexinode.getfeaturematrix().shape[1] == 5
        final_styloobjects.append(lexinode)
        return final_styloobjects, ctrainobj


    @staticmethod
    def check_unique_keys_for_trainobject_comparison(trainobj: StyloFeatures):
        """
        Checks if train object has a matching unique key / feature class identifier that corresponds to this generator.
        This method is only used by evasion algorithms to check if a training object demands that we create
        clang objects from Caliskan et al.'s approach.
        :return: true/false
        """

        keys = ["ast_node_bigram", "ast_node_types", "ast_node_types_avg_dep",
                "code_in_ast_leaves", "code_in_ast_leaves_avg_dep", "max_depth_ast_node",
                "lexical_features"]
        if isinstance(trainobj, StyloClangFeaturesAbstract):
            for key in keys:
                if trainobj.getunique_key().startswith(key):
                    return True
        return False