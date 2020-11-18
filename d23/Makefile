#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for d23
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -Wall -lm 
d23Objs := d23.o libgeodist.o libdinos.o

d23: $(d23Objs)
	$(CC) $(CFLAGS) -o d23 $(d23Objs) 

d23.o: d23.c libgeodist.h libdinos.h
	$(CC) $(CFLAGS) -c d23.c 

libgeodist.o: libgeodist.c libgeodist.h
	$(CC) $(CFLAGS) -c libgeodist.c

libdinos.o: libdinos.c libdinos.h
	$(CC) $(CFLAGS) -c libdinos.c

all: d23

clean:
	rm -rf *.o d23 
