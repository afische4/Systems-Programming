# C - Compiling & Linking Part 2

Today you will write littlelib from D16!  Here is a completed D16 from last time:

    #include <stdio.h> 

    #include "littlelib.h"

    void printprime()
    {
        int lower = 5, upper = 800, r, b;
        
        r = randint(lower, upper);
        b = is_prime(r);
        
        if (b)
            printf("%d is prime\n", r);
        else
            printf("%d is not prime\n", r);    
    }

    int main() 
    { 
        int i = 0;
    
        init_littlelib();
        
        for (i=0; i<10; i++)
            printprime();
        
        return 0; 
    }

I renamed the file to d17.c and provided it for you with this README.

Note that printprime() uses the functions provided by littlelib.  But all I gave you was littlelib.h and littlelib.so.  And littlelib.h is just:

    int init_littlelib();
    int randint(int lower, int upper);
    int is_prime(int n);

These are just the definitions of the functions.  The function signatures.  The function implementation is in another file called littlelib.c, which I didn't provide.  I just gave you the shared object (.so) library file, which was sufficient for you to compile and run your program.

Remember: when you compiled d16.c, you really just compiled d16.c into d16.o.  Then the d16.o was linked with littlelib.so and made into an executable that the operating system could actually use.  You didn't need the source code in littlelib.c because you already had the compiled object code.  The linker's job was to put them together.

Now create a library by writing littlelib.c and compiling your own shared object library file.  To get started, remember that your library will need to implement the three functions defined in the .h file.

# Compiling

Remember from class that you generate shared libraries like so:

    $ gcc -fPIC -shared littlelib.c -o liblittlelib.so
    
And compile programs with them like this:

    $ gcc -Wall -o d17 d17.c -llittlelib -L.

# Testing

I provide a test script for you, as before:

    $ bash d17test.sh 
    Testing  ...
    Sample 1, 5 points             ... Success
    Time: 0 seconds (max allowed=5)
    Score: 5 / 5

Be sure to actually *read* this test script.  You'll see that it compiles your library as a shared object file, and then compiles the d17.c program.  I will use the d17.c file shown above when testing your program, so be sure not to change it.  Your library must work with the d17.c file as provided.
