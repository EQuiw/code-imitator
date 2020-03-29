import numpy as np
import pandas
from evasion.AttackStatus import AttackStatus
from evasion.Author import Author
import typing
import io
import difflib

class AttackResult:

    def __init__(self, sourceauthor: Author, targetauthor: Author):
        self.sourceauthor: Author = sourceauthor
        self.targetauthor: Author = targetauthor

        self.attackstatus: AttackStatus = AttackStatus.NOSUCCESS

        # here, we save the error message if the result contains an unexpected error [err-msg, traceback]
        self.error_message: typing.List[typing.Optional[str], typing.Optional[str]] = [None, None]
        # self.score: float = None

        self.log_chosentransformers: pandas.DataFrame = None

        self.initial_feature_vec: np.ndarray = None
        self.final_feature_vec: np.ndarray = None

        self.linesofcode_before: int = None
        # self.changedlinesofcode_plus: typing.List[str] = None
        # self.changedlinesofcode_minus: typing.List[str] = None
        self.linesofcode_after: int = None
        self.contextdiff: dict = {}

    def extract_changes_linesofcode(self, pathtooriginalfile: str, pathtonewfile: str) -> None:
        """
        Extract the changed code lines.
        :param pathtooriginalfile: the original cpp file
        :param pathtonewfile: the new cpp file after evasion
        """

        with io.open(pathtooriginalfile, "r", encoding="iso-8859-1") as curf:
            lines_bef = [line for line in curf]
        with io.open(pathtonewfile, "r", encoding="iso-8859-1") as curf:
            lines_aft = [line for line in curf]

        self.linesofcode_before = len(lines_bef)
        self.linesofcode_after = len(lines_aft)

        # compute context diff, count the lines that were removed, added, and changed.
        minus_before = 0
        plus_after = 0
        changes = 0
        before = False

        # we go over context-diff output and if we count depending on if we look at 'before' or 'after'
        diff = difflib.context_diff(a=lines_bef, b=lines_aft, fromfile="before", tofile="after")
        for x in list(diff):
            if x.startswith("*** before") or x.startswith("--- after"):
                continue
            if x.startswith("*** "):
                # lineid = x.split(" ")[1].strip()
                before = True
                continue
            if x.startswith("--- "):
                # clineid = x.split(" ")[1].strip()
                before = False
                continue

            if before and x.startswith("- "):
                minus_before += 1

            if not before and x.startswith("+ "):
                plus_after += 1

            if before and x.startswith("! "):
                changes += 1


        self.contextdiff["minus_before"] = minus_before
        self.contextdiff["plus_after"] = plus_after
        self.contextdiff["changes"] = changes


    def __str__(self):
        return "AttackResult:" + "-".join([self.sourceauthor.author, self.targetauthor.author, self.attackstatus.name])


