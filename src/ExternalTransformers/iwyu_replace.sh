#!/bin/bash

if [ $# -ne 7 ];
    then
      echo "usage: $0 <source-file> <iwyu-path> <args> <args> <args> <args> <args>"
      exit 1
    fi


SOURCE_FILE=$1
IWYU=$2
ARG1=$3
ARG2=$4
ARG3=$5
ARG4=$6
ARG5=$7

cp ${SOURCE_FILE} "${SOURCE_FILE}_mod.cpp"

"${IWYU}/include-what-you-use" "${SOURCE_FILE}_mod.cpp" $ARG1 $ARG2 $ARG3 $ARG4 $ARG5 2> "${SOURCE_FILE}_iwyu_out2"

python2 ${IWYU}/../fix_includes.py < "${SOURCE_FILE}_iwyu_out2" > "${SOURCE_FILE}_iwyu_out"

cat "${SOURCE_FILE}_mod.cpp"
rm "${SOURCE_FILE}_mod.cpp"
rm "${SOURCE_FILE}_iwyu_out"
rm "${SOURCE_FILE}_iwyu_out2"
