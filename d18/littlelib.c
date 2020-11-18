#include "littlelib.h"
#include "time.h"
#include <stdio.h>

int init_littlelib(){
  int seed = 1337;
  srand(seed);
  return 0; 
}

int arraylen(int a[]){
  int i = 0;
  int count = 0;
  while(a[i] != 0){
    count++;
    i++;
  }
  return count;
}


int sumnums(int a[]){
  int sum = 0;
  int i = 0;
  while(a[i] != 0){
    sum+=a[i];
    i++;
  }
  return sum;
}

void printarray(int a[]){
  int i = 0;
  fprintf(stdout, "{");
  while(a[i] != 0){
    fprintf(stdout, "%2d ", a[i]);
    i++;
  }
  fprintf(stdout, "}\n");
}

void shuffle(int *a, int len){
  int temp, i, rand1, rand2;
  for(i = 0; i < len-1; i++){
    rand1 = randint(0, len-1); 
    rand2 = randint(0, len-1); 
    temp = a[rand1];           
    a[rand1] = a[rand2];       
    a[rand2] = temp;
  }
}

int randint(int lower, int upper){
  return rand() % (upper - lower + 1) + lower;
}

int is_prime(int n){
  int i = 0;
  for(i = 2; i <= n/2; i++){
    if (n % i == 0)
      return 0;
  }
  return 1;
}


