#include "lib.h"
#include <stdio.h>

void printprime();

int main(void) 
{ 
    int i = 0;
  
    init_littlelib();
    
    for (i=0; i<10; i++)
        printprime();
    
    return 0; 
}

void printprime()
{
    int num, yn;

    num = randint(5,800);
    yn = is_prime(num);
    if (yn)
      printf("%d is prime\n", num);
    else
      printf("%d is not prime\n", num);
} 
