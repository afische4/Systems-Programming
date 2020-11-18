#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for d22
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -Wall 
d22Objs := d22.o libdinos.o

d22: $(d22Objs)
	$(CC) $(CFLAGS) -o d22 $(d22Objs) 

d22.o: d22.c libdinos.h
	$(CC) $(CFLAGS) -c d22.c 

libdinos.o: libdinos.c libdinos.h
	$(CC) $(CFLAGS) -c libdinos.c

all: d22

clean:
	rm -rf *.o d22 
