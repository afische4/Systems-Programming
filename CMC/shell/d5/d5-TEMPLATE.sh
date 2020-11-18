#!/bin/bash

# step 1) set globals
SED="sed -nE"

# step 2) function area

usage(){
    cat 1>&2 <<EOF
Usage: $(basename $0) <FILENAME> <REGEX_TYPE> <TO_SORT>

FILENAME    The name of the file with the password data.

REGEX_TYPE  n: letters-numbers-letters pattern
            l: letters-only pattern

SORT        s: sort the output
EOF
    exit $1
}

# write ONE function for each program you're going to call
# you need to call sed and sort... so that would mean
# one function for sed and one function for sort

# step 3) handle parameter values

P_PASS=$1
P_REGEX=$2
P_SORT=$3

# write an if statement to check if the number of parameters >= 2
# if yes, then call your set/utility functions
# if no, then call the usage function with the argument 1

usage 0 # in this template we just call usage with argument 0

# as an aside, notice that the argument sent to usage() is
# used as the argument for exit()
# this is the return code of the program
# 0 = successful
# 1 = error
# notice that in our if statement we want to call it with
# argument=1, because it is an "error" if someone calls our
# script without enough parameters

# step 4) finally, call the command(s)

# pipe the output to sed and then to sort, with different
# parameters based on what the set/utility functions did

# cat $P_PASS | PIPE TO SOMETHING... 
