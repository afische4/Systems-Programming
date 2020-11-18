#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "libsimg.h"
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define CTRL_KEY(k) ((k) & 0x1f)
#define ABUF_INIT {NULL, 0}
/*
    a) Load and display an image if the provided filename exists.
      If it doesn't exist, create a default background and size.
    b) Have a cursor display over the image. 
     The cursor should be controllable with the arrow keys. 
     If you press the up arrow, for instance, the cursor should move up one
     row and the image redrawn to show the cursor in the new location. 
     The cursor should not be permitted to leave the height and width range of the image.
    c) If you press "c" followed by a char on the keyboard, the cursor will change
     to that char.  The image should be redrawn to show the cursor with the new char.
    d) If you press "r" followed by a number 0-6, the color of the cursor should 
        change to that color.  The image should be redrawn to show the 
        cursor with the new color.
    e) If you press "p", the pixel in the image underneath the cursor is set to 
        the cursor's char and color. 
    f) If you press "s", the image is saved to the given filename.
    g)If you press "l", the image is reloaded from the given filename.
      Redraw the image.
    h) If you press "q", the program quits without saving changes 
    or annoying "are you sure?" messages I mean come on just let me quit already.
*/

/*STRUCTS*/
struct termios orig_termios;

struct editorConfig {
    int screenrows;
    int screencols;
    simg_img img;
    simg_cursor curs;
    struct termios orig_termios;
};

struct abuf {
  char *b;
  int len;
};

struct editorConfig E;

enum editorKey {
  ARROW_LEFT = 10,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN
};

/* FUNCTION DECLARATIONS */
void enableRawMode();
void disableRawMode();
void die(const char *s);
void editorProcessKeypress();
int editorReadKey();
void editorRefreshScreen(simg_img *img, simg_cursor *curs);
int getWindowSize(simg_img *img);
void initEditor(simg_img* img);
void abAppend(struct abuf *ab, const char *s, int len);
void abFree(struct abuf *ab);
void editorDrawRows(struct abuf *ab);
void editorMoveCursor(int key);
int getCursorPosition(simg_img *img);
 
/************* MAIN ************/
int main(int argc, char *argv[]){
    char * fn;
    
    E.curs.c = 'X';
    E.curs.cx = 0;
    E.curs.cy = 0;
    E.curs.r = 1;
    /* display file if it exists */
    if(argc > 1){
        fn = argv[1];
        simg_read(&E.img, fn);
    }
    else{
        simg_create(&E.img, 9, 15, '#');
    }
    
    /* Display a cursor over the image  */
    enableRawMode();
    editorRefreshScreen(&E.img, &E.curs);
    //simg_print(&img, &curs);
    editorProcessKeypress();

    return 0;
}

/****************************** FUNCTION DEFINITIONS ***************************************/

/*~~~~~~~~~~~~~ write handling  ~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~ terminal configuration ~~~~~~~~~~~~~*/
/*void enableRawMode() {
  struct termios raw = E.orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  //raw.c_cc[VMIN] = 0;
  //raw.c_cc[VTIME] = 1;
}*/
void enableRawMode(void)
   {
    struct termios raw;
    raw = orig_termios;  /* copy original and then modify below */
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    /* control modes - set 8 bit chars */
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    /* put terminal in raw mode after flushing */
    //if (tcsetattr(ttyfd,TCSAFLUSH,&raw) < 0) fatal("can't set raw mode");
   }

void editorRefreshScreen(simg_img *img, simg_cursor *curs) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    simg_print(img, curs);
}

void editorDrawSimg() {
  int y;
  for (y = 0; y < E.img.height; y++) {
    write(STDOUT_FILENO, "~\r\n", 3);
  }
}

/*~~~~~~~~~~~~~ input handling ~~~~~~~~~~~~~*/
void editorProcessKeypress() {
  char c = editorReadKey();
  switch (c) {
    case CTRL_KEY('q'):
      exit(0);
      //exit(0);
      /*write(STDOUT_FILENO, "\x1b[2J", 4);
      write(STDOUT_FILENO, "\x1b[H", 3);
      exit(0);*/
      //break;
    case ARROW_UP:
    case ARROW_DOWN:
    case ARROW_LEFT:
    case ARROW_RIGHT:
      editorMoveCursor(c);
      break;
  }
}

int editorReadKey() {
    int nread = 0;
    char c;
    char seq[4];

    while(read(STDIN_FILENO, &c, 1) != 1){
        seq[nread] = c;
        nread++;
        if (c == 'q')
            return c;
    }
    if(nread == 4){
        switch (seq[3]) {
        case 'A': return ARROW_UP;
        case 'B': return ARROW_DOWN;
        case 'C': return ARROW_RIGHT;
        case 'D': return ARROW_LEFT;
      } 
    }
    return c;
  
}

/*~~~~~~~~~~~~~ cursor handling ~~~~~~~~~~~~~*/
void editorMoveCursor(int key) {
  switch (key) {
    case ARROW_LEFT:
      if (E.curs.cx != 0) {
        E.curs.cx--;
      }
      break;
    case ARROW_RIGHT:
      if (E.curs.cx != E.screencols - 1) {
        E.curs.cx++;
      }
      break;
    case ARROW_UP:
      if (E.curs.cy != 0) {
        E.curs.cy--;
      }
      break;
    case ARROW_DOWN:
      if (E.curs.cy != E.screenrows - 1) {
        E.curs.cy++;
      }
      break;
  }
}


