#include <stdio.h> 

#include "littlelib.h"

void printprime()
{
    printf("nothing here yet\n");    
}

int main() 
{ 
    int i = 0;
  
    init_littlelib();
    
    for (i=0; i<10; i++)
        printprime();
    
    return 0; 
}
