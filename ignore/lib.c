#include "lib.h"
#include <stdio.h>

int init_littlelib(){
  time_t t;

  srand((unsigned) time(&t));
  return 0; 
}

int randint(int lower, int upper){

  return rand() % (upper - lower + 1) + 1;
}

int is_prime(int n){
  int i = 0;
  for(i = 2; i <= n/2; i++){
    if (n % i == 0)
      return 0;
  }
  return 1;
}


