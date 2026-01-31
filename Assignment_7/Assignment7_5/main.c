/*

Project/
├── include/          # Header files (.h)
│   ├── mystring.h
│   └── mymath.h
├── src/              # Implementation files (.c)
│   ├── mystring.c
│   └── mymath.c
├── main.c            # Menu-driven client
└── Makefile          # Build automation

make
gcc -Wall -fPIC -Iinclude -c src/mystring.c -o src/mystring.o
gcc -shared -o libmystring.so src/mystring.o
Built libmystring.so
gcc -Wall -fPIC -Iinclude -c src/mymath.c -o src/mymath.o
gcc -shared -o libmymath.so src/mymath.o
Built libmymath.so
gcc main.c -L. -lmystring -lmymath -Iinclude -o my_app
Successfully compiled my_app

*/

#include <stdio.h>
#include <stdlib.h>
#include "include/mystring.h"
#include "include/mymath.h"

void string_menu();
void math_menu();

void string_menu() 
{
    int choice, n;
    char s1[100], s2[100], ch;
    
    printf("\n--- String Library Test ---\n");
    printf("1. Strlen  2. Strcpy  3. Strcat\n");
    printf("4. Strcmp  5. Strrev  6. Strchr\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) 
    {
        case 1:
            printf("Enter string: ");
            scanf("%s", s1);
            printf("Length: %d\n", MyStrlen(s1));
            break;
        case 2:
            printf("Enter source string: ");
            scanf("%s", s2);
            MyStrcpy(s1, s2);
            printf("Copied string: %s\n", s1);
            break;
        case 3:
            printf("Enter first string: "); scanf("%s", s1);
            printf("Enter second string: "); scanf("%s", s2);
            MyStrcat(s1, s2);
            printf("Concatenated: %s\n", s1);
            break;
        case 4:
            printf("Enter first string: "); scanf("%s", s1);
            printf("Enter second string: "); scanf("%s", s2);
            int iRet = MyStrcmp(s1,s2);
            if(iRet == 0)   printf("Equal Strings\n");
            else            printf("Strings not equal\n");
            break;
        case 5:
            printf("Enter string to reverse: ");
            scanf("%s", s1);
            MyStrrev(s1);
            printf("Reversed: %s\n", s1);
            break;
        case 6:
            printf("Enter string: "); scanf("%s", s1);
            printf("Enter char to find: "); scanf(" %c", &ch);
            char *res = MyStrchr(s1, ch);
            printf("Found at: %s\n", res ? res : "Not Found");
            break;
        default: printf("Invalid!\n");
    }
}

void math_menu() 
{
    int choice, a, b;
    double da, db;

    printf("\n--- Math Library Test ---\n");
    printf("1. Power  2. Sqrt  3. GCD  4. Factorial  5. LCM\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) 
    {
        case 1:
            printf("Enter base and exponent: ");
            scanf("%lf %d", &da, &a);
            printf("Result: %.2f\n", MyPow(da, a));
            break;
        case 2:
            printf("Enter number: ");
            scanf("%lf", &da);
            printf("Sqrt: %.2f\n", MySqrt(da));
            break;
        case 3:
            printf("Enter two numbers: ");
            scanf("%d %d", &a, &b);
            printf("GCD: %d\n", MyGCD(a, b));
            break;
        case 4:
            printf("Enter number: ");
            scanf("%d", &a);
            printf("Factorial: %ld\n", MyFactorial(a));
            break;
        case 5:
            printf("Enter two numbers: ");
            scanf("%d %d", &a, &b);
            printf("LCM: %d\n", MyLCM(a, b));
            break;
        default: printf("Invalid!\n");
    }
}

int main() 
{
    int choice = 0;

    while (1) 
    {
        printf("\n====================================\n");
        printf("   SHARED LIBRARY INTERACTIVE TEST   \n");
        printf("====================================\n");
        printf("1. String Library Functions\n");
        printf("2. Math Library Functions\n");
        printf("0. Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: string_menu(); break;
            case 2: math_menu(); break;
            case 0: printf("Closing MyApp...\n") ; exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

