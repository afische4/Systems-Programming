#!/bin/bash
rm report.txt 
uptime >> report.txt
#python3 create_pswds.py

file=$1
while IFS= read line
do
  PSWD=$(echo $line | awk -F ';' '{print $1}')
  REGEX=$(echo $line | awk -F ';' '{print $2}')
  THRD=$(echo $line | awk -F ';' '{print $3}')
  python3 m2c.py -r $REGEX -t $THRD -e $PSWD
done <"$file"

cat report.txt
