#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h> 

#define size 1024

void CopyFileContent(char Source[],char Dest[],char Buff[],long n)
{
    int fd1 = open(Source,O_RDONLY);    // open system call with commandline arguments

    if(fd1 == -1)
    {
        perror("open source");
        return ;
    }

    struct stat st;
    if(fstat(fd1,&st) == -1)
    {
        perror("fstat");
        close(fd1);
        return;
    }

    int fd2 = open(Dest , O_WRONLY | O_CREAT | O_TRUNC , 0600);

    if (fd2 == -1) 
    {
        perror("open dest");
        close(fd1);
        return;
    }


    while((n = read(fd1,Buff,size)) > 0)
    {
        if(write(fd2,Buff,n) != n)      // write exactly n bytes to destination file
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

    if (fchmod(fd2, st.st_mode & 07777) == -1) 
    {   
        perror("fchmod");
    }

    // Closing File descriptor
    close(fd1);
    close(fd2);
}

int main(int argc , char *argv[])
{
    
    char Buff[size];    // Buffer bucket to read 1024 bytes at a time from file
    long n = 0;

    if(argc != 3)
    {
        printf("Usage : %s <SourceFilePath> <DestinationFilePath>\n",argv[0]);     // Usage
        exit(1);
    }

    CopyFileContent(argv[1],argv[2],Buff,n);

    return 0;
}