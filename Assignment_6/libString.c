// gcc -fPIC -shared -o libString.so libString.c

#include <ctype.h>

int CountLower(char *s) 
{
    int c = 0;
    while (*s) 
    { 
        if(islower(*s++)) 
        c++; 
    }
    return c;
}

int CountUpper(char *s) 
{
    int c = 0;
    while (*s) 
    { 
        if(isupper(*s++)) 
        c++; 
    }
    return c;
}

int CountDigits(char *s) 
{
    int c = 0;
    while (*s) 
    { 
        if(isdigit(*s++)) 
        c++; 
    }
    return c;
}