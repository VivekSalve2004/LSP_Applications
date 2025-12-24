#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<dirent.h>                  // Directory Entry
#include<sys/types.h>               // for DIR
#include<string.h>

void DirectoryListing(char Directory[])
{
    DIR* dp = NULL;
    struct dirent *ptr = NULL;
    dp = opendir(Directory);

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
                printf("%s\n",ptr->d_name);
            }
        }
    }

    closedir(dp);
}

int main(int argc , char *argv[])
{
    int n = 0;
    if(argc != 2)
    {
        printf("Usage : %s <DirectoryPath> \n",argv[0]);     // Usage
        exit(1);
    }

    DirectoryListing(argv[1]);

    return 0;
}