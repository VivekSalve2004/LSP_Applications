#ifndef MYSTRING_H
#define MYSTRING_H

int MyStrlen(char *str);
void MyStrcpy(char *dest, char *src);
void MyStrncpy(char *dest, char *src, int n);
void MyStrcat(char *dest, char *src);
int MyStrcmp(char *s1, char *s2);
int MyStrncmp(char *s1, char *s2, int n);
void MyStrrev(char *str);
char* MyStrchr(char *str, char ch);

#endif