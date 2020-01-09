# Authorship Evasion

## Overview
TODO... description how all pieces fit together...

## First Steps

1. Environment variables.

  - Add the bin path of clang to .profile or an equivalent file.
  For instance, `export PATH="/home/PATH-TO/clang+llvm-5.0.0-linux-x86_64-ubuntu16.04/bin:$PATH"`
  For instance, you should be able to call `llvm-config --libdir` directly from shell.
  Be careful, if you add the variable in .profile, you may have to log out and log in again, otherwise
  Python may not find the variable.

  - [Optional] Add to .profile an environment variable to the position of the authorship evasion repo.
    `export AUTHORSHIP_EVASION="PATH/TO/REPO/authorship-evasion/"`.

  - Adjust the config_example.ini file in PyProject.
    This file saves all paths that we need to consider, such as path to this repo, path to clang, etc.
    What you have to do:
        1. Copy config_example.ini to config.ini
        2. Adjust config.ini to your own paths
        3. For IWYU, use a path like: `/home/<YOUR_PATH>/iwyu-trunk/include-what-you-use/build/`
    - Assure that Configuration.py and config.ini are in the same directory.

2. Set up projects.

The project consists of multiple smaller sub projects to have a modular structure.

The python project:
- You need Python >= 3.6
- Look at the requirements.txt

The LibTooling AST project:
- You will find a detailed README in the LibToolingAST directory.

ExternalTransformers:
- Here, we put some information how we can integrate stand-alone tools such as
 Include-What-You-Use. 

The Java Project:
- is taken and adapted from Caliskan et al.
- The driver class is the main entry...
- the java-based features are already extracted for the full dataset, so you can read them,
- but if you want to read the java-based features for a new file, you must create the jar file and export the path...

- We've found some minor important bugs in the Naive Baseline implementation. That's why
we have reimplemented some features via clang. For example, the branching factor
can be determined much more reliably via the compiler than via regex. 
Moreover, we've adapted some other minor things. We added a character set
and it is now possible to add either the path of the different authors or a particular source file directly.
But we'd like to emphasize that it is very good that the authors have published their code.



