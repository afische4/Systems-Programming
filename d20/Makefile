#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for d20
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -Wall 
d20Objs := d20.o libdinos.o

d20: $(d20Objs)
	$(CC) $(CFLAGS) -o d20 $(d20Objs) 

d20.o: d20.c libdinos.h
	$(CC) $(CFLAGS) -c d20.c 

libdinos.o: libdinos.c libdinos.h
	$(CC) $(CFLAGS) -c libdinos.c 

all: d20

clean:
	rm -rf *.o d20 
