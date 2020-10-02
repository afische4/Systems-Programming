#!/bin/bash

echo "$0"

SEQSTART=$1
SEQEND=$2


for i in $(seq $SEQSTART $SEQEND)
do
	echo "$i"
done


