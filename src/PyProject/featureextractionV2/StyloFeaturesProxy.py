from featureextractionV2.StyloFeatures import StyloFeatures
import numpy as np
import typing


class StyloFeaturesProxy(StyloFeatures):
    """
    Handler to call all feature objects.

    We could easily implement a caching principle here, so that the feature matrix calculation is only
    done if something changes (e.g. by a tf-idf call). But we would need to implement here
    some sort of observer design pattern so that this class always knows if a referenced
    StyloFeatures object has changed.
    """

    def __init__(self, codestyloreference: StyloFeatures):
        super(StyloFeaturesProxy, self).__init__()
        self.codestyloreference = codestyloreference


    def getunique_key(self) -> str:
        return "_".join(["merged"])


    def getfeaturematrix(self):
        return self.codestyloreference.getfeaturematrix()

    def getcolnames(self):
        return self.codestyloreference.getcolnames()

    def getcolnamesraw(self):
        return self.codestyloreference.getcolnamesraw()

    def getauthors(self):
        return self.codestyloreference.getauthors()

    def getiids(self):
        return self.codestyloreference.getiids()

    def getlabels(self):
        return self.codestyloreference.getlabels()

    def createtfidffeatures(self, trainobject: typing.Optional['StyloFeatures']) -> None:
        if trainobject is not None:
            self.codestyloreference.createtfidffeatures(trainobject=trainobject.codestyloreference)
        else:
            self.codestyloreference.createtfidffeatures(trainobject=None)

    def selectcolumns(self, index: typing.Optional[np.ndarray], trainobject: typing.Optional['StyloFeatures']) -> None:
        if trainobject is not None:
            self.codestyloreference.selectcolumns(index=index, trainobject=trainobject.codestyloreference)
        else:
            self.codestyloreference.selectcolumns(index=index, trainobject=None)

    def __getitem__(self, index):
        return StyloFeaturesProxy(codestyloreference=self.codestyloreference[index])


    # def __getitem__(self, index):
    #     """
    #     Implements the row-access via [].
    #     For example, you can select the wanted rows via obj[2:5] now.
    #     :param index: the wanted indices
    #     :return: a new object with filtered rows.
    #     """
    #
    #     new_codestyloobject_list = []
    #     for i in range(len(self._codestylobjects)):
    #         c = self._codestylobjects[i][index]
    #         if isinstance(c, list):
    #             new_codestyloobject_list.extend(c) # if we get a list of stylo objects, e.g. from StyloClangFeaturesGenerator
    #         else:
    #             new_codestyloobject_list.append(c) # if we get a single stylo object, e.g. from StyloUnigramFeatures
    #
    #     return StyloFeaturesProxy(new_codestyloobject_list)