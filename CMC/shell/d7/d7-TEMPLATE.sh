#!/bin/bash

# area 1) globals

SORT="sort"
DINOFILE="dinosaur.dat"

# area 2) function area

usage() {
    cat 1>&2 <<EOF
Usage: $(basename $0) <SORT_FUNCTIONS>

SORT_FUNCTIONS are:
    -g sort geographically, south to north
    -n sort by name, alphabetically
    -a sort by maximum possible age, oldest to youngest

Examples:

Sort south-north only:
$(basename $0) dinosaur.dat -g

Sort south-north, then sort by name:
$(basename $0) dinosaur.dat -g -n

Sort by name, and then south-north:
$(basename $0) dinosaur.dat -n -g

Sort by name, then south-north, then by age:
$(basename $0) dinosaur.dat -n -g -a

EOF
}

set_sort() {
    # write a function that takes in the flag (g, n, or a)
    # and modifies the SORT variable so that the correct
    # SORT_FUNCTION is applied
}

# area 3) handle parameters

# write a while loop to go through parameters
	# inside the loop...
	# write a case statement that
	# calls set_sort for whichever
	# flag is set in the parameters or
	# calls usage() if unknown flag

# do not remove, used for grading purposes
echo "$SORT"

# area 4) call the utility

cat $DINOFILE | $SORT -t $'\t' # note how we have to use an ANSI-C quoted char here for the tab
