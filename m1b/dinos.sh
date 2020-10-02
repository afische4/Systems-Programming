#!/bin/bash


DATFILE="dinosaur.dat"

DINOA=$1
DINOB=$2
# Do some initial filtering here with awk
DINOAF=$(cat $DATFILE | awk -F '\t' -v IGNORECASE=1 '$6~/'$DINOA'/ {print $16, $17}' | sort | uniq -c | sed -nE "s/^\s*(.*)/\1/p" | awk -v OFS=';' '{print $1, $2, $3}')
DINOBF=$(cat $DATFILE | awk -F '\t' -v IGNORECASE=1 '$6~/'$DINOB'/ {print $16, $17}' | sort | uniq -c | sed -nE "s/^\s*(.*)/\1/p" | awk -v OFS=';' '{print $1, $2, $3}')

overlap_ma(){
local MNA=$1
local MXA=$2
local MNB=$3
local MXB=$4
#do math
COMP1=$(echo "$MNA < $MXB" | bc -l)
COMP2=$(echo "$MNB < $MXA" | bc -l)
if [ $COMP1 -eq 1 ] && [ $COMP2 -eq 1 ]; then
  YN=1
else
  YN=0
fi
}

YES_COUNT=0
NO_COUNT=0

for i in $DINOAF; do
  NUM_A=$(echo "$i" | awk -F ';' '{print $1}')
  MAX_A=$(echo "$i" | awk -F ';' '{print $2}')
  MIN_A=$(echo "$i" | awk -F ';' '{print $3}')
  for j in $DINOBF; do
    NUM_B=$(echo "$j" | awk -F ';' '{print $1}')
    MAX_B=$(echo "$j" | awk -F ';' '{print $2}')
    MIN_B=$(echo "$j" | awk -F ';' '{print $3}')
    overlap_ma $MIN_A $MAX_A $MIN_B $MAX_B
    if [ $YN -eq 1 ]; then
      YES_COUNT=$(echo "$YES_COUNT + $NUM_A + $NUM_B" | bc -l)
    else
      NO_COUNT=$(echo "$NO_COUNT + $NUM_A + $NUM_B" | bc -l)
    fi
 done
done


# Use bc to calculate $OVERLAP
TEMP=$(echo "$YES_COUNT + $NO_COUNT" | bc -l)
OVERLAP=$(echo "scale=2; $YES_COUNT / $TEMP * 100"  | bc -l)
OVERLAP=$(echo "scale=0; $OVERLAP / 1" | bc -l)

echo "dinoverlap between $DINOA and $DINOB is $OVERLAP%"

# Here's your ASCII art for this assignment!
#                __
#               / _)
#      _.----._/ /
#     /         /
#  __/ (  | (  |
# /__.-'|_|--|_|
#
# Imagine entering a time machine and setting the dial
# for -100 million years.  The door opens and humid air
# enters the machine.  Palm trees sway and a sauropod
# turns its long neck slowly toward you.  In the
# distance, a volcano emits steam and smoke.  A raptor
# suddenly leaps and runs toward you!  You look at the
# fuel gauge: if you jump again, you can make it home,
# but never return to the land of the dinosaurs.  Out
# of the corner of your eye you glance the emergency
# blaster pack. Fully charged, but locked behind the
# safety glass.  You just might have time to grab it,
# if you run now, right now.
#
# Do you punch JUMP or RUN?
# RUN, grab the blaster pack, then jump to the future :o)

