#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

void ReadN(char FileName[],char Bytes[],char Buffer[])
{
    int fd = open(FileName , O_RDONLY);     // open System call

    if(fd < 0)
    {
        printf("Unable to open the file\n");
        printf("Reason  : %s\n",strerror(errno));   
        return ;
    }
    else
    {
        printf("File succesfully opened with fd : %d\n",fd);
        int iRet = read(fd , Buffer , atoi(Bytes));             // read system call
        printf("%d bytes gets read from file %s\n",iRet,FileName);
        printf("Data from file : %s\n",Buffer);
    }

    // fd close
    close(fd);
}

int main(int argc, char*argv[])
{
    char FileName[50];
    char Buffer[100];       // Buffer to read data from file
    memset(Buffer,'\0',sizeof(Buffer));

    if(argc != 3)
    {
        printf("Usage : %s <path> <No of Bytes to Read> \n",argv[0]);   // CommandLine arguments usage
        exit(1);
    }

    ReadN(argv[1] , argv[2] , Buffer);

    return 0;
}