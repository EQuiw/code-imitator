#!/bin/bash

PYPATH="$(pwd)"
CORES=1

# Short check to assure that we start the script in PyProject directory
if [ ${PYPATH##*/} != "PyProject" ];
then
    echo "go to PyProject directory and start the script there"
    exit 1
fi

# Now start the attack for one or more chosen problems

OUTPUT_FILE0="run_train_models_rnn_parallel0.log"
if [ -f OUTPUT_FILE0 ] ; then
    rm OUTPUT_FILE0
fi
OUTPUT_FILE1="run_train_models_rnn_parallel1.log"
if [ -f OUTPUT_FILE1 ] ; then
    rm OUTPUT_FILE1
fi
OUTPUT_FILE2="run_train_models_rnn_parallel2.log"
if [ -f OUTPUT_FILE2 ] ; then
    rm OUTPUT_FILE2
fi

parallel -j $CORES  PYTHONPATH=${PYPATH} python evaluations/learning/rnn_css/train_models_rnn_parallel.py {} 0 \
 ::: 3264486_5736519012712448 \
     8294486_5654117850546176 \
     3264486_5654742835396608 \
     >> $OUTPUT_FILE0 &

sleep 3
parallel -j $CORES  PYTHONPATH=${PYPATH} python evaluations/learning/rnn_css/train_models_rnn_parallel.py {} 1 \
 ::: 5304486_5760761888505856 \
     3264486_5633382285312000 \
     5304486_5697460110360576 \
     >> $OUTPUT_FILE1 &

sleep 3
parallel -j $CORES  PYTHONPATH=${PYPATH} python evaluations/learning/rnn_css/train_models_rnn_parallel.py {} 2 \
 ::: 8294486_5681755159789568 \
     8294486_5630967708385280 \
     >> $OUTPUT_FILE2 &

