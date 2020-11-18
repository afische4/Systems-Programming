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
    char * fsimg;
    int x=0, y=0, height=0, width=0;
    char tmp;

    simg_img img;//= malloc(sizeof(simg_img));

    //simg_pixel *pixel = malloc(sizeof(simg_pixel)); //one simg_pixel
    
    //char * ch = malloc(sizeof(char));
    //pixel->c = *ch;

    //*data = pixels;

    //img->data = data;


    if(argc >= 2){
        ftxt = fopen(argv[1], "r");
        fsimg = argv[2];
    }
    else{
        ftxt = fopen("dino.txt", "r");
        fsimg = "test.simg";
        //simg_create(img, 3, 5, '#');
    }

    //make variables to track x y coords

    while(fscanf(ftxt, "%c", &tmp) != EOF){
        fscanf(ftxt, "%c", &tmp);
        while(tmp != '\n' && (height == 0)){
            fscanf(ftxt, "%c", &tmp);
            width++;
        }
        height++;
    }
    
    img.height = height;
    img.width = width;
    printf("%d %d\n",img.width, img.height);
    rewind(ftxt);
    
    //simg_pixel **pixels = malloc(width*sizeof(simg_pixel*)); //point to array of simg_pixels (row)
    //simg_pixel ***data = malloc(height*sizeof(simg_pixel**)); // array of pointers that point to array of pixel ptrs
    x = 0;
    y = 0;
    //img.data = data;//malloc(height*sizeof(simg_pixel**));
    
    simg_create(&img, height, width, ' ');
    while(fscanf(ftxt, "%c", &tmp) != EOF){
        printf("%c", tmp);
        simg_setpixel(&img, x, height-y, 0, tmp); 
        while(tmp != '\n'){
            fscanf(ftxt, "%c", &tmp);
            printf("%c", tmp);
            simg_setpixel(&img, x, height-y, 0, tmp); 
            /**ch = tmp;

            pixel->c = tmp;
            pixel->r = 0;
            
            img.data[i][j] = pixel;*/

            //simg_setpixel(&img, j, i, 0, tmp);
            x++;  
        }

        x = 0;
        //img->data[i] = pixels;
        y++;
    } 
    //img->data = data;
    //simg_create(&img, height, width, '#');

    //simg_setpixel(&img, x, height-y, 0, tmp); 
    simg_print(&img, NULL);
    
    for(y = 0; y < height; y++){
        simg_setpixel(&img, x, height-y, 0, tmp);
        for(x = 0; x < width; x++){
            simg_setpixel(&img, x, y, 0, tmp);
        }
    }

//    simg_print(&img, NULL);

    /*free(ch); 
    free(pixels);
    free(data);
    free(pixel);
    //free(img);*/
    fclose(ftxt);
    return 0;

}







