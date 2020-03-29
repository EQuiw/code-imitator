#!/bin/bash
RED='\033[0;31m'
NC='\033[0m' # No Color

# activate your conda environment before executing this file, do not forget it #

# get parent directory of data directory where this file is located
SCRIPTPATH=$(dirname $(readlink -f "$0"))
AUTHORSHIP_EVASION=$( dirname $SCRIPTPATH )



SRC="${AUTHORSHIP_EVASION}/data/dataset_2017/dataset_2017_8_formatted/"
OUTPUT_DIR="${AUTHORSHIP_EVASION}/data/dataset_2017/dataset_2017_8_formatted_macrosremoved/"
LOG_FILE="${AUTHORSHIP_EVASION}/data/dataset_2017/log_file_macrosremoved.csv"

PY_CMD="python ${AUTHORSHIP_EVASION}/src/PyProject/dataset_preprocessing/remove_macros.py"

MAX_TIME=3000
MAX_JOBS=8

# Be careful, output dir should not be src, otherwise a call such as
#   clang-format file.cpp > file.cpp will yield an empty cpp file ;)
if [ "${SRC}" == "${OUTPUT_DIR}" ]; then
    echo "Src and output dir are the same. Will lead to empty files."
    exit 1
fi



echo -e "${RED}Let's start formatting all samples via python-tool to expand macros${NC}"

# create target dir's, skip first line that is the SRC itself.
find "${SRC}" -type d | tail -n+2 | parallel mkdir -p ${OUTPUT_DIR}{/}

# check that skipping does not lead to any error's.
nofilessrc=`(ls -l ${SRC} | wc -l)`
nofilestar=`(ls -l ${OUTPUT_DIR} | wc -l)`
echo "NoFiles: ${nofilessrc};${nofilestar}"
if [ "${nofilessrc}" -ne "${nofilestar}" ]; then
    echo "mismatch. error"
    exit 1
fi

# We call clang-format on each input file, pipe the output into a new file in output dir
for f in $(find "${SRC}" -type f -regex '\(.*c\|.*cpp\)')
 do 
	PARENT=$(basename $(dirname $f))
	AUTHOR=$(basename $f)
    ${PY_CMD} $f ${OUTPUT_DIR}${PARENT}/${AUTHOR} ${LOG_FILE}
    clang-format -i ${OUTPUT_DIR}${PARENT}/${AUTHOR}
 done




