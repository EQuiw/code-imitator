# Authorship Identification and Evasion

## About this readme?

I'll explain everything you need to set-up.
Hopefully, you can test all the tools afterwards.
Finally, I will explain how this project is structured.

But first of all, please consider that writing a
documentation is work and no one likes that.
So don't be angry if there are some issues
that are not documented perfectly.

Another warning: the code transformations were implemented over
a longer period, so that some newer transformers could benefit
from a deeper understand of clang. Thus, parts that do the same thing
could be implemented differently (should not occur so often).

Moreover, to understand the code transformations, you should have
a good understand of clang and LibTooling.

Last warning: *Do NOT use the code transformers in real-world applications.*
They work well for our considered dataset. They will not be applicable
to other datasets in general. For instance, our transformers assume a
single source file and do not resolve dependencies across multiple cpp/h files.
To this end, you will need to adapt the transformers.

## Getting Started

What you need
- LLVM and Clang 5.0.0
    * If your OS is supported, you can simply download the pre-compiled
    packages, e.g. if you have Ubuntu.
        - Visit http://releases.llvm.org/download.html and select
        e.g. `Clang for x86_64 Ubuntu 16.04` if you're using Ubuntu.

    * [Recommended] Set `$PATH` to clang+llvm so that you can
    run `llvm-config` from your command line. Actually you don't need to set
    $PATH, but if you will try some things on the command line later, it is
    really useful. To add the path information, you may add
    `export PATH="/home/PATH-TO/clang+llvm-5.0.0-linux-x86_64-ubuntu16.04/bin:$PATH"`
    to your .profile or .bashrc if you are using Ubuntu 16.04.
    * Take care not to use clang 5.0.1 (otherwise,
      you might need to adapt paths, such as in Configuration.py).

- cmake >= 3.9 (probably an older version will
    also work)

- gnu parallel >= 20161122

- Boost (header files)
    * We just need the header files for the graph datatype, no build process.
    * We used Boost 1.65.1, simply download boost_1_65_1.tar.gz from the
    [official website](https://www.boost.org/users/history/).


Afterwards, you should have installed gnu parallel and cmake. And you
should have the following two directories:
  - clang+llvm-5.0.0-linux-x86_64-ubuntu16.04
  - boost_1_65_1

## Further requirements
- In the case that you get some errors in the following compilation steps,
it can be that the following libraries are missing or a link is missing.

- In the case of the cmake error 'cannot find -lstdc++',
you may follow the following instructions:
https://github.com/box/augmented_types/issues/11

- Sometimes necessary:
```
sudo apt-get install libstdc++-5-dev
sudo apt-get install libtinfo-dev
sudo apt-get install lib32z1-dev
sudo apt-get install build-essential
```

With Ubuntu 20, the following will be necessary:
```
sudo apt-get install libncurses5
```

- Sometimes, it is also necessary to install `libgmp-dev` (via apt-get install)

## Compilation
I describe two ways.

### IDE
* In clion, you include the LibTooling directory as project.
* Set Cmake option:
  `-DMY_CLANG_ROOT_DIR=/home/path/to/clang+llvm-5.0.0-linux-x86_64-ubuntu16.04`
* Set Cmake option:
  `-DMY_BOOST_ROOT_DIR=/home/path/to/boost_1_65_1`
* Depending on the clang+llvm version you have downloaded, you may need
to adapt the paths of course.

* Compile all in release-mode. In debug-mode, we will print some debug-messages.

### Command-line
* go to LibTooling directory.
* Then run
```
mkdir cmake-build-release
cd cmake-build-release
```
* Then run
```
cmake .. -DMY_CLANG_ROOT_DIR=<path-to>/clang+llvm-5.0.0-linux-x86_64-ubuntu16.04 -DMY_BOOST_ROOT_DIR=<path-to>/boost_1_65_1
make
```

## A first example

- Let's try to extract the AST node types.
1. Import the project into your IDE...
2. Run cmake
3. Run configuration.
    * Let's run `get_ast_node_types.cpp`



## Technical Details About the Project
- The following is only necessary to read if you are planning to use LibTooling
 or to adapt our code transformations. If you are more interested in misleading
 the code attribution, you just need to compile the transformers as described
 above. You can then skip this section.

### Structure
- We decided to implement each feature class
in a modular way, so we may have some redundant
code sometimes, but for each class we have another
tool which should be easier to understand...

- Structure: Our directories are:
    * `feature_extraction`: Contains the lexems feature extractor.
    * `feature_extraction_single`: One tool to
    extract AST features.
    * `codeinfo`: here, we put all tools that list some information
    about a given target file. For example, list all variable names
    or list all typedefs.
    * `tests`: test scripts based on Catch
    * `transformers`: Here, we have all scripts to do the code
    transformations during the evasion attack.
    It is a larger directory, see below for an detailed introduction.
    * `Utilities`: some utilities that are helpful across all tools.

- Furthermore some important files:
  - `ourerrors.h`: it add some includes that are necessary to compile many files.
  Actually the same as `microsoft_errors.h` which contains some includes to
  let files compile that have microsoft-specific commands. In addition, we need
  to add a bool type, otherwise we often obtain an error (thus the `ourerrors.h` name)
  - `config_transformeroptions.csv`: contains a list of all used code transformations
  for our usenix paper. It contains all the informations that are need to call
  the transformations from our Python implementation!

### Feature Extraction

- Each tool for a particular feature set has two
files: one where the main method is in and another
file where the rest is located. Why? Because
we have tests in the tests-directory that also
need the file and we cannot have two main methods
as entry points.
    * Example: `lexical_features` contains
    all the stuff we need to extract this feature
    set. `get_lexical_features` just contains
    the main method. In `/tests/test_get_lexical_feature`
    we also use `lexical_features`, so you see
    why we use two files..

- All tools are called by our bash script
`extractfeatures_single.sh`. Read the
[attribution-markdown](../PyProject/README_ATTRIBUTION.md) to find out more
how to extract the features.

### Tests
- In the `tests` directory.
- Based on catch library that is already in the dir.

### Transformers

- Structure:
    - Each transformer has its own main entry point. So it should be
        easier to find out how a code transformer works.
    - The directory ControlDataFlow contains some classes when we work
        with a Control Flow Graph (CFG). Note that not each
        transformer needs the CFG, but sometimes it is helpful.
    - Many transformers are implemented in the 'transformers' directory,
    but we've created an own subdirectory for some transformers to get a
    better structure (e.g. typedef-transform)
    - We have various utils files that implement helpful things.


- Getting Started: The easiest transformation is the
    `compoundstmt_transf.cpp`. So look at this
    code transformation first in order to understand
    how a transformation works. All the other code
    transformations have a similar structure.

    - Read the compound-statement-readme.md where I've described
    some more steps that are relevant when rewriting source code with clang.

- How to call a transformer:
  - Each transformer has the following structure of cmd line:
  <file> <transformer-options> -- <compiler-options>.
  For instance, for if-transformer, we need to add the following
  arguments:
  `sometest.cpp -strategy=1 -seed=31 -- -I/home/sectubs/Documents/clang+llvm-5.0.0-linux-x86_64-ubuntu16.04/lib/clang/5.0.0/include -include /home/sectubs/Desktop/authorship-evasion/src/LibToolingAST/ourerrors.h`

  - For each transformer, you have to adapt the transformer options and
  of course the file you want to analyze. The compiler options
  are the same for each transformer.

  - Finally, *use clang-format before and after calling a code transformer*. A few
  code transformations assume that the source code is properly formatted.

  - Last remark: Currently, we can only rewrite a single file that contains
  all the stuff that is required for the current program. Multiple files
  are not supported, currently. This is no limitation for the Google Code Jam
  competition, but of course, we would need to change a few things for multi-file
  projects..

- Differences to paper. You will not always find a 1:1 transformer-name to the listed
names in the paper. For instance, the Declaration Transformer here includes
the various bool, floating-type or char-string transformations. The reason is that
we've changed the grouping for an easier understanding without refactoring all files.
- CFG and DRM: Note that the CFG also contains the DRM, so that we can also query
all references to a variable or function via the CFG. However, later, we found that
multiple declarations in a row outside of functions are not covered by the CFG and moreover
are not covered by a DeclStmt; we have to use the SourceLocation here. That's why we later
added an explicit DeclReference Mapping for variables that uses the source location. (see init-decl-transformer).
If possible, use the newer API for variables, and the CFG for function references.

- Status Codes:
  The code transformers return status code to tell our python code what happened.
  - 124: If no code location exists anymore where we can use our code transformer,
  we return the code 124
  - 123: If our code transformer was not able to rewrite a code location
  although there was an opportunity, we return the code 123
  - There are some more status codes that are specific to some transformers.
  -

### Unused Transformers
- IncludeSort, can be used directly in Python via adding:
`includesort_transformer,,declaration,IncludeSort,sort-includes,IncludeSortTransformer,include-list/include-list`
to config_transformeroptions.csv.


### Future work
  - There are things that occur very often, e.g. to include all headers,
  include all declaration names, namespaces and so. I think, in future, we
  could create some upper class that collects all these information and
  then each each transformer should inherit this class.
  - So far, we switched to a new SourceText API that is located in
  `transformers/lib/SourceTextHelper`; we should get rid of all instances
  where we use the old getSourceText(Context, stmt) and instead use
  getSourceTextStable. Moreover, we should remove all instances with
  getSourceText + Semicolon which was only a temporary hack.
  - Overall, we should remove more getSourceText checks and use the appropriate
  API from clang.
