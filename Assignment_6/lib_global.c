// Compile: gcc -fPIC -shared -o lib_global.so lib_global.c
#include <stdio.h>

int counter = 0; // Global variable

void Modify(int val) 
{ 
    counter += val;
}

void Display() 
{ 
    printf("Current Global Value: %d\n", counter);
}

void Reset() 
{ 
    counter = 0; 
}