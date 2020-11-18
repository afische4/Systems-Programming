#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for d18
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS :=  -Wall 
d18Objs := d18.o liblittlelib.so

d18: $(d18Objs) 
	$(CC) $(CFLAGS) -o d18 $(d18Objs)

liblittlelib.so: littlelib.c littlelib.h
	$(CC) -fPIC -shared littlelib.c -o liblittlelib.so

all: d18

clean:
	rm -rf liblittelib.so d18
