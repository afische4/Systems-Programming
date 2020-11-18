    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

#include "libsoftmodem.h"
#include "libsecretradio.h"

char *audio;
char *message;
int c;
int msglen;
int msgpos;
int nummsg;

void radio_callback(int audlen)
{
    //audlen is num bytes
    //AA<LENGTH>B

    char name[50];
/*write the message to temporary files*/
    char ** msg = malloc(audlen*sizeof(char*));
    int i,len;
    char ptr;
    msglen = rx(msg, audio, audlen);
    sprintf(name, "msg_%d.txt", 0);
    FILE *fp  = fopen(name, "a");

    for(i = 0; i < msglen; i++){
        fprintf(fp, "%c", *(*msg + i));  
    }

    free(msg); 
    fclose(fp);
    nummsg++;
}

int main(int argc, char **argv)
{
    nummsg = 0;
    msgpos = 0;
    msglen = 0;
    c = 0;
    int i;
    char * name;
    char *message;
    secretradio_init();

    audio = secretradio_get_audioloc();
    
    secretradio_register_callback(&radio_callback);
    
    secretradio_listen(2);
    
    secretradio_cleanup();
    
    printf("%d %d %d %d\n", nummsg, msgpos, msglen, c);
   
     
    FILE* fp = fopen("msg_0.txt", "rb");
    fscanf(fp, "%s", message);
    printf("%s", message);
    //sprintf(name, "msg_%d.txt", 1);
    //FILE* out = fopen(name, "wb");

    //fprintf(out, "%s", "hi"); 
    //free(fp);
    //free(out);
    return 0;
}
