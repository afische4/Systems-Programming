#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for d17
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -Wall 
LIB := lib
LIBDIR := .
d16Objs := d16.o lib.o

d16: $(d16Objs)
	$(CC) $(CFLAGS) -o d16 $(d16Objs) 

d16.o: d16.c lib.h
	$(CC) $(CFLAGS) -c d16.c 

lib.o: lib.c lib.h
	$(CC) $(CFLAGS) -c lib.c 

all: d16 

clean:
	rm -rf *.o d16 
