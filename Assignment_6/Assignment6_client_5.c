#include <stdio.h>
#include <dlfcn.h>

int main() 
{
    void *handle1 = NULL;
    void *handle2 = NULL; 
    char libPath[] = "./Assignment6_server_1.so";

    // 1. Load using RTLD_LAZY
    handle1 = dlopen(libPath, RTLD_LAZY);
    if (!handle1) 
    {
        fprintf(stderr, "Lazy Load Error: %s\n", dlerror());
    } 
    else 
    {
        printf("Successfully loaded with RTLD_LAZY. Handle: %p\n", handle1);
    }

    // 2. Load using RTLD_NOW
    handle2 = dlopen(libPath, RTLD_NOW);
    if (!handle2) 
    {
        fprintf(stderr, "Now Load Error: %s\n", dlerror());
    } 
    else 
    {
        printf("Successfully loaded with RTLD_NOW.  Handle: %p\n", handle2);
    }

    if (handle1) dlclose(handle1);
    if (handle2) dlclose(handle2);

    return 0;
}