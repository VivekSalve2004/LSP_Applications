#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h> 
#include<dirent.h>                  // Directory Entry
#include<sys/types.h>  
#include<errno.h>
#include<string.h>

#define size 1024

void DeleteEmptyRegular(char Directory[])
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    int DeleteCount = 0;
    char path[size];

    dp = opendir(Directory);

    if(dp == NULL)
    {
        printf("Error opening Directory: %s\n", strerror(errno));
        return;
    }

    while(ptr = readdir(dp))
    {
        if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
        {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", Directory, ptr->d_name);

        if(stat(path , &sobj) == -1)
        {
            continue;
        }
        if(!S_ISREG(sobj.st_mode))
        {
            continue;
        }
        if(sobj.st_size == 0)    
        {
            if(unlink(path) == 0)
            {
                printf("Deleted File : %s \n",ptr->d_name);
                printf("File Size : %ld bytes\n",sobj.st_size);
                DeleteCount++;
            }
            else
            {
                perror("unlink");
            }   
        }
    }
    printf("Count of Deleted Files is %d\n",DeleteCount);
    closedir(dp);
}

int main(int argc , char*argv[])
{
    if(argc != 2)
    {
        printf("Usage : %s <DirectoryPath> \n",argv[0]);     // Usage
        exit(1);
    }

    DeleteEmptyRegular(argv[1]);

    return 0;
}