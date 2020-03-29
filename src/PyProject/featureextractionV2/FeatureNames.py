class FeatureName:
    """
    Class to store a feature name for a feature matrix,
    incl. the exact feature name, its origin and if post-processed via tf-idf.
    Why do we need this class? A feature like 'char' may occur as Unigram, as code-in-ast-leaf and
    as tf and -tfidf feature.
    """

    def __init__(self,
                 colname: str,
                 coltype: str,
                 colorigin: str,
                 tf: bool = False,
                 idf: bool = False):
        """
        :param colname: feature name (type: str)
        :param coltype: the column type (continous vs. categorial)
        :param colorigin: the origin (unigram, code-in-ast-leaf, arff, ...)
        :param tf: if tf processed
        :param idf: if idf processed
        """
        self.colname: str = colname
        self.coltype: str = coltype
        self.colorigin: str = colorigin
        self.tf: str = "" if tf is False else "tf"
        self.idf: str = "" if idf is False else "idf"

    def __str__(self):
        return "_".join([self.colname, self.colorigin, self.tf, self.idf])

    def settfidf(self, tf: bool, idf: bool):
        self.tf: str = "" if tf is False else "tf"
        self.idf: str = "" if idf is False else "idf"

    def getstrwithouttfidf(self):
        return "_".join([self.colname, self.colorigin, "", ""])
