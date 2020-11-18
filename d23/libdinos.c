#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libdinos.h"
#include "libgeodist.h"

int readline(FILE *fp, char *buf, int len){
    char c = fgetc(fp);
    int i = 0; 
    while((c != '\n') && i < len){
        buf[i] = c; 
        c = fgetc(fp);
        i++;
        if (c == EOF){
            i = -1;
            break;
        }
    }
    return i;
}

int split(char *buf, char **splits, char delim, int max, int len){
  int i = 0, x = 0, count = 0;
  char * section = malloc(max*sizeof(char));
  for(i=0; i < len; i++){
    if( buf[i] != delim){
      section[x] = buf[i];
      x++;
    }else{
      splits[count]=section;
      count++;
      section = malloc(max*sizeof(char));
      x = 0;
    }
  }

  return count;
}

int readdinos(char *fn, dino **dinos)
{
    FILE *fp=fopen(fn, "r");
    dino *temp;
    char delim = '\t';
    int max = 2048, i = 0, m, n, headnum, numsplits;
    double dbl;
    char *ptr;
    char *headers[27];
    char **splits = malloc(27 * sizeof(char*));
    for(i=0; i < 27; i++){
        splits[i] = malloc(max*sizeof(char));
    }
    char *buf = malloc(max * sizeof(char));
    n = readline(fp, buf, max);
    headnum  = split(buf, headers, delim, max, n);
    for(i=0; i< 30000; i++){
        dinos[i] = malloc(sizeof(dino));
    }
    i=0;

    while(n!=-1)
    {
        n = readline(fp, buf, max);
        if (n>0){
            numsplits = split(buf, splits, delim, max , n);
        }else{
            numsplits = 0;
        }
        if (numsplits == headnum)
        {
            temp = malloc(sizeof(dino));
            dbl = strtod(splits[19], &ptr);
            (*temp).lat = dbl;

            dbl = strtod(splits[18], &ptr);
            (*temp).lng = dbl;

            dbl = strtod(splits[15], &ptr);
            (*temp).maxma = dbl;

            dbl = strtod(splits[16], &ptr);
            (*temp).minma = dbl;

            (*temp).namelen = strlen(splits[5]);
            (*temp).name = malloc((*temp).namelen * sizeof(char));
            (*temp).name = splits[5];

            dinos[i] = temp;
            i++;

            buf = malloc(max*sizeof(char));
            splits = malloc(27 * sizeof(char*));
            for(m=0; m < 27; m++){
                splits[m] = malloc(max*sizeof(char));
            } 
        }
    }

    fclose(fp);
    return i;
}

double nearest_dino(dino *d0, dino *d1, dino **dinos, int numdinos, double (*funPtr)(dino*,dino*)){
    double dist, min;
    int i;
    min = (*funPtr)(d0, dinos[0]);
    for(i=1; i<29652; i++){
        dist = (*funPtr)(d0, dinos[i]);
        if((dist < min) && dist != 0.000000){
            memcpy(d1, dinos[i], sizeof(dino));
            min = (*funPtr)(d0, dinos[i]);
        }
    }
    
    return min;
}
