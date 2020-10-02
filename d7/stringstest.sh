#!/bin/bash
VAR=$1

for i in $(seq 0 ${#VAR}); do
	case ${VAR:i:1} in
		h) echo "${VAR:i:1}" ;;
		e) echo "${VAR:i:1}" ;;
		l) echo "${VAR:i:1}" ;;
		l) echo "${VAR:i:1}" ;;
		o) echo "${VAR:i:1}" ;;
	esac
done 

