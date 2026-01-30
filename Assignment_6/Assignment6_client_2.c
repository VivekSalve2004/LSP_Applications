// gcc Assignment6_client_1.c -o client_1 -ldl
// ./client_1
#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>

void DynamicLinking(void *handle , int iRet , int (*fp) (int,int))
{
    char * error;

    fp = (int (*) (int , int)) dlsym(handle , "Addition");      // Type casting

    if ((error = dlerror()) != NULL)  
    {
        fprintf(stderr, "Error locating 'Addition': %s\n", error);
        dlclose(handle);
        return;
    }

    iRet = fp(11,10);
    printf("Addition is : %d\n",iRet);

    fp = (int (*) (int , int)) dlsym(handle , "Substraction");      // Type casting

    if ((error = dlerror()) != NULL) 
    {
        fprintf(stderr, "Error locating 'Substraction': %s\n", error);
        dlclose(handle);
        return;
    }

    iRet = fp(11,10);

    printf("Substraction is : %d\n",iRet);

    dlclose(handle);
}

int main()
{
    void * handle = NULL;
    int (*fp) (int,int);        // Function pointer
    int iRet = 0;

    handle = dlopen("./Assignment6_server_1.so" , RTLD_LAZY);

    if(handle == NULL)
    {
        printf("Unable to load library %s\n",dlerror());
        return -1;
    }

    printf("Library gets loaded successfully \n");

    DynamicLinking(handle , iRet , fp);

    return 0;
}