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
//struct termios orig_termios;

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
    simg_img img;
    simg_cursor curs;
    curs.c = 'X';
    curs.cx = 0;
    curs.cy = 0;
    curs.r = 1;
    /* display file if it exists */
    if(argc > 1){
        fn = argv[1];
        simg_read(&img, fn);
    }
    else{
        simg_create(&img, 9, 15, '#');
    }
    
 
    /* Display a cursor over the image  */
    
    editorRefreshScreen(&img, &curs);
    //simg_print(&img, &curs);
    getWindowSize(&img);
    enableRawMode();
    initEditor(&img);
    editorProcessKeypress();      
    disableRawMode();
    return 0;
}

/****************************** FUNCTION DEFINITIONS ***************************************/

/*~~~~~~~~~~~~~ write handling  ~~~~~~~~~~~~~*/
void abAppend(struct abuf *ab, const char *s, int len) {
  char *new = realloc(ab->b, ab->len + len);
  if (new == NULL) return;
  memcpy(&new[ab->len], s, len);
  ab->b = new;
  ab->len += len;
}
void abFree(struct abuf *ab) {
  free(ab->b);
}

/*~~~~~~~~~~~~~ terminal configuration ~~~~~~~~~~~~~*/
void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
    die("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr");
  atexit(disableRawMode);
  struct termios raw = E.orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void die(const char *s) {
  perror(s);
  exit(1);
}

int getWindowSize(simg_img *img) {
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    return getCursorPosition(img); 
  } else {
    E.screencols = img->height;
    E.screenrows = img->width;
    return 0;
  }
}

void initEditor(simg_img* img) {
    E.img = *img;
    E.curs.cx = 0;
    E.curs.cy = 0;
    if (getWindowSize(&E.img) == -1) die("getWindowSize");
}

void editorDrawRows(struct abuf *ab) {
  int y;
  for (y = 0; y < E.screenrows; y++) {
    abAppend(ab, "~", 1);
    if (y < E.screenrows - 1) {
      abAppend(ab, "\r\n", 2);
    }
  }
}

/*void editorRefreshScreen(simg_img *img, simg_cursor *curs) {
    //simg_print(img, curs);

    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}*/
void editorRefreshScreen(simg_img *img, simg_cursor *curs) {
  struct abuf ab = ABUF_INIT;
  abAppend(&ab, "\x1b[?25l", 6);
  abAppend(&ab, "\x1b[2J", 4);
  abAppend(&ab, "\x1b[H", 3);
  editorDrawRows(&ab);
  simg_print(&E.img, &E.curs);
  abAppend(&ab, "\x1b[H", 3);
  abAppend(&ab, "\x1b[?25h", 6);
  write(STDOUT_FILENO, ab.b, ab.len);
  abFree(&ab);
}

/*~~~~~~~~~~~~~ input handling ~~~~~~~~~~~~~*/

void editorProcessKeypress() {
  char c = editorReadKey();
  switch (c) {
    case CTRL_KEY('q'):
      write(STDOUT_FILENO, "\x1b[2J", 4);
      write(STDOUT_FILENO, "\x1b[H", 3);
      exit(0);
      break;
    case ARROW_UP:
    case ARROW_DOWN:
    case ARROW_LEFT:
    case ARROW_RIGHT:
      editorMoveCursor(c);
      break;
  }
}

/*char editorReadKey() {
    int nread;
    char c;
    while (1) {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);
        if (c == 'q'){
             break;
        }
    }  
    return c;
}*/

int editorReadKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) die("read");
  }
  if (c == '\x1b') {
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
    if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
    if (seq[0] == '[') {
      switch (seq[1]) {
        case 'A': return ARROW_UP;
        case 'B': return ARROW_DOWN;
        case 'C': return ARROW_RIGHT;
        case 'D': return ARROW_LEFT;
      }
    }
    return '\x1b';
  } else {
    return c;
  }
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

int getCursorPosition(simg_img *img) {
  char buf[32];
  unsigned int i = 0;
  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;
  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
    if (buf[i] == 'R') break;
    i++;
  }
  buf[i] = '\0';
  if (buf[0] != '\x1b' || buf[1] != '[') return -1;
  if (sscanf(&buf[2], "%d;%d", E.curs.cx, E.curs.cy) != 2) return -1;
  return 0;
}
