#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for softmodem
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -g -lpthread -lm 
softmodemObjs := softmodem.so libsoftmodem.so

all: softmodem softmodem_test runtx runrx runtest

softmodem_test: 
	$(CC) $(CFLAGS) -o softmodem_test softmodem_test.c -lsoftmodem -L.

softmodem: $(softmodemObjs)
	$(CC) $(CFLAGS) -o softmodem $(softmodemObjs)

softmodem.so: softmodem.c libsoftmodem.h 
	$(CC) $(CFLAGS) -fPIC -shared softmodem.c -o softmodem.so

libsoftmodem.so: libsoftmodem.c libsoftmodem.h
	$(CC) $(CFLAGS) -fPIC -shared libsoftmodem.c -o libsoftmodem.so

runtest:
	LD_LIBRARY_PATH=. ./softmodem_test "a secret message"

runtx:
	LD_LIBRARY_PATH=. ./softmodem tx 8000 0.0 message.txt message.pcm 

runrx:
	LD_LIBRARY_PATH=. ./softmodem rx 8000 message.pcm message.txt 

clean:
	rm -rf softmodem.so softmodem softmodem_test runtest runrx runtx










