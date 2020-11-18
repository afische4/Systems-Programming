#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libsimg.h"

void tty_atexit(void);
int tty_reset(void);
void tty_raw(void);
int screenio(void);
void fatal(char *mess);

struct editorConfig {
    int screenrows;
    int screencols;
    char * fn;
    simg_img img;
    simg_cursor curs;
    struct termios orig_termios;
};

struct editorConfig E;
static struct termios orig_termios;  /* TERMinal I/O Structure */
static int ttyfd = STDIN_FILENO;     /* STDIN_FILENO is 0 by default */

int main(int argc, char* argv[])
   {
    /*if (! isatty(ttyfd)) fatal("not on a tty");
    if (tcgetattr(ttyfd,&orig_termios) < 0) fatal("can't get tty settings");
    if (atexit(tty_atexit) != 0) fatal("atexit: can't register tty reset");*/
    /* display file if it exists */

    E.curs.c = 'X';
    E.curs.cx = 0;
    E.curs.cy = 0;
    E.curs.r = 1;
    if(argc > 1){
        E.fn = argv[1];
        simg_read(&E.img, E.fn);
    }
    else{
        simg_create(&E.img, 9, 15, '#');
    }
    tty_raw();      
    screenio();     
    return 0;      
   }


/* exit handler for tty reset */
void tty_atexit(void)  /* NOTE: If the program terminates due to a signal   */
{                      /* this code will not run.  This is for exit()'s     */
   tty_reset();        /* only.  For resetting the terminal after a signal, */
}                      /* a signal handler which calls tty_reset is needed. */

/* reset tty - useful also for restoring the terminal when this process
   wishes to temporarily relinquish the tty
*/
int tty_reset(void)
   {
    /* flush and reset */
    if (tcsetattr(ttyfd,TCSAFLUSH,&orig_termios) < 0) //return -1;
        simg_read(&E.img, E.fn);
        simg_print(&E.img, &E.curs);
    return 0;
   }

/* put terminal in raw mode - see termio(7I) for modes */
void tty_raw(void)
   {
    struct termios raw;
    raw = orig_termios;  /* copy original and then modify below */
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    /* control modes - set 8 bit chars */
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    /* put terminal in raw mode after flushing */
    if (tcsetattr(ttyfd,TCSAFLUSH,&raw) < 0) fatal("can't set raw mode");
   }

int screenio(void)
   {
    int bytesread;
    char * key;
    char c_in, c_out, up[]="\033[A", down[]="\033[B", right[]="\033[C", left[]="\033[D";
    char eightbitchars[256];                  /* will not be a string! */

    /* A little trick for putting all 8 bit characters in array */
    {int i;  for (i = 0; i < 256; i++) eightbitchars[i] = (char) i; }

    int nread = 0;
    char c;

    while(nread = read(STDIN_FILENO, &c, 1)){
        switch(c){
            case 'q': return 0;
            case 's':
                simg_write(&E.img, E.fn);
                tty_reset();
                break;
            case 'A': write(STDOUT_FILENO, up, 3);
                break;
            case 'B': write(STDOUT_FILENO, down, 3);
                break;
            case 'C': write(STDOUT_FILENO, right, 3);
                break;
            case 'D': write(STDOUT_FILENO, left, 3);
                break;
        }
    }
}

void fatal(char *message)
   {
    fprintf(stderr,"fatal error: %s\n",message);
    exit(1);
   }

    /* control chars - set return condition: min number of bytes and timer 
    raw.c_cc[VMIN] = 5; raw.c_cc[VTIME] = 8; // after 5 bytes or .8 seconds
                                                after first byte seen      
    raw.c_cc[VMIN] = 0; raw.c_cc[VTIME] = 0; // immediate - anything       
    raw.c_cc[VMIN] = 2; raw.c_cc[VTIME] = 0; // after two bytes, no timer  
    raw.c_cc[VMIN] = 0; raw.c_cc[VTIME] = 8; // after a byte or .8 seconds */

    /* input modes - clear indicated ones giving: no break, no CR to NL, 
       no parity check, no strip char, no start/stop output (sic) control */
    /* output modes - clear giving: no post processing such as NL to CR+NL */

    /* local modes - clear giving: echoing off, canonical off (no erase with 
       backspace, ^U,...),  no extended functions, no signal chars (^Z,^C) */

/* Read and write from tty - this is just toy code!! 
   Prints T on timeout, quits on q input, prints Z if z input, goes up
   if u input, prints * for any other input character
*/


            //default :
                //c_out = '*';
                //write(STDOUT_FILENO, &c_out, 1);







