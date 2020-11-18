mkdir -p wrk

SCRIPT=$1
WORTH=4
POINTS=0
SECONDS=0
MAXSECONDS=4

echo "Testing $SCRIPT ..."

printf "   %-30s ... " "Sample 1, 5 points"
gcc -fPIC -shared littlelib.c -o liblittlelib.so
gcc -Wall -o d17 d17.c -llittlelib -L.
LD_LIBRARY_PATH=. ./d17 > wrk/1
diff wrk/1 ref/1
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
