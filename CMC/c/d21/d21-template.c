#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// your code here (define the dino struct)
// use typedef struct, not just struct

void save_dino(dino *d, char *ofn)
{
    // your code here
}

void load_dino(dino *d, char *ifn)
{
    // your code here
}

int main(int argc, char **argv)
{
    if(argc != 2)
        return 1;
    
    char *fn = argv[1];
    
    // create a dino struct and give it the following values:
    // latitude = 51.083332
    // longitude = -1.166667
    // name = "Aves indet."
    // do NOT hardcode the string length, get it with strlen() instead
    
    // call save_dino() and save d0 to the given filename (fn)
    
    dino d1;
    
    // call load_dino() and load the file you just saved into d1 (NOT d0)
    
    printf("d1.lat %f\n", d1.lat);
    printf("d1.lng %f\n", d1.lng);
    printf("d1.name %s\n", d1.name);
    
    return 0;
}
