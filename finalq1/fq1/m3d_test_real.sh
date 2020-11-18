mkdir -p wrk

WORTH=20
POINTS=0
SECONDS=0
MAXSECONDS=900

echo "Testing ..."

printf "   %-30s ... " "message 0, 4 points"
mkdir -p messages
rm -rf messages/msg_*.txt
make clean > /dev/null
make > /dev/null
LD_LIBRARY_PATH=. ./m3d > /dev/null
diff messages/msg_0.txt realref/msg_0.txt
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+4
fi

printf "   %-30s ... " "message 1, 4 points"
diff messages/msg_1.txt realref/msg_1.txt
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+4
fi

printf "   %-30s ... " "message 2, 4 points"
diff messages/msg_2.txt realref/msg_2.txt
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+4
fi

printf "   %-30s ... " "message 3, 4 points"
diff messages/msg_3.txt realref/msg_3.txt
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+4
fi

printf "   %-30s ... " "message 4, 4 points"
diff messages/msg_4.txt realref/msg_4.txt
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+4
fi

echo "Time: $SECONDS seconds (max allowed=$MAXSECONDS)"

if [ $SECONDS -gt $MAXSECONDS ]; then
	echo "  WARNING: Half credit due to time overage."
	let POINTS=$POINTS-$WORTH/2
fi

echo "Score: $POINTS / $WORTH"
