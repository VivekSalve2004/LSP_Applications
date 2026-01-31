// gcc -fPIC -shared -o libperfect.so perfect.c -L. -lhelper
#include "perfect.h"
#include "helper.h"

int IsPerfect(int No) 
{
    if (No <= 0) return 0;
    // Calling helper function from libhelper.so
    
    if (SumOfFactors(No) == No) 
    {
        return 1; // It is a perfect number
    }

    return 0; // Not a perfect number
}