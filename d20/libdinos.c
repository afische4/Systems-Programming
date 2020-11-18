#include "libdinos.h"
#include <stdio.h>
#include <string.h>

int readline(FILE *fp, char *buf, int len){
    char c = fgetc(fp);
    int i = 0;
    
    while((c != '\n') && (i < len)){
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
  int i = 0, x = 0,count = 0;
  char * section = malloc(len*sizeof(char));
  memset(section, 0, sizeof(char)*len);
  for(i=0; i < len; i++){
    if( buf[i] != delim){
      section[x] = buf[i];
      x++;
    }else{
      splits[count] = malloc(sizeof(char)*x+1);
      memset(splits[count], 0, sizeof(char)*x+1); 
      strcpy(splits[count], section);
      count++;
      memset(section, 0,len*sizeof(char));
      x = 0;
    }
  }
  free(section);
  return count;
}


