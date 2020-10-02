#!/bin/bash

# Anna Fischer
# afische4@nd.edu
# 09.04.2020

# globals area

SORT="cat"
OUT="OFS=;"
PRINT="{print \$1, \$2, \$3}"
LOC=""
AWK='awk -v FS=; -v'
DATFILE="zipcodes.dat"

# functions area, starting with usage()

usage() {
    cat 1>&2 <<EOF
Usage: $(basename $0)

-h	This help message.
-s	Sort by zipcode, city, and/or state.
    z zipcose
    s state
    c city
-d	Set output delimiter
-l	Locate city by text.
-c	Data to display.

Available data:
a	Latitude
o	Longitude
t	Timezone offset from UTC
d	DST
g	Geolocation

Examples:

	Output sorted by state, then city, then zipcode.
	$0 -s scz

	Output sorted only by state.
	$0 -s s

	Output uses tabs instead of spaces.
	$0 -s s -d '\t'

	Display latitude and longitude with zipcodes.
	$0 -c ao

	Display timezone, longitude, then latitude.
	$0 -c toa

	Search for Rushville, sort by state/city/zip, delimit using tab.
	./zips.sh -s scz -c oa -d "\t" -l "Rushville"

EOF
    exit $1
}

#functions

set_sort() {
  local FLAG=$1
  SORT="sort"
    for i in $(seq 0 ${#FLAG}); do
      case ${FLAG:i:1} in 
          s)SORT="$SORT -k3,3 ";;
          z)SORT="$SORT -k1,1 ";;
          c)SORT="$SORT -k2,2 ";;
      esac
    done
   SORT="$SORT -t ;"
}
set_loc(){
  local CITY=$1
  while [ $# -gt 1 ]; do
    shift
    CITY="$CITY $1"
  done
  LOC="\$2~/$CITY/"
}

set_delim(){
 local SET=$1
 OUT="OFS=$SET"
}

set_display(){
  local DISP=$1
  DATA="print \$1, \$2, \$3"
    for i in $(seq 0 ${#DISP}); do
      case ${DISP:i:1} in 
          a)DATA="$DATA ,\$4";;
          o)DATA="$DATA ,\$5";;
          t)DATA="$DATA ,\$6";;
          d)DATA="$DATA ,\$7";;
          g)DATA="$DATA ,\$8";;
      esac
    done
    PRINT="{$DATA}"
}

# read parameters

while [ $# -gt 0 ]; do
	case $1 in
	  -h) usage 0;;
    -s) set_sort $2;; 
    -l) set_loc $2;;
    -d) set_delim $2;;
    -c) set_display $2;;
	   *) usage 1;;
	esac
  shift
  shift
done

# call the utilities
#echo "$SORT $AWK $OUT $LOC $PRINT"

cat $DATFILE | $SORT | $AWK "$OUT" "$LOC $PRINT"

# Whew! Thanks for working hard on this assignment.
#
# Here's an ASCII fish I thought was cute:
#
#                O  o
#           _\_   o
# >('>   \\/  o\ .
#        //\___=
#           ''
# I especially like the little fish behind the big one.
# 
# I put it here as a reminder of how simple things, like
# a couple greater-than signs and a paren, can have
# a big meaning.  As you gain knowledge of this material,
# you will throw off the yoke put on you by most
# operating systems like Android, iOS, Windows, and yes
# even MacOS.  Those OSes are designed to keep you from
# making mistakes, but also to keep you contained.  They
# have you right where they want you, in your cell.
#
# Learn well, take the power into your own hands, and
# be free.
#
#            - cmc

