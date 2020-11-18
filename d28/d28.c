#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libdinos.h"
#include "libgeodist.h"
#include <unistd.h>
#include <math.h>
#include <limits.h>

void printdino(dino *d)
{
    printf("%f %f %f %f %s\n", d->lat, d->lng, d->maxma, d->minma, d->name);
}

void handle_sigchld(int sig)
{
    wait(NULL);
}
void handle_incoming_conn(dino **d, int input)
{
    fflush(NULL);
    int wrklen = 2048, buflen = 256, rc, n;
    char *wrk = malloc(wrklen * sizeof(char)); 
    char *buf = malloc(buflen * sizeof(char));
    char *ptr;
    memset(wrk, 0, wrklen);
    memset(buf, 0, buflen);
    
    while((rc = read(input, buf, buflen)) > 0)
    {
        n = (int)strtol(buf, &ptr, 10);
        sprintf(wrk, "%f %f %f %f %s\n", d[n]->lat, d[n]->lng, d[n]->maxma, d[n]->minma, d[n]->name);
        write(input, wrk, wrklen);
        memset(wrk, 0, wrklen);
        memset(buf, 0, buflen);
    }

}


int main(int argc, char *argv[])
{
    int sock, t, port, cpid, input, n;
    dino *dinos[30000];
    n = readdinos("dinosaur.dat", dinos);

    if (argc < 2){
        fprintf(stderr, "usage %s port\n", argv[0]);
        exit(0);
    }

    port = atoi(argv[1]);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    t = bind(sock, (struct sockaddr *) &addr, sizeof(addr));

    if(t < 0)
    {
        perror("could not bind!");
        exit(-1);
    }
    
    listen(sock, 5);
 
    while(1)
    {
        input = accept(sock, NULL, NULL);
        cpid = fork();
        if(cpid == 0)
        {
            handle_incoming_conn(dinos, input);
            signal(SIGCHLD, &handle_sigchld);
            return 0;
        }else{
            close(input);
        }
    }   

    for(n = 0; n < 29652; n++){
        free((*dinos[n]).name);
        free(dinos[n]);
    }
    return 0;
}


