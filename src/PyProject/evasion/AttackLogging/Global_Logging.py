# import multiprocessing
import logging
# from logging.handlers import QueueHandler, QueueListener
import os


##
## this logger logs the attack progress over
## all attack instances, not each individual evasion attack
##



def logger_sequential_init(logfilepath, logfile_name: str = 'info_all.log'):
    if not os.path.exists(logfilepath):
        os.makedirs(logfilepath)

    handler = logging.FileHandler(os.path.join(logfilepath, logfile_name), mode="w+")
    handler.setFormatter(logging.Formatter("%(levelname)s: %(asctime)s - %(process)s - %(message)s"))

    logger = logging.getLogger("parallel_logger")
    logger.setLevel(logging.DEBUG)
    # add the handler to the logger so records from this process are handled
    logger.addHandler(handler)

    return logger


def close_logger_sequential(logger):
    handlers = logger.handlers[:]
    for handler in handlers:
        handler.close()
        logger.removeHandler(handler)

