#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for d28
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -g -Wall -lm -lpthread 
d28Objs := d28.o libgeodist.so libdinos.so 

d28: $(d28Objs)
	$(CC) $(CFLAGS) -o d28 $(d28Objs)

d28.o: d28.c libgeodist.h libdinos.h
	$(CC) $(CFLAGS) -c d28.c 

libgeodist.so: libgeodist.c libgeodist.h
	$(CC) $(CFLAGS) -fPIC -shared libgeodist.c -o libgeodist.so 

libdinos.so: libdinos.c libdinos.h
	$(CC) $(CFLAGS) -fPIC -shared libdinos.c -o libdinos.so 

all: d28

clean:
	rm -rf *.o *.so d28 
