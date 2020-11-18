#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>
#define NT 4
        int n, len=256;
        char *s;// = argv[2];
        
        char *buf;// = malloc(len * sizeof(char));
int num_run;
typedef struct{
    int tn;
} threadarg;
typedef struct{
    int t;
    char *b;
} rets;
rets r[NT];
int readline(FILE *fp, char *buf, int len)
{
    char c = fgetc(fp);
    int i = 0;
    
    memset(buf, 0, len);
    
    while((c != '\n') && (i < len))
    {
        if (c == EOF)
        {
            i = -1;
            break;
        }
        
        buf[i] = c;
        
        c = fgetc(fp);
        i++;
    }
    
    return i;
}

int levenshtein(char *s, int ls, char *t, int lt)
{
        int a, b, c;
 
        if (!ls) return lt;
        if (!lt) return ls;
 
        if (s[ls - 1] == t[lt - 1])
                return levenshtein(s, ls - 1, t, lt - 1);
 
        a = levenshtein(s, ls - 1, t, lt - 1);
        b = levenshtein(s, ls,     t, lt - 1);
        c = levenshtein(s, ls - 1, t, lt    );
 
        if (a > b) a = b;
        if (a > c) a = c;
 
        return a + 1;
}

void * threadfcn(void *varg){
    threadarg *arg = (threadarg *) varg;
    fflush(NULL); 
    //dino t;
    //nearest_dinos[n+arg->tn] = nearest_dino(dinos[n+arg->tn], &t, dinos, ND, &calc_geodist);
    r[arg.tn].t = levenshtein(s, strlen(s), r[arg.tn].b, n);

//printf("%d\t%s\n", levenshtein(s, strlen(s), buf, n), buf);
    return varg;
}


int main(int argc, char **argv)
{    
        if(argc<3)
            return 1;
    pthread_t tid[NT];
    threadarg targs[NT]; 

        s = argv[2];
        int i,j,k,m;
        FILE *fp = fopen(argv[1], "r");
        
        buf = malloc(len * sizeof(char));
        n = readline(fp, buf, len);

        while (n!=-1)
        {
            for(j = 0; j < NT; j++)
                targs[j].tn = j;
            for(k = 0; k < NT; k++){
                pthread_create(&tid[k], NULL, threadfcn, (void *) &targs[k]);
                n = readline(fp, buf, len);
                r[k].b = buf
            }
            for(m = 0; m < NT; m++){
                pthread_join(tid[m], NULL);
                printf("%d\t%s\n", r[m].t, r[m].b);
            }  



            printf("%d\t%s\n", levenshtein(s, strlen(s), buf, n), buf);
            n = readline(fp, buf, len);
        }
        
        fclose(fp);
            
        return 0;
}
