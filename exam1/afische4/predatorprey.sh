#!/bin/bash

NUM_PREY=0
NUM_PRED=0
DATFILE="dinosaur.dat"

usage(){
cat 1>&2 <<EOF
Usage: $(basename $0) -y <PREY> -r <PREDATOR>

PREY is a single prey animal.
PREDATOR is a single predator animal.

If -s is not specified, search the entire file regardless of country or location.  If -s is not specified first, the behavior is undefined.

Note that -y and -r may be specified multiple times.  The number of each predator and prey should be added.

This script does not consider time.  It only counts total occurrences of an animal in the data file that occur within the specified state.

The search is case insensitive.

Ratio of hadrosaur animals to tyrannosaur:
    predatorprey.sh -y hadrosaur -r tyrannosaur

Ratio of stegasaur animals to allosaur:
    predatorprey.sh -y stegasaur -r allosaur
    
Ratio of hadrosaur and ceratop animals to tyrannosaur:
    predatorprey.sh -y hadrosaur -y ceratop -r tyrannosaur

Ratio of hadrosaur and ceratop animals to tyrannosaur, raptor, and allosaur:
    predatorprey.sh -y hadrosaur -y ceratop -r tyrannosaur -r raptor -r allosaur

EOF
exit $1
}

set_prey(){
local PREY=$1
NUM_PREY=$(cat $DATFILE | awk -F '\t' -v IGNORECASE=1 "\$6~/$PREY/ {print \$6}" | wc -l)
}
set_pred(){
local PRED=$1
NUM_PRED=$(cat $DATFILE | awk -F '\t' -v IGNORECASE=1 "\$6~/$PRED/ {print \$6}" | wc -l)
}

while [ $# -gt 0 ]; do
  case $1 in
      -h) usage 0;;
      -y) shift; set_prey $1;; 
      -r) shift; set_pred $1;;
       *) usage 1;;
   esac
   shift
   done
# do not change these echo statements, I use them for grading
echo "number of prey: $NUM_PREY"
echo "number of predator: $NUM_PRED"

YRRAT=$(echo "$NUM_PREY/$NUM_PRED" | bc -l)
# calculate ratio

echo "ratio: $YRRAT"


#I would keep playing around with teh prey and predator numbers until I got it to work right I know it is printing the whole column but
