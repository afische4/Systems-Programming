#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int readline(FILE *fp, char *buf, int len);
int split(char *buf, char **splits, char delim, int max, int len);

#endif
