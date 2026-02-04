#include <stdio.h>
#include "math_ops.h"

int main() 
{
    int x = 20, y = 10;
    
    printf("--- Static Library Demo ---\n");
    printf("Addition:       %d\n", Add(x, y));
    printf("Subtraction:    %d\n", Sub(x, y));
    printf("Multiplication: %d\n", Mul(x, y));
    printf("Division:       %d\n", Div(x, y));
    
    return 0;
}