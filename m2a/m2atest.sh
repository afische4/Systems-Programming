mkdir -p wrk

SCRIPT=$1
DINO_SCRIPT=$2
MAP_SCRIPT=$3
WORTH=6
POINTS=0
SECONDS=0
MAXSECONDS=60

echo "Testing m2a.py, mapmaker.py, dinodata.py ..."
python3 m2a.py -z 46556 -d 1
python3 m2a.py -z 91210 -d 2
mv 46* maptest1.png
mv 91* maptest2.png
coverage3 run $T_SCRIPT
coverage3 report

# test 23456 dist 5
printf "   %-30s ... " "Sample 1, 1 points"
python3 $SCRIPT -z 23456 -d 5 > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
  echo "Failure"
else
  echo "Success"
  let POINTS=$POINTS+1
fi

# test 62681 dist 2
printf "   %-30s ... " "Sample 2, 1 points"
python3 $SCRIPT -z 62681 -d 2 > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
  let POINTS=$POINTS+1
fi

# test 66208 dist 20
printf "   %-30s ... " "Sample 3, 2 points"
python3 $SCRIPT -z 66208 -d 20 > wrk/3
diff wrk/3 ref/3
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
  let POINTS=$POINTS+2
fi

# test 91210 dist 1
printf "   %-30s ... " "Sample 4, 2 points"
python3 $SCRIPT -z 91210 -d 1 > wrk/4
diff wrk/4 ref/4
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
  let POINTS=$POINTS+2
fi

echo "Time: $SECONDS seconds (max allowed=$MAXSECONDS)"

if [ $SECONDS -gt $MAXSECONDS ]; then
  echo "  WARNING: Half credit due to time overage."
  let POINTS=$POINTS-$WORTH/2
fi

echo "Score: $POINTS / $WORTH"


rm -r wrk
rm 2* 9* 6*
