mkdir -p wrk

SCRIPT=$1
WORTH=20
POINTS=0
SECONDS=0
MAXSECONDS=120

echo "Testing $SCRIPT ..."

# test single predator and prey
printf "   %-30s ... " "Sample 1, 5 points"
./$SCRIPT -y hadrosaur -r tyrannosaur > wrk/14a
diff wrk/14a ref/14a
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+5
fi

# test single predator and prey
printf "   %-30s ... " "Sample 2, 5 points"
./$SCRIPT -y stegosaur -r allosaur > wrk/14b
diff wrk/14b ref/14b
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+5
fi

# test multiple prey, single predator
printf "   %-30s ... " "Sample 3, 5 points"
./$SCRIPT -y hadrosaur -y ceratop -r tyrannosaur > wrk/14c
diff wrk/14c ref/14c
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+5
fi

# test multiple prey, multiple predator, any order
printf "   %-30s ... " "Sample 4, 5 points"
./$SCRIPT -y hadrosaur -r tyrannosaur -r raptor -y ceratop -r allosaur > wrk/14d
diff wrk/14d ref/14d
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+5
fi

echo "Time: $SECONDS seconds (max allowed=$MAXSECONDS)"

if [ $SECONDS -gt $MAXSECONDS ]; then
	echo "  WARNING: Half credit due to time overage."
	let POINTS=$POINTS-$WORTH/2
fi

echo "Score: $POINTS / $WORTH"

echo
echo "NOTE 1: I will heartlessly lop half credit if code not in proper structure."
echo "        By proper structure, I mean the 4-section design we discussed in class."
echo "NOTE 2: I will grade these by hand.  If your code fails to past the test"
echo "        for a very small reason, I will use my judgement to assign points."
