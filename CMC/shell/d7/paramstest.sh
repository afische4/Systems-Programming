
usage(){
	echo "qqqqqqq"
	exit $1
}


while [ $# -gt 0 ]; do
	
	case $1 in
		-h) usage 0 ;;
		-g) echo "mario" ;;
		-p) shift; echo "player: $1" ;;
		*) echo $1 ;;
	esac

	shift
done


