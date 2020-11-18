#!/bin/bash

OFS=";"
SORT="cat"

DATFILE="dinosaur.dat"

DINOA=$1
DINOB=$2

# Do some initial filtering here with awk

overlap_ma(){
}

YES_COUNT=0
NO_COUNT=0

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

