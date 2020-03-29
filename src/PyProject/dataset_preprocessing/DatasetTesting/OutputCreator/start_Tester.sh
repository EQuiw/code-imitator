#!/bin/bash

PYPATH="$(pwd)"
CORES=8

# Short check to assure that we start the script in PyProject directory
if [ ${PYPATH##*/} != "PyProject" ];
then
    echo "go to PyProject directory and start the script there"
    exit 1
fi

# Now start the attack for one or more chosen problems

parallel -j $CORES --delay 5 PYTHONPATH=${PYPATH} python dataset_preprocessing/DatasetTesting/OutputCreator/Tester.py {}\
 ::: 3264486_5736519012712448  8294486_5654117850546176  3264486_5654742835396608\
  5304486_5760761888505856  3264486_5633382285312000  5304486_5697460110360576\
  8294486_5681755159789568  8294486_5630967708385280 >> output_outputcreator.log

echo "created output_outputcreator.log file"