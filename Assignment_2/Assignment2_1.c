#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

#define size 1024

void ReadEntireFile(char FileName[],char Buff[],long n)
{
    int fd = open(FileName,O_RDONLY);    // open system call with commandline arguments
    if(fd == -1)
    {
        perror("open ");
        return ;
    }

    while((n = read(fd,Buff,size)) > 0)
    {
        write(1,Buff,n);    // write exactly n bytes to stdout
        printf("\n");
        printf("No of Bytes Read are : %ld\n",n);
    }

    // Closing File descriptor
    close(fd);
}

int main(int argc , char *argv[])
{
    
    char Buff[size];    // Buffer bucket to read 1024 bytes at a time from file
    long n = 0;

    if(argc != 2)
    {
        printf("Usage : %s <FilePath> \n",argv[0]);     // Usage
        exit(1);
    }

    ReadEntireFile(argv[1],Buff,n);

    return 0;
}