############### Variable Definition ##############
import configparser
import os
import sys


### Read config.ini to get all path information such as path to this repo, path to clang, path to IWYU, ...
__config_ini_file_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "config.ini")
config = configparser.ConfigParser()
config.read(__config_ini_file_path)


### Now set values
# Get the path to repository
repo_path = config["AUTHORSHIP_EVASION"]["root"]

# Get the clang library include path, for the prebuilt binaries, it is:
# llvmconfig_libdir = utils_extraction.getclanglibpath()
llvmconfig_prefix = config["CLANG"]["prefix"]
llvmconfig_libdir = config["CLANG"].get("libdir", os.path.join(llvmconfig_prefix, "lib"))


# Get information about the dataset
probsperprogrammer = 8
suffix = "_2017_8_formatted_macrosremoved"
# suffix="_2017_8"
datasetpath = os.path.join(repo_path, "data/dataset_2017/dataset" + suffix)
exampledatasetpath = os.path.join(repo_path, "data/dataset_2017/example_dataset" + suffix)
arffile = os.path.join(repo_path, "data/dataset_2017/libtoolingfeatures" + suffix, "lexical_features.arff")
joerndats = os.path.join(repo_path + "data/dataset_2017/libtoolingfeatures" + suffix)
learnmodelspath = os.path.join(repo_path, "data/ClassificationModels")
evasionattackpath = os.path.join(repo_path, "data/attackresults")

# Get and set things for attack
testfilesdir = os.path.join(repo_path, "data/dataset_2017/test_inputs")
call_instructions_csv_path = os.path.join(repo_path, "data/dataset_2017/call_database_authors/call_instructions.csv")
ini_settings_evasionattack_path = os.path.join(repo_path, "src", "PyProject", "ConfigurationAttack", "Settings")

no_of_example_files = 2
# attackdir = repo_path + "data/evasionattack/"
attackdirConfig = config["AUTHORSHIP_EVASION"]["attack_dir"]

def createattackdir(attdir: str):
    if not os.path.exists(attdir):
        # raise FileNotFoundError("Attack dir '{:s}' does not exist.".format(attackdir))
        print("Attack dir does not exist. I will create it: {}".format(attdir), file=sys.stderr)
        os.makedirs(attdir)

noofparallelthreads = int(config["AUTHORSHIP_EVASION"]["noofparallelthreads"])
noofparallelattacks = int(config["AUTHORSHIP_EVASION"]["noofparallelattacks"])
savemorelogfiles = bool(int(config["AUTHORSHIP_EVASION"]["savemorelogfiles"]))

# csv file for external transformers
externaltransformercsvfile = os.path.join(repo_path, "src/ExternalTransformers/config_externaltransformers.csv")

# feature extractors
featureextractordir = os.path.join(repo_path, "src/LibToolingAST/cmake-build-release/feature_extraction")
featureextractordir_single = os.path.join(repo_path, "src/LibToolingAST/cmake-build-release/feature_extraction_single")
naivebaselinecmd = config["NAIVEBASELINE"].get("naivebaselinecmd", '')
if naivebaselinecmd == '':
    naivebaselinecmd = None


# Important: we should exclude these common words; especially "txt", "in" and "out" are important,
# since these are actually part of file names that authors use as test input. This is not the coding style.
stop_words_codestylo = ["txt", "in", "out", "attempt0", "attempt", "attempt1", "small", "output", "input"]

# clang-based transformers
transformersdir = os.path.join(repo_path, "src/LibToolingAST/cmake-build-release/transformers")
transformercsvfile = os.path.join(repo_path, "src/LibToolingAST/config_transformeroptions.csv")
codeinfodir = os.path.join(repo_path, "src/LibToolingAST/cmake-build-release/codeinfo")
ifostreampreppath = os.path.join(transformersdir, "IOTransformers", "ifostream_preprocessor")

flag_list = ['-w',
             '-std=c++11',
             '-I{}'.format(os.path.join(llvmconfig_libdir, "clang/5.0.0/include/")),
             '-include',
             '{}'.format(os.path.join(repo_path, 'src/LibToolingAST/ourerrors.h'))]

#flags = ' '.join(flag_list)

compilerflags_list = ['-w',
             '-std=c++11',
             '-include',
             '{}'.format(os.path.join(repo_path, 'src/LibToolingAST/ourerrors.h'))]

#compilerflags = ' '.join(compilerflags_list)


# External Transformers
iwyu_dir = config["EXTERNALTRANSFORMERS"].get("iwyu_dir", '')
if iwyu_dir == '':
    iwyu_dir = None


# Latex Stuff (for paper)
evaluation_latexresults_dir = config["LATEX"]["evaluation_latexresults_dir"]