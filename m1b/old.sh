#!/bin/bash

OFS=";"
SORT="cat"

DATFILE="dinosaur.dat"

DINOA=$1
DINOB=$2

# Do some initial filtering here with awk
DINOAF=$(cat $DATFILE | awk -F '\t' -v IGNORECASE=1 '$6~/^'$DINOA'/ {print $16, $17}' | uniq -c | sed -nE "s/^\s*(.*)/\1/p")
DINOBF=$(cat $DATFILE | awk -F '\t' -v IGNORECASE=1 '$6~/^'$DINOB'/ {print $16, $17}' | uniq -c | sed -nE "s/^\s*(.*)/\1/p")
#echo "$DINOAF $DINOBF"
#num_x is the number of unique dinox occurances in the file
NUMA=$(cat $DATFILE | awk -F '\t' -v IGNORECASE=1 '$6~/^'$DINOA'/ {print $16, $17}' | uniq -c | wc -l)
NUMB=$(cat $DATFILE | awk -F '\t' -v IGNORECASE=1 '$6~/^'$DINOB'/ {print $16, $17}' | uniq -c | wc -l)
NUMA=$(echo "$NUMA - 1" | bc -l)
NUMB=$(echo "$NUMB - 1" | bc -l)
#echo "number of uniq A and B: $NUMA $NUMB"
A_MAX=$(echo "$DINOAF" | awk '{print $2}')
A_MIN=$(echo "$DINOAF" | awk '{print $3}')
B_MAX=$(echo "$DINOBF" | awk '{print $2}')
B_MIN=$(echo "$DINOBF" | awk '{print $3}')
U_DINOA=$(echo "$DINOAF" | awk '{print $1}')
U_DINOB=$(echo "$DINOBF" | awk '{print $1}')
#what if I grabbed the entire line of 3 pieces of data and then compared like $2 of one to $2 of the other
#or set variables equal to these but renew each time, so just one loop to make the array and then
overlap_ma(){
#do simple math
local MNA=$1
local MXA=$2
local MNB=$3
local MXB=$4
#echo "$MNA $MXA $MNB $MXB"
#echo "comparisons:"
#COMP1=$(echo "$MNA >= $MNB" | bc -l)
COMP2=$(echo "$MNA < $MXB" | bc -l)
#COMP3=$(echo "$MNA <= $MNB" | bc -l)
COMP4=$(echo "$MXA > $MNB" | bc -l)
#echo "$COMP1 $COMP2 $COMP3 $COMP4"
if [ $COMP2 -eq 1 ] && [ $COMP4 -eq 1 ]; then
    YN=1
#elif [ $COMP3 -eq 1 ] && [ $COMP4 -eq 1 ]; then
    #YN=1
else
    YN=0
fi
#echo "YN = $YN"

}

YES_COUNT=0
NO_COUNT=0
UA=()
UB=()
MAXA=()
MAXB=()
MINA=()
MINB=()

x=0
for i in $U_DINOA; do
  UA[$x]=$i
  x=$(echo $x + 1 | bc)
done

x=0
for i in $U_DINOB; do
  UB[$x]=$i
  x=$(echo $x + 1 | bc)
done

x=0
for i in $A_MAX; do
  MAXA[$x]=$i
  x=$(echo $x + 1 | bc)
done
x=0
for i in $A_MIN; do
  MINA[$x]=$i
  x=$(echo $x + 1 | bc)
done
x=0
for i in $B_MAX; do
  MAXB[$x]=$i
  x=$(echo $x + 1 | bc)
done
x=0
for i in $B_MIN; do
  MINB[$x]=$i
  x=$(echo $x + 1 | bc)
done
#echo "${UB[*]}"
#echo "${UA[*]}"
#echo "${MINA[*]}"
#echo "${MAXA[*]}"
#echo "${MINB[*]}"
#echo "${MAXB[*]}"
YES_COUNT=0
NO_COUNT=0
for i in $(seq 0 $NUMA); do
  U_A=$(echo "${UA[$i]}")
  AMIN=$(echo "${MINA[$i]}")
  AMAX=$(echo "${MAXA[$i]}") 
  for j in $(seq 0 $NUMB); do
    U_B=$(echo "${UB[$j]}")
    BMIN=$(echo "${MINB[$j]}")
    BMAX=$(echo "${MAXB[$j]}") 
    #echo "$U_A $AMIN $AMAX $U_B $BMIN $BMAX"
    overlap_ma $AMIN $AMAX $BMIN $BMAX
    if [ $YN -eq 1 ]; then
      YES_COUNT=$(echo "$YES_COUNT + $U_A + $U_B" | bc -l)
    else
      NO_COUNT=$(echo "$NO_COUNT + $U_A + $U_B" | bc -l)
    fi
 done
done



# Recall the pseudocode from README.md:
#
#For each *unique* Allosaurus occurrence:
#      NUM_ALLOSAUR = number of times this Allosaurus timespan occurs
#      For each *unique* Stegosaurus occurrence:
#          NUM_STEGOSAUR = number of times this Stego timespan occurs
#          YN = overlap_ma(dinoA_maxma, dinoA_minma, dinoB_maxma, dinoB_minma)
#          if YN equals 1
#              yes_count += NUM_ALLOSAUR + NUM_STEGOSAUR
#          else
#              no_count += NUM_ALLOSAUR + NUM_STEGOSAUR

# Use bc to calculate $OVERLAP
#echo "$YES_COUNT $NO_COUNT"
TEMP=$(echo "$YES_COUNT + $NO_COUNT" | bc -l) 
OVERLAP=$(echo "$YES_COUNT / $TEMP * 100"  | bc -l)
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
#

