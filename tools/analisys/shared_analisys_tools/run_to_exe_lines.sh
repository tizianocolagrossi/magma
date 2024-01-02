#!/bin/bash -e

echo "hi"

# /input/ here there will be the crach input/s

##
# Pre-requirements:
# - FUZZER
# - PROGRAM
# - TARGET
# - IRUN
##

# echo "FUZZER  $FUZZER"
# echo "PROGRAM $PROGRAM"
# echo "TARGET  $TARGET"
# echo "IRUN    $IRUN"

PROGRAM_PATH=$(find /magma_out/ -name $PROGRAM)
echo "PROGRAM_PATH $PROGRAM_PATH"

crashes=(/input/*id:*) 

echo "$crashes"

/magma_analisys/extractor_lines.py $PROGRAM_PATH $crashes

# /bin/bash