// gcc -fPIC -shared -o libprime.so prime.c
#include "prime.h"

int CheckPrime(int iNo) 
{
    if (iNo <= 1) return 0;

    for (int i = 2; i * i <= iNo; i++) 
    {
        if (iNo % i == 0) return 0; // Not Prime
    }

    return 1; // Prime
}