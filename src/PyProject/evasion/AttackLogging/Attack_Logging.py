import logging
import os
import sys
#
# class _MyFilter(logging.Filter):
#     def __init__(self, level):
#         self.__level = level
#         logging.Filter.__init__(self)
#
#
#     def filter(self, record):
#         return record.levelno <= self.__level



class Logger:
    """
    Class for logging each evasion attack.
    We have three levels of logging, info just for high-level information, debug for detailed information,
    error for error messages of course. We also write the info messages to stdout so that we can always see
    th of the evasion attack.
    != Parallel_Logging.py that logs the overall progress over all evasion attack instances.
    """

    DEBUGDETAILS_LEVEL_NUM = 9

    def __init__(self, logfilepath: str, logging_id: str):

        self.logfilepath: str = logfilepath
        self.logger = logging.getLogger(logging_id)
        self.logger.setLevel(logging.DEBUG)

        # create a file handler for various output levels
        self.handlerInfo = logging.FileHandler(os.path.join(logfilepath, 'info.log'), mode="w+")
        self.handlerInfo.setLevel(logging.INFO)
        self.handlerDebug = logging.FileHandler(os.path.join(logfilepath, 'debug.log'), mode="w+")
        self.handlerDebug.setLevel(logging.DEBUG)
        self.handlerError = logging.FileHandler(os.path.join(logfilepath, 'error.log'), mode="w+")
        self.handlerError.setLevel(logging.ERROR)
        self.handlerDebugDetails = logging.FileHandler(os.path.join(logfilepath, 'debug_details.log'), mode="w+")
        self.handlerDebugDetails.setLevel(Logger.DEBUGDETAILS_LEVEL_NUM)

        self.handlerStdout = logging.StreamHandler(sys.stdout)
        self.handlerStdout.setLevel(logging.INFO)

        # self.handlerInfo.addFilter(_MyFilter(logging.INFO))
        # self.handlerDebug.addFilter(_MyFilter(logging.DEBUG))
        # self.handlerError.addFilter(_MyFilter(logging.ERROR))

        # create a logging format #%(asctime)s - %(name)s -
        formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
        self.handlerInfo.setFormatter(formatter)
        self.handlerDebug.setFormatter(formatter)
        self.handlerError.setFormatter(formatter)
        self.handlerStdout.setFormatter(formatter)
        self.handlerDebugDetails.setFormatter(formatter)

        self.logger.addHandler(self.handlerInfo)
        self.logger.addHandler(self.handlerDebug)
        self.logger.addHandler(self.handlerError)
        self.logger.addHandler(self.handlerStdout)
        self.logger.addHandler(self.handlerDebugDetails)

        self.setOfErrMsg: set = set()


    def close_logger(self):
        """
        Closes all file handlers
        """
        self.handlerInfo.close()
        self.handlerDebug.close()
        self.handlerError.close()
        self.handlerStdout.close()
        self.handlerDebugDetails.close()
        self.logger.removeHandler(self.handlerInfo)
        self.logger.removeHandler(self.handlerDebug)
        self.logger.removeHandler(self.handlerError)
        self.logger.removeHandler(self.handlerDebugDetails)
        self.logger.removeHandler(self.handlerStdout)


    def error(self, msg: str):
        """
        Passes the error msg to logging object if the error msg is new
        :param msg:
        """
        if msg not in self.setOfErrMsg:
            self.setOfErrMsg.add(msg)
            self.logger.error(msg)


    def debug_details(self, message, *args, **kws):
        """
        Pass a logging message that is below debug. We use it to debug what features
        were rewritten successfully or not by a particular transformer.
        We get a lot of these messages, thus we have two debug levels.
        :param message: your message
        :param args: additional params passed to logger
        :param kws: additional params passed to logger
        """
        self.logger._log(self.DEBUGDETAILS_LEVEL_NUM, message, args, **kws)