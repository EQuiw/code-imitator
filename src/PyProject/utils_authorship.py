import numpy as np
import scipy.sparse
import typing
import os


def boolstr_to_floatstr(v: str) -> str:
    if v.lower() == 'true':
        return '1'
    elif v.lower() == 'false':
        return '0'
    else:
        return v


def sortmatrix(matrix1: scipy.sparse.csr_matrix, matrix1ids: np.ndarray, matrix1authors: np.ndarray = None)\
        -> typing.Tuple[scipy.sparse.csr_matrix, np.ndarray, np.ndarray]:
    """
    Sort matrix1 csr matrix and matrix1authors numpy array w.r.t. to matrix1ids input.
    TODO so far not really efficient. rewrite it..
    :param matrix1: the scipy matrix
    :param matrix1ids: the keys for sort
    :param matrix1authors: can be None
    :return: newmatrixsparse, newauthors, newindex
    """

    # convert input matrix from csr sparse to numpy so that assigment in for loop is possible
    matrix1 = matrix1.toarray()
    # sort, define new variables and do assignment
    newindex = np.sort(matrix1ids)
    newmatrix = np.zeros(matrix1.shape, dtype=np.float32)
    newauthors = np.copy(matrix1authors)

    for i in range(matrix1.shape[0]):
        matchix = np.where(newindex[i] == matrix1ids)[0][0]
        newmatrix[i, :] = matrix1[matchix, :]
        if matrix1authors is not None:
            newauthors[i] = matrix1authors[matchix]

    newmatrixsparse = scipy.sparse.csr_matrix(newmatrix, dtype=np.float32)

    return newmatrixsparse, newindex, newauthors


def create_unique_file_dir_with_suffix(parent_dir: str, file_or_dir: str) -> str:
    """
    Creates a unique file or directory name in parent_dir. It creates a number as suffix,
    and increments it until file_or_dir + suffix does not exist in parent_dir.
    Suffix goes only to 10000, otherwise you may use the wrong function.
    :param parent_dir: the parent directory
    :param file_or_dir: can be a file or directory name. Here, it does not matter.
    """

    for i in range(0, 10000):
        file_or_dir_unique = file_or_dir + "_" + str(i)
        if not os.path.exists(os.path.join(parent_dir, file_or_dir_unique)):
            return file_or_dir_unique

    raise Exception("Could not find a suitable suffix for a unique file or directory name")