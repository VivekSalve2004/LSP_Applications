#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<dirent.h>                  // Directory Entry
#include<sys/types.h>               // for DIR
#include<string.h>
#include<unistd.h>

void CheckFile(char Directory[],char FileName[])
{
    DIR* dp = NULL;
    struct dirent *ptr = NULL;
    dp = opendir(Directory);
    int bFlag = 0;
    char FullPath[50];

    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
        return ;
    }
    else
    {
        while(ptr = readdir(dp))
        {
            if (strcmp(ptr->d_name, FileName) == 0)    // use strcmp instead of directly comparing strings
            {
                printf("File %s exists in Directory %s\n",FileName,Directory);
                getcwd(FullPath,sizeof(FullPath));
                printf("Full Directory Path is : %s/%s\n",FullPath,Directory);
                printf("Full File Path is : %s/%s/%s\n",FullPath,Directory,FileName);
                bFlag = 1;
            }
        }
    }
    if(bFlag == 0)
    {
       printf("File %s does not exists in Directory %s\n",FileName,Directory);
    }
    closedir(dp);
}

int main(int argc , char *argv[])
{
    int n = 0;
    if(argc != 3)
    {
        printf("Usage : %s <DirectoryPath> <FilePath>\n",argv[0]);     // Usage
        exit(1);
    }

    CheckFile(argv[1],argv[2]);

    return 0;
}