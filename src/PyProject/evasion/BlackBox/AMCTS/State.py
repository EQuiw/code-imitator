import typing
from evasion.Transformers.TransformerBase import TransformerBase
# from evasion.Transformers.TemplateTransformers.AddTemplateTransformer import AddTemplateTransformer
import numpy as np

# Note #1:
# We use the transformer-id + cmd line options except seed as unique state id to repeat transformer

# Note #2:
# As we do not use the seed to save branches, it can happen that a transformer fails.
# Following example: Assume node u is root.
# We create a sequence with for-transformer seed=1 and for-transformer seed=2.
# Another sequence is for-transformer seed=3 and for-transformer seed=4.
# First sequence fails after first transformer, as seed 2 leads to a for-loop that we cannot replace.
# Second sequence works completely.
#
# In tree, we save the first occurence, without seed, so we have a path "<for-transformer>, <for-transformer>".
# Now in perform-next-move, we select the for-transformer (in principle the one with seed=1, as it was the first).
# However, in tree, the 2nd sequence is saved with for-transformer seed=4 as child.
# If we want to select this promising node, it can happen that the base file where we work is a different
# what the original for-transformer (seed=4) actually had (it had seed=3, and not seed=2).
# We could easily solve this problem, by using the seeds in the state_id's, but then we would have
# a very large branching factor in search tree.



class State:

    def __init__(self,
                 transformer: typing.Optional[TransformerBase] = None):

        self.VisitCount: int = 0
        self.Scores: typing.List[float] = []


        # State id is the transformer unique id + the seed if we have template transformers, otherwise just id
        if transformer is None:
            self.transformer_uniqueid = None
            self.seed = None
            self.simplified_transformer_call = None
            self.state_id = None
        else:
            self.transformer_uniqueid = transformer.uniqueid
            _, self.simplified_transformer_call, _, self.seed = \
                transformer.load_information_about_last_call()
            # parse transformer_call and get options from fillcmdline, but exclude seed
            self.state_id = transformer.obtain_unique_last_state_id()


    def getMeanScore(self):
        if len(self.Scores) == 0:
            return 0.0
        else:
            x = np.array(self.Scores)
            return np.mean(x)

    def getSdScore(self):
        if len(self.Scores) == 0:
            return 0.0
        else:
            x = np.array(self.Scores)
            return np.std(x)
