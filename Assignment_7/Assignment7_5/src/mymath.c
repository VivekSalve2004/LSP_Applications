#include "../include/mymath.h"

double MyPow(double base, int exp) 
{
    double res = 1.0;
    int p = (exp < 0) ? -exp : exp;
    for(int i = 0; i < p; i++) res *= base;
    return (exp < 0) ? 1.0/res : res;
}

double MySqrt(double n) 
{
    if(n < 0) return -1;
    double x = n, y = 1.0, e = 0.000001;
    while(x - y > e) 
    {
        x = (x + y) / 2;
        y = n / x;
    }
    
    return x;
}

int MyAbs(int n) 
{ 
    return (n < 0) ? -n : n; 
}

int MyMax(int a, int b) 
{ 
    return (a > b) ? a : b; 
}

int MyMin(int a, int b) 
{ 
    return (a < b) ? a : b; 
}

long MyFactorial(int n) 
{
    if (n < 0) return 0;
    long res = 1;
    for(int i = 2; i <= n; i++) 
    {
        res *= i;
    }
    return res;
}

int MyGCD(int a, int b) 
{
    while(b) 
    {
        a %= b; int t = a; a = b; b = t; 
    }

    return a;
}

int MyLCM(int a, int b) 
{
    if(a == 0 || b == 0) return 0;
    int gcd = MyGCD(a, b);
    return MyAbs(a * b) / gcd;
}