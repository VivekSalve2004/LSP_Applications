#include <stdio.h>
#include <dlfcn.h>

int main() 
{
    void *h = dlopen("./Assignment6_server_1.so", RTLD_LAZY);
    
    // Array of function pointers
    int (*fptr[2])(int, int);

    fptr[0] = (int (*)(int, int))dlsym(h, "Addition");
    fptr[1] = (int (*)(int, int))dlsym(h, "Substraction");

    const char* names[] = {"Addition", "Subtraction"};

    for(int i = 0; i < 2; i++) 
    {
        printf("Function: %s | Address: %p | Result: %d\n", 
                names[i], (void*)fptr[i], fptr[i](11, 10));
    }

    dlclose(h);

    return 0;
}