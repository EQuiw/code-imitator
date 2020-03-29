#!/bin/bash
RED='\033[0;31m'
NC='\033[0m' # No Color

# * * * SET UP PATHES HERE * * *
# SET UP THE PATH TO JAVA BASELINE JAR or use environment variables 
CMD_DIR_NAIVEBASELINE=${CMD_DIR_NAIVEBASELINEJAR} #; exit # remove exit then





# get parent directory of data directory where this file is located
SCRIPTPATH=$(dirname $(readlink -f "$0"))
AUTHORSHIP_EVASION=$( dirname $SCRIPTPATH )
echo -e "${RED}Start extracting features${NC}"

### Now do feature extraction

SRC="${AUTHORSHIP_EVASION}/data/dataset_2017/dataset_2017_8_formatted_macrosremoved/"
OUTPUT_DIR="${AUTHORSHIP_EVASION}/data/dataset_2017/libtoolingfeatures_2017_8_formatted_macrosremoved/"
mkdir -p $OUTPUT_DIR


CMD_DIR="${AUTHORSHIP_EVASION}/src/LibToolingAST/cmake-build-release/feature_extraction_single/"
CMD_DIR_LEXEMS="${AUTHORSHIP_EVASION}/src/LibToolingAST/cmake-build-release/feature_extraction/"
CLANG_LIB=$( llvm-config --libdir )
COMPILER_FLAG="-w -std=c++11 -ferror-limit=1 -I${CLANG_LIB}/clang/5.0.0/include/ -include${AUTHORSHIP_EVASION}/src/LibToolingAST/ourerrors.h"


MAX_TIME=3000
MAX_JOBS=8


function make_pause {
# print * 90x
s=$(printf "%-90s" "*")
echo -e "${RED} ${s// /*} ${NC}"
# ask user to proceed
read -p "Press enter to continue"
}



# I. Get all features
echo -e "${RED}EXTRACT FEATURES...${NC}"
TOOL="feature_extraction_single"
OPTIONS="-ast_node_bigram=True -ast_node_types=True -ast_node_types_avg_dep=True -max_depth_ast_node=True -code_in_ast_leaves=True -code_in_ast_leaves_avg_dep=True -lexical_features=True"
find "${SRC}/" -type f -regex '\(.*c\|.*cpp\)' | parallel --bar --timeout ${MAX_TIME} -j ${MAX_JOBS}\
    "${CMD_DIR}${TOOL}" {} ${OPTIONS} -- ${COMPILER_FLAG} > ${OUTPUT_DIR}/"features_temp.dat"

#make_pause

# II. Split features to invidual files
echo -e "${RED}SPLIT FEATURES TO INDIVIDUAL FILES...${NC}"

# fct takes output file name, greps for it in feature extraction output, removes it from output and pipes filtered lines into output file:
function split { # takes one parameter
	PATTERN="$1 ::--::"
	cat ${OUTPUT_DIR}/"features_temp.dat" | grep "${PATTERN}" | sed "s/^\(${PATTERN}\)//" > ${OUTPUT_DIR}/$1

    # sort in-place with -o
    sort -o ${OUTPUT_DIR}/$1 ${OUTPUT_DIR}/$1
}  


PAT="ast_node_types.dat"
split $PAT

PAT="ast_node_types_avg_dep.dat"
split $PAT

PAT="max_depth_ast_node.dat"
split $PAT

PAT="ast_node_bigram.dat"
split $PAT

PAT="code_in_ast_leaves.dat"
split $PAT

PAT="code_in_ast_leaves_avg_dep.dat"
split $PAT

PAT="lexical_features.dat"
split $PAT

rm ${OUTPUT_DIR}/"features_temp.dat"

#make_pause

# III. Extract lexems
echo -e "${RED}NEXT, GET LEXEMS...${NC}"
find "${SRC}/" -type f -regex '\(.*c\|.*cpp\)' | parallel --bar --timeout ${MAX_TIME} -j ${MAX_JOBS}\
    "${CMD_DIR_LEXEMS}get_lexems_features" {} -- ${COMPILER_FLAG} > ${OUTPUT_DIR}/"lexems_features.dat"

sort -o ${OUTPUT_DIR}/"lexems_features.dat" ${OUTPUT_DIR}/"lexems_features.dat"

make_pause

# IV. Extract lexical and layout features via the Java Implementation
echo -e "${RED}FINALLY, GET LEXICAL - LAYOUT FEATURES FROM USENIX' PAPER JAVA IMPLEMENTATION...${NC}"

java -jar ${CMD_DIR_NAIVEBASELINE} ${SRC} ${OUTPUT_DIR}/"lexical_features.arff"






