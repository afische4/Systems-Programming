#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include "libdinos.h"
#include "libgeodist.h"
#include <unistd.h>
#include <string.h>

int num_run;
dino *dinos[30000]; 
dino d;

void printdino(dino *d)
{
    printf("%f %f %f %f %s\n", d->lat, d->lng, d->maxma, d->minma, d->name);
}

void handle_sigusr1(int sig, siginfo_t *siginfo, void *context){
    int DINONUM;
    char fname[50];
    
    FILE *fp = fopen("dinonum.bin", "r");
    fread(&DINONUM, sizeof(int), 1, fp); 
    fclose(fp);
    sprintf(fname, "dino_%d.bin", DINONUM);
    save_dino(dinos[DINONUM], fname);
    num_run++;
    //printdino(dinos[DINONUM]);
}

void handle_sigusr2(int sig, siginfo_t *siginfo, void *context){
    int DINONUM;
    char fname[50];
    FILE *fp = fopen("dinonum.bin", "r");
    fread(&DINONUM, sizeof(int), 1, fp); 
    fclose(fp);
    sprintf(fname, "dino_%d.bin", DINONUM);
    load_dino(dinos[DINONUM], fname);
    num_run++;
    //printdino(dinos[DINONUM]);

}

double calc_geodist(dino *d0, dino *d1)
{
    return geodist(d0->lat, d0->lng, d1->lat, d1->lng);
}

double calc_timedist(dino *d0, dino *d1)
{
    double t0 = (d0->maxma + d0->minma) / 2;
    double t1 = (d1->maxma + d1->minma) / 2;
    return fabs(t0 - t1);
}


int main()
{
    int n;

    readdinos("dinosaur.dat", dinos);
    int pid = getpid();
    printf("pid: %d\n", pid);
    struct sigaction act1;
    struct sigaction act2;

    act1.sa_sigaction = &handle_sigusr1;
    act1.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act1, NULL);
    act2.sa_sigaction = &handle_sigusr2;
    act2.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR2, &act2, NULL);
    
    while(1){}
    while(2){}
    for(n = 0; n < 29652; n++){
        free((*dinos[n]).name);
        free(dinos[n]);
    }

    return 0; 
}
