// gcc Assignment6_client_1.c -o client_1 -ldl
// ./client_1
#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>

void DynamicLinking(void *handle , int iRet , int (*fp) (int,int))
{
    char *error;
    fp = (int (*) (int , int)) dlsym(handle , "Addition");      // Type casting

    if((error = dlerror()) != NULL)
    {
        printf("Unable to get address of function %s \n",error);
        dlclose(handle);
        return ;
    }
    else
    {
        iRet = fp(11,10);
        printf("Addition is : %d\n",iRet);      
    }
    
    printf("\nAttempting to call a non-existent function...\n");
    fp = (int (*)(int, int)) dlsym(handle, "NonExistentFunction");

    error = dlerror();
    if (error != NULL) 
    {
        printf("Handle Error via dlerror(): %s\n", error);
    } 
    else 
    {
        iRet = fp(11, 10);
        printf("Result: %d\n", iRet);
    }

    dlclose(handle);
}

int main()
{
    void * handle = NULL;
    int (*fp) (int,int);        // Function pointer
    int iRet = 0;
    char *error;
    dlerror();

    handle = dlopen("./Assignment6_server_1.so" , RTLD_LAZY);

    if(handle == NULL)
    {
        fprintf(stderr, "Library Load Error: %s\n", dlerror());
        return -1;
    }

    printf("Library gets loaded successfully at address : %p \n",handle);

    DynamicLinking(handle , iRet , fp);

    return 0;
}