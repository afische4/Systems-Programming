#Author: Anna Fischer
#email: afische4@nd.edu
#
#Makefile for simg_edit
#CC is GCC compiler
CC := gcc
#compiler flags for production quality compilation
CFLAGS := -g -lpthread -lm 
simg_displayObjs := simg_display.so libsimg.so
simg_convertObjs := simg_convert.so libsimg.so
simg_editObjs := simg_edit.so libsimg.so

all: clean simg_edit simg_display simg_convert 

simg_display: $(simg_displayObjs)
	$(CC) $(CFLAGS) -o simg_display $(simg_displayObjs)

simg_display.so: simg_display.c libsimg.h 
	$(CC) $(CFLAGS) -fPIC -shared simg_display.c -o simg_display.so

simg_convert: $(simg_convertObjs)
	$(CC) $(CFLAGS) -o simg_convert $(simg_convertObjs)

simg_convert.so: simg_convert.c libsimg.h 
	$(CC) $(CFLAGS) -fPIC -shared simg_convert.c -o simg_convert.so

simg_edit: $(simg_editObjs)
	$(CC) $(CFLAGS) -o simg_edit $(simg_editObjs)

simg_edit.so: simg_edit.c libsimg.h 
	$(CC) $(CFLAGS) -fPIC -shared simg_edit.c -o simg_edit.so

test:
	./m3a_test.sh

debug:
	LD_LIBRARY_PATH=. gdb simg_convert

clean:
	rm -rf simg_edit.so simg_edit simg_display.so simg_display simg_convert.so simg_convert
	rm -rf dino_t.simg


