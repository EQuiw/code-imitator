import typing

import classification.LearnSetups.LearnSetup
import pandas
import os
import random
from evasion.Author import Author, AuthorException
from evasion.AttackResult import AttackResult
from abc import ABC, abstractmethod
import sys


class AttackEvalAbstract(ABC):

    def __init__(self,
                 testlearnsetup: classification.LearnSetups.LearnSetup.LearnSetup,
                 attack_dir: str,
                 no_authors: typing.Optional[int],
                 selected_authors: typing.Optional[typing.List[str]],
                 seed: int = 31,
                 verbose: bool = False,
                 ) -> None:
        """
        Create matrix of author pairs for impersonation or dodging.
        :param testlearnsetup: the learn setup
        :param attack_dir: the directory where attack will take place
        :param no_authors: we try to create matrix of A x A authors. If not possible it will raise an Exception.
        If None, all authors are used.
        :param selected_authors: if given, only authors from this string list are selected...
        :param seed: a seed, necessary if no_authors is given to subsample...
        :param verbose: print status if true
        """

        # A. Init..
        self.testlearnsetup = testlearnsetup
        self.attack_dir = attack_dir
        self.possible_authors: typing.Dict[str, Author] = {}

        if selected_authors is None:
            selected_authors = testlearnsetup.data_final_test.getauthors().tolist()

        if no_authors is None:
            no_authors = len(selected_authors)

        # B. Get authors that are correctly classified
        authors_to_choose: typing.List[str] = selected_authors
        assert no_authors <= len(authors_to_choose)

        # randomly sort list if number of wanted authors is smaller than possible authors
        if len(authors_to_choose) != no_authors:
            random.seed(seed)
            random.shuffle(authors_to_choose)

        for i in range(len(authors_to_choose)):
            try:
                sourceauthor = Author(author=authors_to_choose[i], learnsetup=self.testlearnsetup)
                sourceauthor.check_is_correct(learnsetup=self.testlearnsetup, verbose=verbose)

                self.possible_authors[sourceauthor.author] = sourceauthor
                if len(self.possible_authors) == no_authors:
                    break
            except AuthorException as e:
                continue


        if len(self.possible_authors) != no_authors:
            print("Could not collect the wanted number of authors. Got only {}".format(len(self.possible_authors)), file=sys.stderr)

        print("Could collect authors: Got {}".format(len(self.possible_authors)))
        print("Their names are: {}".format(self.possible_authors.keys()))


        # C. Init matrix
        self.authorEvasionMapping = pandas.DataFrame(columns=self.possible_authors.keys(), index=self.possible_authors.keys())
        self.authorEvasionMapping = self.authorEvasionMapping.fillna(0)

        self.rowindex = 0
        self.colindex = 0


    @abstractmethod
    def getNextAuthorPair(self, fix_src: typing.Optional[str] = None, fix_tar: typing.Optional[str] = None,
                          fix_pair: typing.Optional[typing.List[typing.Tuple[str, str]]] = None):
        pass


    def setAuthorPairResult(self, attackresult: AttackResult):

        self.authorEvasionMapping.iloc[self.rowindex, self.colindex] = attackresult

    def setAuthorPairResult2(self, attackresult: AttackResult, sourceauthor: Author, targetauthor: Author):

        self.authorEvasionMapping.loc[sourceauthor.author, targetauthor.author] = attackresult



class AttackEvalImpersonation(AttackEvalAbstract):

    def __init__(self,
                 testlearnsetup: classification.LearnSetups.LearnSetup.LearnSetup,
                 attack_dir: str,
                 no_authors: typing.Optional[int],
                 selected_authors: typing.Optional[typing.List[str]],
                 seed: int = 31,
                 verbose: bool = False,
                 ) -> None:
        super(AttackEvalImpersonation, self).__init__(testlearnsetup, attack_dir, no_authors, selected_authors,
                                                     seed,
                                                     verbose)


    def getNextAuthorPair(self, fix_src: typing.Optional[str] = None, fix_tar: typing.Optional[str] = None,
                          fix_pair: typing.Optional[typing.List[typing.Tuple[str, str]]] = None):
        """
        Get the next author pair. You can fix the source or target author by specifying their name.
        :param fix_src: Either None or set name to just iterate over fixed src-author and all other tar-authors
        :param fix_tar: Either None or set name to just iterate over all src-authors and fixed tar-author
        :param fix_pair: Either None or a list of author pairs (src to target) that should be evaluated.
        :return: source author, target author objects as well attackdirauth path
        """

        for self.rowindex in range(self.authorEvasionMapping.shape[0]):
            for self.colindex in range(self.authorEvasionMapping.shape[1]):
                if self.rowindex == self.colindex:
                    continue

                source_author_str = self.authorEvasionMapping.index[self.rowindex]
                target_author_str = self.authorEvasionMapping.index[self.colindex]

                if fix_src is not None and source_author_str != fix_src:
                    continue
                if fix_tar is not None and target_author_str != fix_tar:
                    continue

                if fix_pair is not None and (source_author_str, target_author_str) not in fix_pair:
                    continue

                sourceauthor: Author = self.possible_authors[source_author_str]
                targetauthor: Author = self.possible_authors[target_author_str]

                attackdirauthtarget = os.path.join(self.attack_dir, target_author_str, source_author_str)

                yield sourceauthor, targetauthor, attackdirauthtarget




class AttackEvalFixedDodging(AttackEvalAbstract):

    def __init__(self,
                 testlearnsetup: classification.LearnSetups.LearnSetup.LearnSetup,
                 attack_dir: str,
                 no_authors: typing.Optional[int],
                 selected_authors: typing.Optional[typing.List[str]],
                 seed: int = 31,
                 verbose: bool = False,
                 ) -> None:
        super(AttackEvalFixedDodging, self).__init__(testlearnsetup, attack_dir, no_authors, selected_authors,
                                                     seed,
                                                     verbose)


    def getNextAuthorPair(self, fix_src: typing.Optional[str] = None, fix_tar: typing.Optional[str] = None,
                          fix_pair: typing.Optional[typing.List[typing.Tuple[str, str]]] = None):
        """
        Get next author.
        :param fix_src: Either None or set name to just iterate over fixed src-author and all other tar-authors
        :param fix_tar: Will be ignored.
        :param fix_pair: Will be ignored.
        :return: source author, target author objects as well attackdirauth path
        """

        for self.rowindex in range(self.authorEvasionMapping.shape[0]):
            for self.colindex in range(self.authorEvasionMapping.shape[1]):
                if self.rowindex != self.colindex:
                    continue

                source_author_str = self.authorEvasionMapping.index[self.rowindex]
                target_author_str = self.authorEvasionMapping.index[self.colindex]

                if fix_src is not None and source_author_str != fix_src:
                    continue

                sourceauthor: Author = self.possible_authors[source_author_str]
                targetauthor: Author = self.possible_authors[target_author_str]

                attackdirauthtarget = os.path.join(self.attack_dir, source_author_str)

                yield sourceauthor, targetauthor, attackdirauthtarget
