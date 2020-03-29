from featureextraction.CodeStyloARFFFeatures import CodeStyloARFFFeatures
from featureextraction.CodeStyloUnigramFeatures import CodeStyloUnigramFeatures
from featureextraction.CodeStyloJoernFeatures import CodeStyloJoernFeatures
from featureextraction.CodeStyloMergedFeatures import CodeStyloMergedFeatures
from evasion.utils_attack_workflow import *
from featureextraction.CodeStyloFeatures import CodeStyloFeatures
from featureextraction.CodeStyloLexemFeatures import CodeStyloLexemFeatures

import subprocess
import Configuration
import sys


def extract_features_fromfeatureextraction(output: str, call_options: typing.List[str]) -> typing.Dict[str, typing.List[str]]:
    """
    Extract feature strings for each feature class (such as bigrams, ast node types, ...).
    Use this method if we use feature_extraction_single (our clang tool) that outputs all various types per row.
    :param output: the output from feature_extraction_single
    :param call_options: the call options for feature_extraction_single
    :return:
    """

    results = {}

    rows = output.split("\n")
    # assert (len(rows)-1) == len(call_options) # the last row is ''
    if (len(rows) - 1) != len(call_options):
        print("len", len(rows) - 1, ",", len(call_options), file=sys.stderr)
        raise Exception("extract features single error")
    for r in rows:
        if r != '':
            rowsplit = r.split("::--::")
            assert len(rowsplit) == 2 # should only be the feature class and the feature name

            featuretype, featurestring = rowsplit[0].strip(), rowsplit[1]+"\n"
            results[featuretype] = [featurestring]

    return results




def get_clang_features_call(src: str, output_dir: str):

    call_options = ["-ast_node_bigram=True", "-ast_node_types=True", "-ast_node_types_avg_dep=True",
                    "-max_depth_ast_node=True", "-code_in_ast_leaves=True", "-code_in_ast_leaves_avg_dep=True",
                    "-lexical_features=True"]

    cmdd_transform = [os.path.join(Configuration.featureextractordir_single, "feature_extraction_single"),
                      src, *call_options, "--", *Configuration.flag_list]

    tarfile = os.path.join(output_dir, "clang_features.dat")
    return cmdd_transform, call_options, tarfile


def get_lexems_features_call(src: str, output_dir: str):
    cmdd_transform = [os.path.join(Configuration.featureextractordir, "get_lexems_features"),
                      src, "--", *Configuration.flag_list]
    tarfile = os.path.join(output_dir, "lexems_features.dat")
    return cmdd_transform, tarfile


def extractfeatures_evasion(src: str, output_dir: str, use_arff: bool, use_clang: bool, dolexems: bool,
                            already_extracted: bool) \
        -> typing.Tuple[typing.Dict[str,typing.List[str]], typing.List[str]]:
    """
    Extracts the features for a single source file.
    Calls all feature extraction clang tools
    :param src: the complete path to c/cpp file
    :param output_dir: the complete path where extracted features will be saved. Should be empty.
    :param use_arff: set true if naive baseline implementation from Caliskan-Islam et al. should be used for
    extraction some lexical features.
    :param use_clang: set true if clang-based features should be extracted
    :param dolexems: set true if clang-based lexems should be extracted.
    :param already_extracted: if true, this method will assume that feature files already exist.
    :return: It returns a dict for clang-based extracted features and the arff features -- if used -- would be
    saved in a .arff file in output_dir.
    """

    dict_clang = None
    lexems = None

    # A. Extract features from our clang-based implementation that mimics Joern
    if use_clang:

        cmdd_transform, call_options, targetfile = get_clang_features_call(src=src, output_dir=output_dir)
        if not already_extracted:

            p = subprocess.run(cmdd_transform, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False, timeout=250)

            output, err = p.stdout, p.stderr
            if err != b'':
                print("Error while loading new features for object:" + src + "call:" + str(cmdd_transform), file=sys.stderr)
                print("Error: {}".format(str(err)), file=sys.stderr)
                raise Exception("feature extraction failure:" + str(err))
            output_clang = str(output.decode("ISO-8859-1"))
        else:
            assert(os.path.isfile(targetfile))
            with open(targetfile, "r", encoding='ISO-8859-1') as f:
                output = f.readlines()
                output_clang = "".join(output)

        # now we need to parse the output so that we get a string for each feature class
        dict_clang = extract_features_fromfeatureextraction(output=output_clang,
                                                            call_options=call_options)

    # B. Extract features from naive baseline implementation from Caliskan-Islam et al. that extracts some lexical features.
    if use_arff:

        if Configuration.naivebaselinecmd is None:
            raise Exception("Use Arff is set to True, but no java feature extraction dir was specified")

        cmdd_transform = ["java -jar", Configuration.naivebaselinecmd, src,
                          os.path.join(output_dir, "lexical_features.arff")]
        cmdd_transform = " ".join(cmdd_transform)
        p = subprocess.run(cmdd_transform, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, timeout=145)
        output, err = p.stdout, p.stderr
        if err != b'':
            print("Error while loading new arff features for object:" + src, file=sys.stderr)
            raise Exception("arff feature extraction failure:" + str(err))

    # C. If we use lexems, get lexems features
    if dolexems:

        cmdd_transform, targetfile = get_lexems_features_call(src=src, output_dir=output_dir)
        if not already_extracted:
            p = subprocess.run(cmdd_transform, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False, timeout=175)

            output, err = p.stdout, p.stderr
            if err != b'':
                print("Error while loading new lexems features for object:" + src + "call:" + str(cmdd_transform), file=sys.stderr)
                print("Error: {}".format(str(err)), file=sys.stderr)
                raise Exception("feature lexem extraction failure:" + str(err))
            output_lexems = str(output.decode("ISO-8859-1"))
        else:
            assert (os.path.isfile(targetfile))
            with open(targetfile, "r", encoding='ISO-8859-1') as f:
                output = f.readlines()
                output_lexems = "".join(output)

        lexems = [output_lexems] # feat. extraction requires list.

    return dict_clang, lexems


def load_new_features_merged(datasetpath: str, attackdirauth: str, verbose: bool, cppfile: str,
                             train_object: CodeStyloMergedFeatures, already_extracted: bool) -> CodeStyloMergedFeatures:
    """
    New interface for loading features.
    Loads a single feature vector for a given source file-author.
    Internally, it calls load_new_features..
    :param datasetpath:
    :param attackdirauth:
    :param verbose:
    :param cppfile:
    :param train_object: CodeStyloMergedFeatures object
    :param already_extracted: bool to indicate if clang-lexems-arff features were already extracted from
    cpp file. If you are unsure, set it to False. We use it only if we perform all transformations
    via gnu parallel, so that we also extract the features in parallel.
    :return: CodeStyloMergedFeatures object
    """
    o: typing.List[CodeStyloFeatures] = __load_new_features(datasetpath=datasetpath, attackdirauth=attackdirauth,
                                                   verbose=verbose, cppfile=cppfile,
                                                   train_objects=train_object.codestyloobject_list,
                                                   already_extracted=already_extracted)
    co: CodeStyloMergedFeatures = CodeStyloMergedFeatures(o)
    co.update_tfidffeatures(trainobject=train_object)
    co.update_columns(index=None, trainobject=train_object)
    return co


def load_new_features(datasetpath: str, attackdirauth: str, verbose: bool, cppfile: str, train_objects: list):
    """
    Loads a single feature vector for a given source file - author.
    Deprecated.
    :param datasetpath:
    :param attackdirauth:
    :param verbose:
    :param cppfile:
    :param train_objects:
    :return:
    """
    print("load_new_features method is deprecated", file=sys.stderr)
    return __load_new_features(datasetpath=datasetpath, attackdirauth=attackdirauth,
                                                   verbose=verbose, cppfile=cppfile,
                                                   train_objects=train_objects,
                                                   already_extracted=False)


def __load_new_features(datasetpath: str, attackdirauth: str, verbose: bool, cppfile: str, train_objects: list,
                        already_extracted: bool):

    # A. Determine what feature classes are needed; unigram features are read from Python directly.
    doarff = dojoern = dolexems = False
    for train_obj in train_objects:
        doarff = True if isinstance(train_obj, CodeStyloARFFFeatures) else doarff
        dojoern = True if isinstance(train_obj, CodeStyloJoernFeatures) else dojoern
        dolexems = True if isinstance(train_obj, CodeStyloLexemFeatures) else dolexems

    # Extract features
    dict_clang, lexems = extractfeatures_evasion(src = cppfile, output_dir=attackdirauth,
                                                 use_arff=doarff, use_clang=dojoern, dolexems=dolexems,
                                                 already_extracted=already_extracted)

    # B. Load calculated features into Python
    attack_data = []  # type: list[CodeStyloFeatures]
    for train_obj in train_objects:

        if isinstance(train_obj, CodeStyloARFFFeatures):
            # i. Get Arff features from java implementation
            arffmatrix_att = CodeStyloARFFFeatures(inputdata=os.path.join(attackdirauth, "lexical_features.arff"),
                                                   removelog=True)
            attack_data.append(arffmatrix_att)

        elif isinstance(train_obj, CodeStyloUnigramFeatures):
            # ii.a Get WordUnigramTF features
            unigrammmatrix_att = CodeStyloUnigramFeatures(inputdata=cppfile, nocodesperprogrammer=1,
                                                          noprogrammers=1, binary=False,
                                                          tf=train_obj.tf, idf=train_obj.idf,
                                                          ngram_range=train_obj.ngram_range,
                                                          stop_words=train_obj.stop_words,
                                                          trainobject=train_obj)
            attack_data.append(unigrammmatrix_att)

        elif isinstance(train_obj, CodeStyloLexemFeatures):
            # ii.b Get LexemTF features
            unigrammmatrix_att = CodeStyloLexemFeatures(inputdata=lexems,
                                                        tf=train_obj.tf, idf=train_obj.idf, trainobject=train_obj,
                                                        verbose=verbose)
            attack_data.append(unigrammmatrix_att)

        elif isinstance(train_obj, CodeStyloJoernFeatures):
            # iii. Get joern features
            joernmatrix_att = CodeStyloJoernFeatures(inputdata=dict_clang,
                                                     get_lexical_features=train_obj.get_lexical_features,
                                                     verbose=verbose,
                                                     tf=train_obj.tf, tfidf=train_obj.tfidf,
                                                     trainobject=train_obj)
            attack_data.append(joernmatrix_att)
            # print("->", attackdirauth, "::", np.mean(joernmatrix_att.featurematrix.todense())) #todo


    # C. Last but not least: Clean previous .dat files
    # items = os.listdir(attackdirauth)
    # for item in items:
    #     if item.endswith(".dat") or item.endswith(".arff"):
    #         os.remove(os.path.join(attackdirauth, item))


    return attack_data



def run_hill_simulation(args):
    attinstance, nexttransformerindex, currenttransformer, seed, queue = args
    lasttransfcall, successtransf, scoreprednew, classprednew = attinstance.do_transformation_and_predict(
                    prefix=str(nexttransformerindex), currenttransformer=currenttransformer, seed=seed)
    queue.append([nexttransformerindex, currenttransformer, lasttransfcall,
               successtransf, scoreprednew, classprednew])

