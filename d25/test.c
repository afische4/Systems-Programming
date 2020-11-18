#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>

#include "libdinos.h"

void printdino(dino *d)
{
    printf("%f %f %f %f %d %s\n", d->lat, d->lng, d->maxma, d->minma, d->namelen, d->name);
}

void clearbuf(char *buf, int len)
{
    int i;
    
    for(i=0; i<len; i++)
        buf[i] = 0;
}

int main() 
{
    
    int dn = 8080;

    FILE *fp = fopen("dinonum.bin", "wb");
    fwrite(&dn, sizeof(int), 1, fp);
    fclose(fp);

    char *dfn = malloc(256 * sizeof(char));
    sprintf(dfn, "dino_%d.bin", dn);

    dino d;
    load_dino(&d, dfn);
    printdino(&d);

    d.name = "Santaclausosaurus Rex";
    d.lat = 90.0;
    d.lng = 0.0;
    d.maxma = 4500.0;
    d.minma = 0.0;
    d.namelen = strlen(d.name);
    
    printf("changed to:\n");
    printdino(&d);
    
    save_dino(&d, dfn);
    
    
    printf("received back:\n");

    dino d1;
    load_dino(&d1, dfn);
    
    printdino(&d1);
    
    return 0;
}
