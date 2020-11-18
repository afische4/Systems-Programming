#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for d24
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -Wall -lm -g 
d24Objs := d24.o libgeodist.so libdinos.so

d24: $(d24Objs)
	$(CC) $(CFLAGS) -o d24 $(d24Objs) 

d24.o: d24.c libgeodist.h libdinos.h
	$(CC) $(CFLAGS) -c d24.c 

libgeodist.so: libgeodist.c libgeodist.h
	$(CC) $(CFLAGS) -fPIC -shared libgeodist.c -o libgeodist.so

libdinos.so: libdinos.c libdinos.h
	$(CC) $(CFLAGS) -fPIC -shared libdinos.c -o libdinos.so

all: d24

run: clean d24
	LD_LIBRARY_PATH=. ./d24

clean:
	rm -rf *.o d24 
