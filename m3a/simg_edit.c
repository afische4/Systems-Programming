#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libsimg.h"

void end(void);
int reset_simg(void);
void raw_mode(void);
int editor(simg_img *img, simg_cursor *curs, char* fn);
void refreshSimg(simg_img *img, simg_cursor *curs);
void fatal(char*message);

static struct termios orig_termios;  
static int ttyfd = STDIN_FILENO;     

int main(int argc, char* argv[]){
    if (! isatty(ttyfd)) fatal("not on a tty");
    if (tcgetattr(ttyfd,&orig_termios) < 0) fatal("can't get tty settings");
    if (atexit(end) != 0) fatal("atexit: can't register tty reset");
    
    char * fn;
    simg_img img;// = malloc(sizeof(simg_img));
    simg_pixel ***data = malloc(sizeof(simg_pixel**));
    simg_pixel **pxls = malloc(sizeof(simg_pixel*));
    simg_pixel *pxl = malloc(sizeof(simg_pixel));
    pxl = *pxls;
    pxls = *data;
    img.data = malloc(sizeof(simg_pixel***));
    img.data = data;//malloc(sizeof(simg_pixel**));
    simg_cursor curs;
    char * k = malloc(sizeof(char));
    curs.c = *k;
    curs.c = 'X';
    curs.cx = 0;
    curs.cy = 0;
    curs.r = 5;
  
    /* display file if it exists */
    if(argc > 1){
        fn = argv[1];
        //simg_read(img, fn);
    }
    else{
        simg_create(&img, 9, 15, ' ');
        fn = "new_creation.simg";
    }
    
    int i, j;
    for(i = 0; i < img.height; i++){
        for(j = 0; j < img.width; j++){
                if(img.data[i][j]->c == 0){
                    img.data[i][j]->c = ' ';//malloc(sizeof(simg_pixel));
                    img.data[i][j]->r = 0;}
        }
    }

    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    refreshSimg(&img, &curs);
    raw_mode();      
    editor(&img, &curs, fn);     
    free(data);
    free(pxls);
    free(pxl);
    free(k);
    return 0;       
}

void end(void){                      
   reset_simg();        
}
                      
int reset_simg(void){
    if (tcsetattr(ttyfd,TCSAFLUSH,&orig_termios) < 0) return -1;
    return 0;
}

void raw_mode(void){
    struct termios raw;
    raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 1; 
    /* put terminal in raw mode after flushing */
    tcsetattr(ttyfd, TCSAFLUSH, &raw);
}

void refreshSimg(simg_img *img, simg_cursor *curs) {
    reset_simg(); 
    write(STDOUT_FILENO, "\x1b[?25h", 6);
    int i;
    for(i = 0; i < img->height; i++){
        write(STDOUT_FILENO, "\033[A", 3);
    }
    simg_print(img, curs);
    raw_mode();
}

int editor(simg_img *img, simg_cursor *curs, char* fn){
    char up[]="\033[A", down[]="\033[B", right[]="\033[C", left[]="\033[D";
    int nread = 0;
    char c;
    int i,f;

    while(nread = read(STDIN_FILENO, &c, 1)){
        switch(c){
            case 'q':
                reset_simg(); 
                return 0;
            case 's': 
                simg_write(img, fn);//write(STDOUT_FILENO, eightbitchars + 'Z', 1);
                break;
            case 'l':
                simg_read(img, fn);
                curs->cx = 0;
                curs->cy = 0;
                refreshSimg(img, curs);
                break;
            case 'c':
                read(STDIN_FILENO, &c, 1);
                curs->c = c;
                refreshSimg(img, curs);
                break;
            case 'r':
                read(STDIN_FILENO, &c, 1);
                c = atoi(&c);
                curs->r = c;
                refreshSimg(img, curs);
                break;
            case 'p':
                simg_setpixel(img, curs->cx, curs->cy, curs->r, curs->c);
                refreshSimg(img, curs);
                break;
            case 'A': 
                if(curs->cy < img->height-1){
                    curs->cy++;//write(STDOUT_FILENO, up, 3);
                    refreshSimg(img, curs);}
                break;
            case 'B': 
                if(curs->cy > 0){// img -> height)
                    curs->cy--;//write(STDOUT_FILENO, down, 3);
                    refreshSimg(img, curs);} 
                break;
            case 'C': 
                if(curs->cx < img->width-1){
                    curs->cx++;//write(STDOUT_FILENO, right, 3);
                    refreshSimg(img, curs);}
                break;
            case 'D': 
                if(curs->cx > 0){
                    curs->cx--;//write(STDOUT_FILENO, left, 3);
                    refreshSimg(img, curs);}
                break;
            default:
                break;
        }
    }
}

void fatal(char *message){
    fprintf(stderr,"fatal error: %s\n",message);
    exit(1);
}
