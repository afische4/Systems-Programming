#!/bin/bash
FILE=$1
NOUN=$2
OUT=$(cat $FILE | sed -nE "s/^.* (the|a) ([a-zA-Z]{2,}) $NOUN.*$/\2/p" | sort | uniq) 
echo "$OUT"
