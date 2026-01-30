#include <stdio.h>
#include <dlfcn.h>

int main() 
{
    char str[100];
    void *h = dlopen("./libString.so", RTLD_LAZY);
    int (*f)(char*);

    printf("Enter a string: ");
    scanf("%[^\n]s", str);

    f = dlsym(h, "CountLower");
    printf("Lowercase: %d\n", f(str));

    f = dlsym(h, "CountUpper");
    printf("Uppercase: %d\n", f(str));

    f = dlsym(h, "CountDigits");
    printf("Digits:    %d\n", f(str));

    dlclose(h);

    return 0;
}


/*

nm -D lib_global.so
0000000000004014 B counter
                 w __cxa_finalize@GLIBC_2.2.5
000000000000113e T Display
                 w __gmon_start__
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000001119 T Modify
                 U printf@GLIBC_2.2.5
0000000000001168 T Reset


*/
