# Authorship Evasion

## Overview
Here, you find different README files that belong to the different steps
of the project.

## First Steps

### Environment variables.

  - [Optional] Add to .profile an environment variable to the position of the authorship evasion repo.
    `export AUTHORSHIP_EVASION="PATH/TO/REPO/authorship-evasion/"`.

### Set up projects.

The project consists of multiple smaller sub projects to have a modular structure.
Each of the following directories has a own README file. Some projects
are optional, such as the java project (which is necessary for some layout features,
  which we not need necessarily).

1. The LibTooling AST project:
  - You will find a detailed README in the LibToolingAST directory. Please compile
  everything, as we will the feature extractors and transformers for
  code attribution and evasion, respectively.
  - You find the [README here](./LibToolingAST/README.md)

2. The Java Project [Optional]
  - You find the [README here](./CodeStyloJava/README.md)
  - is taken and adapted from Caliskan et al.
  - The driver class is the main entry...
  - the java-based features are already extracted for the full dataset, so you can read them,
  - but if you want to read the java-based features for a new file, you must create the jar file and export the path...

3. The python project:
  - You find the [README here](./PyProject/README.md)

4. ExternalTransformers [Optional]:
- Here, we put some information how we can integrate stand-alone tools such as
 Include-What-You-Use.
 - You find the [README here](./ExternalTransformers/README.md)
