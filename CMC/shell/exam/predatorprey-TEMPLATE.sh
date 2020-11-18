#!/bin/bash

NUM_PREY=0
NUM_PRED=0

usage(){
cat 1>&2 <<EOF
Usage: $(basename $0) -y <PREY> -r <PREDATOR>

PREY is a single prey animal.
PREDATOR is a single predator animal.

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

# do not change these echo statements, I use them for grading
echo "number of prey: $NUM_PREY"
echo "number of predator: $NUM_PRED"

YRRAT= # calculate ratio

echo "ratio: $YRRAT"
