#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char **argv)
{    
        if(argc<3)
            return 1;
 
        int n, len=256;
        char *s = argv[2];
        
        char *buf = malloc(len * sizeof(char));
        
        FILE *fp = fopen(argv[1], "r");
        
        n = readline(fp, buf, len);
        while (n!=-1)
        {
            printf("%d\t%s\n", levenshtein(s, strlen(s), buf, n), buf);
            n = readline(fp, buf, len);
        }
        
        fclose(fp);
            
        return 0;
}
