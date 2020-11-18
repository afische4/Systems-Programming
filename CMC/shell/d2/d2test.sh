#!/bin/bash

NETID=$1
HIDDENDIR=$2
DIRPERM=$3
FILEPERM=$4

echo "Testing $NETID ..."

printf "   %-30s ... " "check 0"
if [ ! -f "/escnfs/courses/fa20-cse-20289.01/dropbox/$NETID/d2.md" ]; then
        echo "Failure"
else
        echo "Success"
fi

printf "   %-30s ... " "check 1"
if [ ! -d "/escnfs/home/cmcmill2/public/d2/$NETID" ]; then
	echo "Failure"
else
	echo "Success"
fi

printf "   %-30s ... " "check 2"
if [ $(stat -c "%a" "/escnfs/home/cmcmill2/public/d2/$NETID") != "$DIRPERM" ]; then
        echo "Failure"
else
        echo "Success"
fi

printf "   %-30s ... " "check 3"
if [ ! -f "/escnfs/home/cmcmill2/public/d2/$NETID/asciiart.txt" ]; then
        echo "Failure"
else
        echo "Success"
fi

printf "   %-30s ... " "check 4"
if [ $(stat -c "%a" "/escnfs/home/cmcmill2/public/d2/$NETID/asciiart.txt") != "$FILEPERM" ]; then
        echo "Failure"
else
        echo "Success"
fi

printf "   %-30s ... " "check 6a"
if [ ! -f "/escnfs/home/cmcmill2/public/d2/$HIDDENDIR/$NETID.txt" ]; then
        echo "Failure"
else
        echo "Success"
fi

printf "   %-30s ... " "check 6b"
if [ ! -L "/escnfs/home/cmcmill2/public/d2/$HIDDENDIR/$NETID.txt" ]; then
        echo "Failure"
else
        echo "Success"
fi

