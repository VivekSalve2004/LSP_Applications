// gcc -o client Assignment7_client_4.c -L. -lprime -Wl,-rpath,$(pwd)

#include <stdio.h>
#include "prime.h"

int main() 
{
    int iValue = 0;
    printf("Enter number: ");
    scanf("%d", &iValue);

    if (CheckPrime(iValue)) 
    {
        printf("%d is a Prime number\n", iValue);
    } 
    else 
    {
        printf("%d is NOT a Prime number\n", iValue);
    }

    return 0;
}