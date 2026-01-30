// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./my_libs
// ./client_1
#include <stdio.h>
#include <dlfcn.h>
  
int main() 
{
    void *handle = NULL;

    handle = dlopen("Assignment6_server_1.so", RTLD_LAZY);

    if (handle == NULL) 
    {
        printf("FAILED: Unable to find/load library.\n");
        printf("System Error: %s\n", dlerror());
        return -1;
    }

    printf("SUCCESS: Library found and loaded at %p\n", handle);
    dlclose(handle);
    
    return 0;
}