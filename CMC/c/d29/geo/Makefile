all:	libgeodist.so

libgeodist.so:	libgeodist.c
	gcc -g -fPIC -shared libgeodist.c -o libgeodist.so -lm

clean:
	rm -f libgeodist.so
