// gcc -o client Assignment7_client_1.c -L. -lperfect -lhelper
// LD_LIBRARY_PATH=. ./client

#include <stdio.h>
#include "perfect.h"

int main() {
    int numbers[] = {28, 12};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < size; i++) 
    {
        if (IsPerfect(numbers[i])) 
        {
            printf("%d is a Perfect Number\n", numbers[i]);
        } 
        else 
        {
            printf("%d is NOT a Perfect Number\n", numbers[i]);
        }
    }

    return 0;
}