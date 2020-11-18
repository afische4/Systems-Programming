#!/usr/bin/env python3

def ackermann(m=3, n=2):
	print(f'A({m}, {n})')
	if(m == 0):
		return(n+1)
	elif(m > 0 and n == 0):
		return(ackermann(m-1, 1))
	elif(m > 0 and n > 0):
		return(ackermann(m-1, ackermann(m, n-1)))

ackermann(2, 4)

