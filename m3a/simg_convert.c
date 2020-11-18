#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsimg.h"

/* convert a text file to a .simg */
/*
    BYTES 1-4:  height of the image in rows as an integer
          5-8:  width of the image in chars as an integer
          9+:   height X width pixel data with last row printed first
*/

int main(int argc, char *argv[]){
    FILE * ftxt;
    char * fn;
    char * fsimg;
    int x = 0, y = 0, height=0, width=0;
    char tmp;
    simg_img img;

    if(argc >= 2){
        fn = argv[1];
        ftxt = fopen(argv[1], "r");
        fsimg = argv[2];
    }
    else{
        ftxt = fopen("dino.txt", "r");
        fsimg = "dino.simg";
    }


    while(fscanf(ftxt, "%c", &tmp) != EOF){
        while(tmp != '\n' ){
            fscanf(ftxt, "%c", &tmp);
            if(height==2)
                width++;
        }
        height++;
    }

    simg_create(&img, height, width, ' ');
    rewind(ftxt);
    
    for(y = height-1; y>=0; y--){
        for(x = 0; x <= width; x++){
            fscanf(ftxt, "%c", &tmp);
            printf("%c", tmp);
            if(tmp == '\n')
                simg_setpixel(&img, x, y, 0, ' ');
            else
                simg_setpixel(&img, x, y, 0, tmp);
        }
    }
    
    simg_write(&img, fsimg);
    printf("\n");
    fclose(ftxt);
    //simg_print(&img, NULL);
    printf("%s converted and saved as %s\n", fn, fsimg);

    return 0;

}







