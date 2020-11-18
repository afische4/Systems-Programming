#include "littlelib.h"
#include "time.h"
#include <stdio.h>

int init_littlelib(){
  int seed = 1337;
  srand(seed);
  return 0; 
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


