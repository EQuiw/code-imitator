# Authorship Attribution
This section describes how to perform authorship attribution.
You can use the code as a stand-alone code for attribution tasks or you will
need this step as a requirement for the attacks, of course.

You can either use our dataset (Google Code Jam contest 2017) or
your own dataset. If you're using our dataset, you do not need to
consider the *dataset* step, as the formatted dataset
is also part of the repository.

## Dataset & Features

### Dataset [Optional]
- Under the repository's root directory in data/dataset_2017, you will find the
used dataset.
- We added the raw dataset, the formatted dataset via clang-format, and
the dataset where we also processed macros.

- If you have a new dataset, make sure you have the following format:
  - In your dataset directory, each author should have its own directory.
  - Each author directory should contain all the challenges/problems.
  - Each file should have the following format: ```<round-id>_<challenge-id>_<authorname>.cpp```

- Then, run the following scripts in this order:
  - clangformat.sh
  - remove_macros.sh
  - Adjust the paths of course.

### Features
First of all, we need to extract the features for a dataset.
We've build the extractors with clang, so you need to compile at least
the feature extraction commands.

1. Now go to the data directory under the project's root directory.
2. You will find there a extractfeatures_single.sh.
  - Adjust the path to the java jar.
    I've used an environment variable CMD_DIR_NAIVEBASELINEJAR but you can set the path here simply.
  - Adjust the relative paths to the dataset.
    - Adjust the variables SRC and OUTPUT_DIR
  - The remaining paths are extracted automatically.
3. Run the bash script.


## Machine Learning
Now we switch to the python world. We have all the features as json file.
For our USENIX paper, the features are located under *data/dataset_2017/libtoolingfeatures_2017_8_formatted_macrosremoved*.

The next step is to extract these files in Python and to create a feature matrix.
Then, we will learn a classification model to differentiate between the authors.

### Getting started
- Load the python project *PyProject* into your IDE (e.g. PyCharm).
- Make sure your root directory is PyProject.
- Alternatively, you may need to set up the python path. Or if you're in your terminal,
you can set the path for each python call, such as:
```
$PYPATH="/<path-to-repo>/src/PyProject"
$PYTHONPATH=${PYPATH} python evaluations/blackbox/attack/blackbox_attack_batch.py
```

### Test your setup
1. Open the python file *UnitTests/testFeatureExctraction.py*. All tests should pass.
2. Open the python file *UnitTests/test_learning.py*. All tests should pass.

If something goes wrong, check if all your paths are correctly set.
Check that all files are present. Check you've called the file with the correct
python path. Otherwise, you can contact me if you cannot find the error.

### Learn your first model
Now let's look how we can learn a simple classification model.

#### Structure
A short introduction to the python directories, as located under *PyProject*:
- *evaluations*
  - *learning*
    - This directory contains the code to learn classification models
    on the dataset with the method by Caliskan et al. and by Abuhamad et al..
    We call the first method "rf_usenix", the second "rnn_css" based
    on the conference and the proposed learning model.
    - *post_learning_steps*: This directory contains some analysis scripts to evaluate the learning
      results. We can analyze the accuracy and the extracted features for
      code attribution. We also collect a list of author pairs that are
      successfully classified across all problems in our dataset.
      Furthermore, we have a script to get author pairs that are successfully
      classified across all problems by *both* models
      (Caliskan et al. and Abuhamad et al.). This is useful
      for our impersonation evaluation, as the pairs should be classified
      correctly before any attack.
- *classifications*
  - This directory contains all the learning code.
- *ConfigurationLearning*
  - These classes here bundle all the settings for learning.
- *featureextraction*
  - All classes that extract the different types of features.

#### Learning
- Open ```evaluations/learning/rf_usenix/train_models_parallel.py```
- If you do not start the script via bash (see start_train_models_parallel.sh),
 pass the PROBLEM_ID in python as string simply, and remove the args parser.
- Go through the script step by step.
- For Abuhamad et al., we have an equivalent script located under *rnn_css*.

### Some notes about the feature classes
- In the following, I will introduce the different feature classes
in the directory *PyProject/featureextraction*.
- *CodeStyloFeatures*  is the abstract parent class.
- Then, we have a child class for the different sources of features.
We have features that we load from the java implementation by Caliskan et al,
we have features we can get from Python directly and we have features that we obtain from our clang implementation (all the AST features).
- Features sources:
  1. *CodeStyloARFFFeatures* contains the features that we load from the
  Java implementation by Caliskan et al..
    - It mostly contains layout features.
    - The lexical features that are present in this feature type
    are also present in our other feature sources. Therefore, you will often see that we do not load the ARFF features in our experiments.
    And that's why it is actually optional to set up all the java stuff.
    - Example: the number of functions is also given by an AST node type.
  2. Unigrams / Lexems:
    - We have two classes *CodeStyloUnigramFeatures* and *CodeStyloLexemFeatures* to get unigram features.
    - The first loads the source code files in Python, and tokens are directly
    extracted in Python.
    - The second class loads the lexems extracted by clang.
    - Both methods have almost the same output, and you can use the python
    version for convenience.
  3. *CodeStyloJoernFeatures*:
    - This class contains all clang-based features, such as AST bigrams or
      AST code in leaves features.
- *CodeStyloMergedFeatures* is a class to bundle all different feature classes.
It serves as a proxy to the individual feature classes, so that we can use
a single feature matrix later.

- Another remark about the td-idf stuff: It is important that we perform
the tf-idf transformation only on the respective training set for any split
during the cross-validation. That's why we have the function *gettfidffeatures*.
If we have a training feature matrix, we call it without a trainingobject. Then,
we perform a tf-idf weighting on the training matrix. Later for the 'test'
matrix, we can simply pass the training object and we use the normalization
parameters from the  training step for the test matrix as well. This avoids
data snooping.
