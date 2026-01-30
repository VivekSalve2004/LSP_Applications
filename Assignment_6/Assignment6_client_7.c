#include <stdio.h>
#include <dlfcn.h>

int main() 
{
    void *handle = dlopen("./lib_global.so", RTLD_LAZY);
    void (*Modify)(int) = dlsym(handle, "Modify");
    void (*Display)() = dlsym(handle, "Display");
    void (*Reset)() = dlsym(handle, "Reset");

    printf("--- Demonstrating Persistence ---\n");
    Display();      // Initial 0
    Modify(50);     // Change to 50
    Display();      // Shows 50
    Modify(25);     // Adds 25
    Display();      // Shows 75 (Persistence confirmed)
    Reset();
    Display();      // Back to 0

    dlclose(handle);
    
    return 0;
}