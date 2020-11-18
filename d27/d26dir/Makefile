#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for d26
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -g -Wall -lm -lpthread 
d26Objs := d26.o libgeodist.so libdinos.so

d26: $(d26Objs)
	$(CC) $(CFLAGS) -o d26 $(d26Objs)

d26.o: d26.c libgeodist.h libdinos.h
	$(CC) $(CFLAGS) -c d26.c 

libgeodist.so: libgeodist.c libgeodist.h
	$(CC) $(CFLAGS) -fPIC -shared libgeodist.c -o libgeodist.so 

libdinos.so: libdinos.c libdinos.h
	$(CC) $(CFLAGS) -fPIC -shared libdinos.c -o libdinos.so 

all: d26

clean:
	rm -rf *.o *.so d26 dino_*

