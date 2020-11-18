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
  char * section = malloc(max*sizeof(char)+1);
  memset(section, 0, max*sizeof(char) + 1);

  for(i=0; i < len; i++){
    if( buf[i] != delim){
      section[x] = buf[i];
      x++;
    }else{
    splits[count] = malloc(sizeof(char)*x+1);
    memset(splits[count], 0, sizeof(char)*x + 1);
    strcpy(splits[count], section); 
      count++;
      memset(section, 0, max*sizeof(char) + 1);
      x = 0;
    }
  }
  free(section);
  return count;
}

int readdinos(char *fn, dino **dinos)
{
    FILE *fp=fopen(fn, "r");
    char delim = '\t';
    int max = 2048, i = 0, n, f,numsplits;
    char *ptr;
    char **splits = malloc(27 * (sizeof(char*)));
    memset(splits, 0, sizeof(char*));
    char *buf = malloc(max * sizeof(char)+1);
    memset(buf, 0, sizeof(char)*max + 1); 
    n = readline(fp, buf, max);
    i=0;
    while(n!=-1)
    {
        n = readline(fp, buf, max);
        if (n >= 27*sizeof(char)){
            numsplits = split(buf, splits, delim, max , n);

        }else{
            numsplits = 0;
        }
        if (numsplits == 27)
        {
            dinos[i] = malloc(sizeof(dino));
            memset(dinos[i], 0, sizeof(dino));            
      
            (*dinos[i]).lat = strtod(splits[19], &ptr);
            (*dinos[i]).lng = strtod(splits[18], &ptr);
            (*dinos[i]).maxma = strtod(splits[15], &ptr);
            (*dinos[i]).minma = strtod(splits[16], &ptr);
            (*dinos[i]).namelen = (int)strlen(splits[5]);
            (*dinos[i]).name = malloc(sizeof(char) * (*dinos[i]).namelen + 1);
            memset((*dinos[i]).name, 0, sizeof(char) * (*dinos[i]).namelen + 1);
            strcpy((*dinos[i]).name, splits[5]);
            i++;
        }
        memset(buf, 0, sizeof(char) * max + 1);    
        for(f=0;f<numsplits;f++){
            free(splits[f]);
        }
        memset(splits, 0, 27*(sizeof(char)));
        }
    free(splits);
    free(buf);
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


