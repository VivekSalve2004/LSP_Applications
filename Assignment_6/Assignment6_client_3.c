// gcc Assignment6_client_1.c -o client_1 -ldl
// ./client_1
#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>

void DynamicLinking(void *handle , int iRet , int (*fp) (int,int) , int op)
{
    char * error;

    if(op == 1)
    {
        fp = (int (*) (int , int)) dlsym(handle , "Addition");      // Type casting
        if ((error = dlerror()) != NULL)  
        {
            fprintf(stderr, "Error locating 'Addition': %s\n", error);
            dlclose(handle);
            return;
        }
        iRet = fp(11,10);
        printf("Addition is : %d\n",iRet);
    }
    else if(op == 2)
    {
        fp = (int (*) (int , int)) dlsym(handle , "Substraction");      // Type casting
        if ((error = dlerror()) != NULL) 
        {
            fprintf(stderr, "Error locating 'Substraction': %s\n", error);
            dlclose(handle);
            return;
        }
        iRet = fp(11,10);
        printf("Substraction is : %d\n",iRet);
    }
    else if(op == 3)
    {
        fp = (int (*) (int , int)) dlsym(handle , "Multiplication");      // Type casting
        if ((error = dlerror()) != NULL) 
        {
            fprintf(stderr, "Error locating 'Multiplication': %s\n", error);
            dlclose(handle);
            return;
        }
        iRet = fp(11,10);
        printf("Multiplication is : %d\n",iRet);
    }
    else if(op == 4)
    {
        fp = (int (*) (int , int)) dlsym(handle , "Division");      // Type casting
        if ((error = dlerror()) != NULL) 
        {
            fprintf(stderr, "Error locating 'Division': %s\n", error);
            dlclose(handle);
            return;
        }
        iRet = fp(11,10);
        printf("Division is : %d\n",iRet);
    }
    else
    {
        printf("Invalid Operation\n");
        dlclose(handle);
    }

    dlclose(handle);
}

int main()
{
    void * handle = NULL;
    int (*fp) (int,int);        // Function pointer
    int iRet = 0;
    int operation = -1;
    handle = dlopen("./Assignment6_server_3.so" , RTLD_LAZY);

    if(handle == NULL)
    {
        printf("Unable to load library %s\n",dlerror());
        return -1;
    }

    printf("Library gets loaded successfully \n");

    printf("What operation do you want to perform\n1.Addition\n2.Substraction\n3.Multiplication\n4.Division \n");

    scanf("%d",&operation);

    DynamicLinking(handle , iRet , fp , operation);

    return 0;
}