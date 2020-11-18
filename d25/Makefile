#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for d25
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -Wall -lm -g 
d25Objs := d25.o libgeodist.so libdinos.so

d25: $(d25Objs)
	$(CC) $(CFLAGS) -o d25 $(d25Objs) 

d25.o: d25.c libgeodist.h libdinos.h
	$(CC) $(CFLAGS) -c d25.c 

libgeodist.so: libgeodist.c libgeodist.h
	$(CC) $(CFLAGS) -fPIC -shared libgeodist.c -o libgeodist.so

libdinos.so: libdinos.c libdinos.h
	$(CC) $(CFLAGS) -fPIC -shared libdinos.c -o libdinos.so

all: d25

clean:
	rm -rf *.o *.so d25 dino_*

#CFLAGS :=  -Wall 
#d18Objs := d18.o liblittlelib.so
#
#d18: $(d18Objs) 
#	$(CC) $(CFLAGS) -o d18 $(d18Objs)
#
#liblittlelib.so: littlelib.c littlelib.h
#	$(CC) -fPIC -shared littlelib.c -o liblittlelib.so
#
#all: d18
#
#clean:
#	rm -rf liblittelib.so d18
