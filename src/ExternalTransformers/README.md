# External Transformers

- Here, we put stand-alone tools that we can also use to rewrite code, e.g.
 we use Include-What-You-Use to detect what unused headers we can remove and
what headers we should include.

Consider that each external transformer is optional, so if you don't set the environment
variables, we will skip the respective transformer during evasion attack.
In this way, you can quickly set up our project and do some transformations, and if necessary,
add the helpful external transformers later.

## Overview

1. Include-What-You-Use
- We use IWYU from the official website:
https://github.com/include-what-you-use/include-what-you-use
- A possible sequence of commands (works for Ubuntu) is:
  ```
  git clone https://github.com/include-what-you-use/include-what-you-use.git
  cd include-what-you-use
  git checkout clang_5.0
  mkdir build
  cd build
  cmake -G "Unix Makefiles" -DIWYU_LLVM_ROOT_PATH=<path-to>/clang+llvm-5.0.0-linux-x86_64-ubuntu16.04 ..
  make
  ```
- Summary of steps:
  - Make sure you checkout the branch that corresponds to clang 5.0.
  - Please create the *build* directory inside of include-what-you-use
  - Set the correct path to your clang directory for iwyu.
- Add the full path of *include-what-you-use/build* to config.ini in PyProject.

- Finally, make sure you have python2 installed. Otherwise, the bash script 
src/ExternalTransformers/iwyu_replace.sh will not work. It is the only location
where python 2 is somehow needed in our attribution+evasion project.

2. no other external transformers, yet


## Problems
In case of problems with IWYU, you may need to install
- libncurses5-dev


## How to add your own external transformer
In short:
- modify csv in this directory
- create own Python class that inherits from TransformerBase
- add code to `__load_external_transformers` in TransformerHandler
- add path to dir of executable to config.ini and Configuration.py
