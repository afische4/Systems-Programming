#!/bin/bash

# set parameter values
PASS=$1
MAX=$2
NLEN=$3
WLEN=$4
LENA=$5
LENB=$6

echo "top $MAX most-common passwords"

# a freebie! :-)
cat $PASS | sort | uniq -c | sort -r -h | head -n $MAX

echo ""
echo "top $MAX most-common number sequences of length $NLEN"

# your command here

echo ""
echo "top $MAX most-common words of length $WLEN"

# your command here

# calculate total (non-unique) occurrences of passwords matching letters-numbers-letters pattern
# set a variable called NUMLNL that counts the number of letters-numbers-letters matches
# remember the format VARIABLENAME=$(...)

echo ""
echo "top $MAX most-common of pattern letters-numbers-letters (out of $NUMLNL total)"

# your command here

echo ""
echo "number of total (non-unique) passwords that match pattern: my NUM XYZ"

# your command here

echo ""
echo "number of occurrences of number sequences of various lengths"
echo "length num_occur"

# use a for loop that iterates over a sequence
# then inside the loop, run a command to get the number of occurrences of
# number sequences of the length $i
# then print them out along with the index
for # rest of for loop
do
    NUMSEQ= # your command here
    echo "$i $NUMSEQ"
done
