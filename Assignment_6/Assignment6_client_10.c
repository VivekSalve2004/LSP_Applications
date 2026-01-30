// gcc Assignment6_client_10.c -o client_1 -ldl
// ./client_1 ./Assignment6_server_1.so Addition
// SUCCESS: Symbol 'Addition' found at address: 0x7c14c520c0f9

#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        printf("Usage: %s <library_path> <symbol_name>\n", argv[0]);
        return -1;
    }

    // Accepting arguments from command line
    void *handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) 
    {
        printf("Error: Could not load library '%s'. %s\n", argv[1], dlerror());
        return -1;
    }

    // Checking symbol existence
    void *symbol_addr = dlsym(handle, argv[2]);
    char *err = dlerror();

    if (err != NULL) 
    {
        printf("Symbol '%s' NOT found in '%s'.\n", argv[2], argv[1]);
    } 
    else 
    {
        printf("SUCCESS: Symbol '%s' found at address: %p\n", argv[2], symbol_addr);
    }

    dlclose(handle);

    return 0;
}