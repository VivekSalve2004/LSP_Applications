#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int WriteString(char FileName[],char str[])
{
    int fd = open(FileName,O_WRONLY | O_APPEND | O_CREAT, 0777);

    if(fd < 0)
    {
        printf("Unable to open the file\n");
        printf("Reason  : %s\n",strerror(errno));
        return -1;
    }

    long len = strlen(str);   
    long n = write(fd,str,len);

    if(n < 0)
    {
        printf("Write Failed\n");
        printf("Reason : %s\n",strerror(errno));
        close(fd);
        return -1;
    }

    close(fd);
    return (int)n;

}

int main(int argc , char *argv[])
{
    int n = 0;
    if(argc != 3)
    {
        printf("Usage : %s <FilePath> <String> \n",argv[0]);     // Usage
        exit(1);
    }

    int no = WriteString(argv[1],argv[2]);

    printf("No of Bytes written are : %d\n",no);

    return 0;
}