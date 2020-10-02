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

set_regex(){
   local REGEXTYPE=$1
   local SORT=$2

   case $REGEXTYPE in
      n) REGEX="(^[a-zA-Z]+[0-9]+[a-zA-Z]+)" ;;
      l) REGEX="^[^a-z]*([a-z]+)[^a-z]*$" ;;
   esac

  local SORT=$1

  if [ $SORT != 's' ] ; then
    SORT="cat"
  fi

  if [ $SORT == 's' ] ; then
    SORT="sort"
  fi
}


# step 3) parameter parsing
P_TXTFILE=$1
P_SORT=$3
P_REGEXTYPE=$2

set_regex $P_REGEXTYPE $P_SORT

# step 4) call the utility

cat $P_TXTFILE | $SED "s/$REGEX/\1/p" | $SORT | head -n 5

