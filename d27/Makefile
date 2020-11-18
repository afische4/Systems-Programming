#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for d27
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -g -Wall -lm -lpthread 
d27Objs := d27.o libgeodist.so libdinos.so

d27: $(d27Objs)
	$(CC) $(CFLAGS) -o d27 $(d27Objs)

d27.o: d27.c libgeodist.h libdinos.h
	$(CC) $(CFLAGS) -c d27.c 

libgeodist.so: libgeodist.c libgeodist.h
	$(CC) $(CFLAGS) -fPIC -shared libgeodist.c -o libgeodist.so 

libdinos.so: libdinos.c libdinos.h
	$(CC) $(CFLAGS) -fPIC -shared libdinos.c -o libdinos.so 

all: d27

clean:
	rm -rf *.o *.so d27 dino_*

