#include <stdio.h>
#include "operations.h"

int main() 
{
    int n1 = 100, n2 = 20;
    printf("--- Shared Library Application ---\n");
    printf("Result: %d + %d = %d\n", n1, n2, Add(n1, n2));
    return 0;
}