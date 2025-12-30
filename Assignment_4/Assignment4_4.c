#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h> 

#define size 1024

void MergeFiles(char OutPutFile[],char Buff[],long n,int iCount,char *InputFiles[])
{
    int fd2 = 0;
    struct stat st;

    int fd1 = open(OutPutFile, O_WRONLY | O_CREAT | O_TRUNC , 0777);    // open system call with commandline arguments
    if(fd1 == -1)
    {
        perror("open output");
        return ;
    }

    // Merge each input file 
    for(int iCnt = 0;iCnt < iCount ; iCnt++)
    {
        fd2 = open(InputFiles[iCnt] , O_RDONLY);
        if(fd2 == -1)
        {
            perror("open input");
            close(fd1);
            return;
        }

        while((n = read(fd2,Buff,size)) > 0)
        {
            if(write(fd1,Buff,n) != n)      // write exactly n bytes to Output file
            {
                perror("write");
                close(fd1);
                close(fd2);
                return;
            }    
        }

        if(n<0)
        {
            perror("read");
        }

        if(fstat(fd2 , &st) != -1)
        {
            fchmod(fd1 , st.st_mode);
        }
        
        close(fd2);
    }    
    close(fd1);
}

int main(int argc , char *argv[])
{
    
    char Buff[size];    // Buffer bucket to read 1024 bytes at a time from file
    long n = 0;

    if(argc < 3)
    {
        printf("Usage : %s <OutPutFile> <InputFile1> <InputFile2> ... \n",argv[0]);     // Usage
        exit(1);
    }

    // Pass input files as array (skipping argv[0] and argv[1])
    MergeFiles(argv[1],Buff,n , argc - 2 , &argv[2]);

    return 0;
}