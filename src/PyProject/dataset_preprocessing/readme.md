# Dataset Preprocessing

- Everything that we need to do on the dataset

1. remove_macros.py
    With this file, we can remove macros from the dataset with clang's preprocessor.
    However, the proprocessor also removes headers, that's why we need the python file
    that includes the headers again after preprocessing.

2. DatasetTesting
    Here, we can check if an author produces an output file for a given input
    file. This is necessary, because some authors may have implemented some
    programs that never terminate for the test cases from Google Code Jam
    or create empty files.
