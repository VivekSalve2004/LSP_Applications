// gcc -o client Assignment7_client_3.c -L. -ldisplay -Wl,-rpath,$(pwd)
#include <stdio.h>
#include "display.h"

int main() 
{
    char arr[100];

    printf("Enter a string: ");
    scanf("%[^\n]s", arr); // Accept string with spaces

    Display(arr);

    return 0;
}