#include <stdio.h>
#include "helper.h"

int main() 
{
    int num1, num2, sum;

    printf("Enter two integers: ");

    if (scanf("%d %d", &num1, &num2) == 2) 
    {
        sum = add(num1, num2); 
        printf("The addition of %d and %d is: %d\n", num1, num2, sum);
    } 
    else 
    {
        printf("Error: Please enter valid integers.\n");
        return 1;
    }
    return 0;
}