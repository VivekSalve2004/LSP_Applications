#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<dirent.h>                  // Directory Entry
#include<sys/types.h>               // for DIR

void DirectoryListing(char Directory[])
{
    DIR* dp = NULL;
    dp = opendir(Directory);

    if(dp == NULL)
    {
        printf("\n");
        return ;
    }
    else
    {

    }

    closedir(Directory);
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