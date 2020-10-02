#!/bin/bash

# step 1) set up globals

SED="sed -nE"

# step 2) function area

usage(){
    cat 1>&2 <<EOF
Usage: $(basename $0) <FILENAME> <FORMAT> <REGEX_TYPE> <NOUN>

FILENAME    The name of the file with the password data.

FORMATS     u: print in uppercase
            l: print in lowercase

OPERATIONS  a: extract adjectives (must also specify noun)
            n: extract names

EOF
    exit $1
}

set_regex(){
    local REGEXTYPE=$1
    local NOUN=$2
    
    if [ $REGEXTYPE != 'a' ] && [ $REGEXTYPE != 'n' ] ; then
        echo "invalid regex type"
        exit 1
    fi
    
    case $REGEXTYPE in
        a) REGEX=".*\s(a|the)\s+([a-zA-Z]+)\s+($NOUN).*"; LOC="\2" ;;
        n) REGEX="^\s+\b([A-Z]{3,16})\b\..*"; LOC="\1" ;;
    esac
}

# step 3) parameter parsing
P_TXTFILE=$1
P_FORM=$2
P_REGEXTYPE=$3
P_NOUN=$4

FORM="\L"

set_regex $P_REGEXTYPE $P_NOUN

# step 4) call the utility

cat $P_TXTFILE | $SED "s/$REGEX/$FORM$LOC/p"

