// gcc -fPIC -shared -o libdisplay.so display.c
#include <stdio.h>
#include <string.h>
#include "display.h"

void Display(char *str) 
{
    if (str == NULL) return;
    
    printf("The string is: %s\n", str);
    printf("Total characters: %ld\n", strlen(str)); 
}