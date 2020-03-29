############### Variable Definition ##############
import configparser
import os



### Read config.ini to get all path information such as path to this repo, path to clang, path to IWYU, ...
__config_ini_file_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "config.ini")
config = configparser.ConfigParser()
config.read(__config_ini_file_path)


### Now set values
# Get the path to repository
repo_path = config["AUTHORSHIP_EVASION"]["root"]
learnmodelspath = os.path.join(repo_path, "data/ClassificationModels")

# Dataset Settings
probsperprogrammer = 8 # How many problems/challenges per author?


# Important: we should exclude these common words; especially "txt", "in" and "out" are important,
# since these are actually part of file names that authors use as test input. This is not the coding style.
stop_words_codestylo = ["txt", "in", "out", "attempt0", "attempt", "attempt1", "small", "output", "input"]

noofparallelthreads = int(config["AUTHORSHIP_EVASION"]["noofparallelthreads"])



# Latex Stuff (for paper), only necessary for analysis afterwards...
evaluation_latexresults_dir = config["LATEX"]["evaluation_latexresults_dir"]
