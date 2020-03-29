# Authorship Attribution Attacks
This section describes the attacks against authorship attribution.

## Getting started
Make sure you've followed the instructions from the attribution readme.
For the evasion setup, I strongly recommend using a virtual machine
to avoid running the experiments on your local computer. While most
of the operations are secure, we let the source code of each author
run for a few seconds to collect the output (in this way, we can also
test if the code transformer has not changed the behavior). Thus,
you should run these experiments on a separate machine. Everything
here is on your own risk.


## Test your setup
Open the python file *UnitTests/EvasionTesting/test_AMCTS_SimAnnealing.py*.
It is actually not a JUnit test, but the attacks should work for the
combination of authors.

## Remarks
There are few issues that may impact your results.
- First of all, the results / evasion rate depends on the time you let
the system work. We need to transform code and then run the compiled
source code to check for the output. If your system is slow and the time
to run exceeds our threshold, the code is treated as non-valid, although
a few seconds more would lead to the correct result.
- The transformers work in C++, the MCTS-based attack works in Python.
We call the transformers by starting a subprocess in Python. This is slow,
and nowadays, I would have integrated them via Cython directly.
- Thus, all the attacks are slow and it takes some time to evaluate
everything for all authors.

## Evaluation
For the evaluation, look at the file *PyProject/evaluations/blackbox/attack/blackbox_attack.py*.

The directory *PyProject/evasion* contains all the classes / methods
for performing the evasion attack.

## Future Work
- We should be able to call the code transformers from Python directly.
