#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>   
#include<errno.h> 
#include <sys/stat.h> 

#define size 1024

void FindLargestFile(char DirecrtoryName[])
{
    char Buff[size];
    int MaxSize = INT_MIN;
    char ans[size];
    struct stat sobj;
    DIR* dp = NULL;
    struct dirent *ptr = NULL;
    dp = opendir(DirecrtoryName);

    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
        return ;
    }
    else
    {
        while(ptr = readdir(dp))
        {
            if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    // use strcmp instead of directly comparing strings
            {
                continue;
            }
            else
            {
                int iRet = stat(ptr->d_name , &sobj);
                if(iRet != -1)
                {
                    if(sobj.st_size > MaxSize)
                    {
                        MaxSize = sobj.st_size;
                        strcpy(ans , ptr->d_name);
                    }
                }
                else 
                {
                    perror("Stat Failed");
                    return;
                }
            }
        }
    }
    closedir(dp);
    printf("Largest: %s, size: %d\n", ans, MaxSize);
}

int main(int argc , char *argv[])
{

    if(argc != 2)
    {
        printf("Usage : %s <DirectoryPath> \n",argv[0]);     // Usage
        exit(1);
    }

    FindLargestFile(argv[1]);

    return 0;
}