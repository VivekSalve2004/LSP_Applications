// gcc -o client Assignment7_client_2.c -L. -laddition -lsubstraction
// LD_LIBRARY_PATH=. ./client
#include <stdio.h>

// Function prototypes from the libraries
int Addition(int, int);
int Substraction(int, int);

int main() 
{
    int value1, value2;
    
    printf("Enter two numbers: ");
    scanf("%d %d", &value1, &value2);

    printf("Addition: %d\n", Addition(value1, value2));
    printf("Substraction: %d\n", Substraction(value1, value2));

    return 0;
}