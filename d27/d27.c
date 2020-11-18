#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include "libdinos.h"
#include "libgeodist.h"
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>
#include <limits.h>
#define NP 4

int num_run;
int n;
dino *dinos[30000]; 
double x;
double nearest_dinos[20000];
int ND;

typedef struct{
    int tn;
} threadarg;

typedef struct{
    int mynum;
    double dist;
} fret;

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
//double rets[NT];

void * threadfcn(void *varg){
    threadarg *arg = (threadarg *) varg;
    fflush(NULL); 

    fret out;
    dino t;

    out.mynum = arg->tn;
    out.dist = nearest_dino(dinos[arg->tn], &t, dinos, ND, &calc_geodist);
    

    char *fn = malloc(256 * sizeof(char));
    sprintf(fn, "tmp_%d.bin", getpid());
    FILE *fp = fopen(fn, "wb");
    //printf("%s\t%d\t%f\n", fn, out.mynum, out.dist);
    fwrite(&out, sizeof(fret), 1, fp);
    fclose(fp);
    free(fn);
    return 0;
}
    
int main()
{
    n = 0;
    int i,j,k,m;
    int cpid;
    fret ret;

    ND = readdinos("dinosaur.dat", dinos);

    //pthread_t tid[NT];
    threadarg targs[NP];
    
    for(n = 0; n < 20000; n+=NP){
        for(j = 0; j < NP; j++){
            targs[j].tn = j+n;
            //printf("%d\n", targs[j].tn);
        }
        for(k = 0; k < NP; k++){
            cpid = fork();
            if(cpid == 0)
            {
                threadfcn((void *) &targs[k]);
                return 0;
            }
            //pthread_create(&tid[k], NULL, threadfcn, (void *) &targs[k]);
        }
        for(m = 0; m < NP; m++){
            cpid = wait(NULL);
            char *fn = malloc(256 * sizeof(char));
            sprintf(fn, "tmp_%d.bin", cpid);
            FILE *fp = fopen(fn, "rb");
            fread(&ret, sizeof(fret), 1, fp);
            nearest_dinos[ret.mynum] = ret.dist;
            fclose(fp);
            remove(fn);
            free(fn); 
            //pthread_join(tid[m], NULL);
        }
    }

    //FILE *fp = fopen("results.txt", "w"); 
    for(i=0; i < 20000; i++)
    {
        printf("%d\t%f\n", i, nearest_dinos[i]);
        //fprintf(fp, "%d\t%f\n", i, nearest_dinos[i]);
        free(dinos[i]->name);
        free(dinos[i]);
    }
    //fclose(fp);

    return 0; 
}
