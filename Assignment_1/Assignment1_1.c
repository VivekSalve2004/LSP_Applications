#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<error.h>

void OpenFile(char FileName[])
{
    int fd = 0;
    fd = open(FileName , O_RDONLY);

    if(fd == -1)    // error code 
    {
        perror("File did not open");
        return ;
    }
    else            // File open success code
    {
        printf("File opened successfully with file descriptor : %d \n" , fd);
    }

    // file descriptor closed
    close(fd);
}

int main()
{
    char FileName[50];
    memset(FileName,'\0',sizeof(FileName));

    printf("Enter name of file you want to open \n");

    // Secure Input from STDIN 
    fgets(FileName,sizeof(FileName),stdin);

    // New Line Removal
    char *NewLine = strchr(FileName , '\n');

    if (NewLine) *NewLine = '\0';

    OpenFile(FileName);
    
    return 0;
}