#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for m3d
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -g -lpthread -lm 
m3dObjs := m3d.so libsoftmodem.so libsecretradio.so

all: clean m3d run
	cat msg_*

m3d: $(m3dObjs)
	$(CC) $(CFLAGS) -o m3d $(m3dObjs)

m3d.so: m3d.c libsoftmodem.h libsecretradio.h 
	$(CC) $(CFLAGS) -fPIC -shared m3d.c -o m3d.so

run:
	LD_LIBRARY_PATH=. ./m3d

test:
	./m3d_test.sh

clean:
	rm -rf m3d.so m3d msg_*









