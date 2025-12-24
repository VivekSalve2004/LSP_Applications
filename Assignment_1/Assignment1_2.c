#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<error.h>

void OpenMode(char FileName[],char Mode[])
{
    int fd = 0;
    if(strcmp(Mode,"R") == 0)
    {
        fd = open(FileName , O_RDONLY);
    }
    else if(strcmp(Mode,"W") == 0)
    {
        fd = open(FileName , O_WRONLY | O_CREAT | O_TRUNC, 0777);
    }
    else if(strcmp(Mode, "RW") == 0)
    {
        fd = open(FileName , O_RDWR | O_CREAT, 0777);
    }
    else if(strcmp(Mode, "A") == 0)
    {
        fd = open(FileName , O_WRONLY | O_APPEND | O_CREAT, 0777);
    }
    else
    {
        printf("Invalid mode %s\n",Mode);
        return ;
    }

    if(fd == -1)    // error code 
    {
        perror("File open failed");
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
    char Mode[10];
    memset(FileName,'\0',sizeof(FileName));
    memset(Mode,'\0',sizeof(Mode));

    printf("Enter name of file you want to open \n");

    // Secure Input from STDIN 
    fgets(FileName,sizeof(FileName),stdin);

    // New Line Removal
    char *NewLine = strchr(FileName , '\n');

    if (NewLine) *NewLine = '\0';

    printf("Enter Mode (R , W , RW , A) for opening the file \n");

    fgets(Mode,sizeof(Mode),stdin);

    NewLine = strchr(Mode , '\n');

    if (NewLine) *NewLine = '\0';

    OpenMode(FileName,Mode);

    return 0;
}