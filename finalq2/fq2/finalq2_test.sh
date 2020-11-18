mkdir -p wrk

SCRIPT=$1
WORTH=6
POINTS=0
SECONDS=0

echo "Testing $SCRIPT ..."

printf "   %-30s ... " "first record, 1 point"
python3 fq2.py > wrk/2
head -n 1 wrk/2 > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "all records, 5 points"
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+5
fi

echo "Score: $POINTS / $WORTH"
