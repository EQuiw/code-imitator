# Python Project Authorship Evasion

This directory contains all the code to perform
authorship attribution based on the extracted features and
to perform the attacks.

## About

In particular, you'll find here the code for the following
two groups of experiments:

1. *Code Authorship Attribution.* Extract features for a dataset and try to
assign source code to authors. This is completely independent of the attacks.
2. *Authorship Attacks.* This group allows attacks
against the learning models from step 1.

## Setup
In this directory, you will find a *requirements.txt* and *config_example.ini*
file. We will need both files in the following.

1. Create a virtualenv or conda environment (strongly recommended).
I've tested everything with conda. Use Python 3.6, with conda,
you can use ```conda create --name authorshipevasion python=3.6```.
Then activate the environment via ```conda activate authorshipevasion```.

2. Install via ```pip install -r requirements.txt``` the dependencies
in your python environment. I strongly recommend using a virtualenv or
conda environment.

3. Adjust the configuration in PyProject.
  - The config file saves all paths that we need to consider, such as path to this repo, path to clang, etc.
  What you have to do:
      1. Copy config_example.ini to config.ini
      2. Adjust config.ini to your own paths
      3. For IWYU, use a path like: `/home/<YOUR_PATH>/iwyu/include-what-you-use/build/`
  - Assure that Configuration.py and config.ini are in the same directory.


## Attribution
Read the [attribution-markdown](./README_ATTRIBUTION.md) file to get the details how to set up
the whole attribution.

## Evasion attacks
Read the [evasion-markdown](./README_EVASION.md) file for an introduction
of our MCTS-based attack against authorship attribution.
