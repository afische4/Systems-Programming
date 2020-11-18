
VAR=$2

for i in $(seq 0 ${#VAR}); do
	case ${VAR:i:1} in
		q) echo "q" ;;
		e) echo "e"  ;;
	esac
done 

