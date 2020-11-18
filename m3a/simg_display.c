#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsimg.h"


/*
    BYTES 1-4:  height of the image in rows as an integer
          5-8:  width of the image in chars as an integer
          9+:   height X width pixel data with last row printed first
*/

int main(int argc, char *argv[]){
    char * fn;
    simg_img img;


    if(argc > 1){
        fn = argv[1];
        simg_read(&img, fn);
    }
    else{
        simg_create(&img, 3, 5, '#');
    }
    
    simg_print(&img, NULL);

    return 0;

}







