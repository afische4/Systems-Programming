#!/bin/bash
YES_COUNT=115
NO_COUNT=89
TEMP=$(echo "$YES_COUNT + $NO_COUNT" | bc -l) 
OVERLAP=$(echo "scale=2; $YES_COUNT / $TEMP * 100"  | bc -l)
OVERLAP=$(echo "scale=0; $OVERLAP / 1" | bc -l)
echo "dinoverlap between poop and fart is $OVERLAP%"


