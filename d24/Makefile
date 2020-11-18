#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for d24
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -Wall -lm -g 
d24Objs := d24.o libgeodist.o libdinos.o

d24: $(d24Objs)
	$(CC) $(CFLAGS) -o d24 $(d24Objs) 

d24.o: d24.c libgeodist.h libdinos.h
	$(CC) $(CFLAGS) -c d24.c 

libgeodist.o: libgeodist.c libgeodist.h
	$(CC) $(CFLAGS) -c libgeodist.c

libdinos.o: libdinos.c libdinos.h
	$(CC) $(CFLAGS) -c libdinos.c

all: d24

clean:
	rm -rf *.o d24 
