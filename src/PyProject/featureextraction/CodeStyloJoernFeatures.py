from featureextraction.CodeStyloJoernFeatCl import *
import numpy as np
import os
import typing
from scipy import sparse


class CodeStyloJoernFeatures(CodeStyloFeatures.CodeStyloFeatures):
    """
    This class creates the AST features.
    """

    def __init__(self, inputdata: typing.Union[str, dict], get_lexical_features: bool,
                 tf: bool, tfidf: bool,
                 trainobject: typing.Optional['CodeStyloJoernFeatures'],
                 verbose: bool = False) -> None:
        """
        Constructor for Joern/clang-based AST features.
        :param inputdata: Either string with path to directory with *dat files OR dict with lists of features
        for each feature class.

        IF dir is given, we will look for dat files created by joern / our clang-based tool. In particular,
        we look for the files: ast_node_bigram.dat, ast_node_types.dat, ast_node_types_avg_dep.dat,
        # code_in_ast_leaves.dat, code_in_ast_leaves_avg_dep.dat, max_depth_ast_node.dat.
        :param get_lexical_features: set to true if we want to extract lexical features additionally.
        These features were reimplemented in our clang tool, since they were not properly extracted in the original
        Java implementation.
        :param: tf set to true if you want to get term frequencies. Note that we only do the tf-idf transformation
        for AST Node Bigrams, AST Node Types and Code in AST Leaves (as suggested by the usenix paper).
        :param: tfidf set to true if you want idf transformation additonally. Ignored if tf is false.
        In contrast to other classes: Note that by setting tf and idf to true, we get tf-features + tf-idf-features,
        look at Table 4 in Caliskan et al., USENIX.
        :param trainobject: used for feature alignment to have same set of features as train set
        and used for tf-idf-transformation. This object should be a CodeStyloJoernFeatures object,
        representing the training set. In particular, this object is used to perform for vectorizing input data
        and the tf-idf transformation by using the already fitted tf-idf-transformer from the trainobject.
        :param verbose: set to true if you want to see some print messages indicating the progress
        """

        self.verbose = verbose
        self.get_lexical_features = get_lexical_features
        self.tf = tf
        self.tfidf = tfidf

        # save all the code stylo subclasses
        self.codestylosubclasses = {}  # type: typing.Dict[str, CodeStyloJoernFeatCl]

        # call parent's init method that will call read_data_from_source
        super(CodeStyloJoernFeatures, self).__init__(inputdata=inputdata, trainobject=trainobject)



    # @Overwrite
    def read_data_from_source(self, inputdata: typing.Union[str, dict],
                              trainobject: typing.Optional['CodeStyloJoernFeatures']):

        # A. First, get all AST Node features from the different dat-files,
        # check that the id columns are the same.
        if not isinstance(inputdata, str) and not isinstance(inputdata, dict):
            raise Exception("For Joern Code Stylo, use str or dict as input, not other types, such as list")

        # A. Get AST bigrams
        astnodeinput = inputdata["ast_node_bigram.dat"] if isinstance(inputdata, dict) \
            else os.path.join(inputdata, "ast_node_bigram.dat")
        ctrainobj = None if trainobject is None else trainobject.codestylosubclasses["ast_node_bigram.dat"]

        self.codestylosubclasses["ast_node_bigram.dat"] = ASTNodeFeature(inputdata=astnodeinput, verbose=self.verbose,
                                                                         bigrams=True,
                                                                         trainobject=ctrainobj,
                                                                         featureclassidentifier="ast_node_bigram")

        # A-2. Get further AST features
        astnodefeaturepaths = ["ast_node_types.dat", "ast_node_types_avg_dep.dat",
                               "code_in_ast_leaves.dat", "code_in_ast_leaves_avg_dep.dat"]
        for cpath in astnodefeaturepaths:
            astnodeinput = inputdata[cpath] if isinstance(inputdata, dict) else os.path.join(inputdata, cpath)
            ctrainobj = None if trainobject is None else trainobject.codestylosubclasses[cpath]
            featureclassident: str = os.path.basename(cpath).split(sep=".dat")[0]

            self.codestylosubclasses[cpath] = ASTNodeFeature(inputdata=astnodeinput, verbose=self.verbose,
                                                             bigrams=False,
                                                             trainobject=ctrainobj,
                                                             featureclassidentifier=featureclassident)

        # B. Get the depth feature
        maxdepthastnodeinput = inputdata["max_depth_ast_node.dat"] if isinstance(inputdata, dict) \
            else os.path.join(inputdata, "max_depth_ast_node.dat")
        ctrainobj = None if trainobject is None else trainobject.codestylosubclasses["max_depth_ast_node.dat"]

        self.codestylosubclasses["max_depth_ast_node.dat"] = ASTMaxPropertyFeature(inputdata=maxdepthastnodeinput,
                                                                                   verbose=self.verbose,
                                                                                   trainobject=ctrainobj,
                                                                                   featureclassidentifier="max_depth_ast_node")

        # C. We may add the lexical features that we reimplemented via clang
        if self.get_lexical_features:
            lexicalfeaturesinput = inputdata["lexical_features.dat"] if isinstance(inputdata, dict) \
                else os.path.join(inputdata, "lexical_features.dat")
            ctrainobj = None if trainobject is None else trainobject.codestylosubclasses["lexical_features.dat"]

            self.codestylosubclasses["lexical_features.dat"] = ASTNodeFeature(inputdata=lexicalfeaturesinput,
                                                                              verbose=self.verbose, bigrams=False,
                                                                              trainobject=ctrainobj,
                                                                              featureclassidentifier="lexical_features")

            # for lexical features, we know how many columns we should have. test that.
            assert self.codestylosubclasses["lexical_features.dat"].featurematrix.shape[1] == 5


        # D. Merge them and return them
        prevelem = None
        for i, value in enumerate(self.codestylosubclasses.values()):
            if i == 0:
                prevelem = value
            else:
                prevelem = value.mergeToNewObject(prevelem)


        return prevelem.featurematrix, prevelem.colnames, prevelem.authors, \
               prevelem.iids


    # @Overwrite
    def __getitem__(self, index):
        """
        Implements the row-access via [].
        For example, you can select the wanted rows via obj[2:5] now.
        :param index: the wanted indices
        :return: a new CodeStyloFeatures object with filtered rows.
        """
        newstylofeatureobject = copy.deepcopy(self)
        for key, val in newstylofeatureobject.codestylosubclasses.items():
            newstylofeatureobject.codestylosubclasses[key] = val[index]
            newstylofeatureobject.tfidftransformer = None
            newstylofeatureobject.tfidftransformer2nd = None

        newstylofeatureobject.featurematrix = newstylofeatureobject.featurematrix[index, :]
        newstylofeatureobject.iids = newstylofeatureobject.iids[index]
        newstylofeatureobject.authors = newstylofeatureobject.authors[index]

        return newstylofeatureobject


    # @Overwrite
    def gettfidffeatures(self, trainobject: typing.Optional['CodeStyloFeatures']):
        """
        Special Case: we create tf versions only for specific classes if tf is true.
         Moreover, if tfidf was set to true before, we create for some feature classes
        tf and tf-idf versions.
        Returns new featurematrix and column names, adapted to tf-idf.
        """

        astnodefeaturepaths = ["ast_node_bigram.dat", "ast_node_types.dat", "ast_node_types_avg_dep.dat",
                               "code_in_ast_leaves.dat", "code_in_ast_leaves_avg_dep.dat", "max_depth_ast_node.dat"]

        # tf and tf-idf such as in Caliskan et al.
        tfinstances = [True, True, False, True, False, False]
        idfinstances = [False, True, False, True, False, False]
        featmatrix_list = []
        colnames_list = []

        if self.get_lexical_features:
            astnodefeaturepaths.append("lexical_features.dat")
            tfinstances.append(False)
            idfinstances.append(False)

        # Run over each code stylo sub class and get tf (and possibly tf-idf) feature matrix
        for cpath, ctf, cidf in zip(astnodefeaturepaths, tfinstances, idfinstances):
            curcodestylo: CodeStyloJoernFeatCl = self.codestylosubclasses[cpath]
            ctrainobj = None if trainobject is None else trainobject.codestylosubclasses[cpath]

            # tf
            featmatrix, colnames = curcodestylo.apply_tf_idf_normalization(tf=ctf and self.tf, idf=False, trainobject=ctrainobj)
            featmatrix_list.append(featmatrix)
            colnames_list.append(colnames)

            # tf + idf
            if ctf and cidf and self.tfidf:
                featmatrix, colnames = curcodestylo.apply_tf_idf_normalization(tf=ctf, idf=cidf, trainobject=ctrainobj)
                featmatrix_list.append(featmatrix)
                colnames_list.append(colnames)

        # Merge them and return them: concatenate all feature matrices and column names
        featurematrix = featmatrix_list[0]
        colnames = colnames_list[0]

        for i in range(1, len(featmatrix_list)):
            featurematrix = sparse.hstack([featurematrix, featmatrix_list[i]], format="csr")
            colnames = colnames + colnames_list[i]

        return featurematrix, colnames




