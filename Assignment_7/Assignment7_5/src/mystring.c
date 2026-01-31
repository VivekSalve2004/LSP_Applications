#include "../include/mystring.h"

int MyStrlen(char *str) 
{
    int i = 0;
    while(str[i] != '\0') i++;
    return i;
}

void MyStrcpy(char *dest, char *src) 
{
    while((*dest++ = *src++));
}

void MyStrncpy(char *dest, char *src, int n) 
{
    int i = 0;
    for (i = 0; i < n && src[i] != '\0'; i++) 
    {
        dest[i] = src[i];
    }
    for (; i < n; i++) 
    {
        dest[i] = '\0';
    }        
}

void MyStrcat(char *dest, char *src) 
{
    while(*dest) 
    {
        dest++;
    }

    while((*dest++ = *src++));
}

int MyStrcmp(char *s1, char *s2) 
{
    while(*s1 && (*s1 == *s2)) 
    { 
        s1++; s2++; 
    }

    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

int MyStrncmp(char *s1, char *s2, int n) 
{
    while(n--) 
    {
        if(*s1 != *s2) return *(unsigned char*)s1 - *(unsigned char*)s2;
        if(*s1 == 0) break;
        s1++; s2++;
    }
    return 0;
}

void MyStrrev(char *str) 
{
    int i = 0, j = MyStrlen(str) - 1;
    while(i < j) 
    {
        char temp = str[i];
        str[i++] = str[j];
        str[j--] = temp;
    }
}

char* MyStrchr(char *str, char ch) 
{
    while(*str) 
    {
        if(*str == ch) return str;
        str++;
    }

    return (ch == '\0') ? str : (void*)0;
}