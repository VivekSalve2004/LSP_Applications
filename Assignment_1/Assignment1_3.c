#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<error.h>

void FileAccess(char FileName[],char Mode[])
{
    int amode;

    if (strcmp(Mode, "R") == 0)
    {
        amode = R_OK;
    }
    else if (strcmp(Mode, "W") == 0)
    {
        amode = W_OK;
    }
    else if (strcmp(Mode, "X") == 0)
    {
        amode = X_OK;
    }
    else 
    {
        printf("Invalid mode. Use R, W or X.\n");
        return ;
    }

    if (access(FileName, amode) == 0) 
    {
        printf("Accessible: current process has ");
        if (amode == R_OK) printf("read");
        else if (amode == W_OK) printf("write");
        else if (amode == X_OK) printf("execute");
        printf(" permission on '%s'.\n", FileName);
    } 
    else 
    {
        printf("Not accessible \n");
        if (amode == R_OK)  printf("no read permission or file missing.\n");
        if (amode == W_OK)  printf("no write permission or file missing.\n");
        if (amode == X_OK)  printf("no execute permission or file missing.\n");

        // Detailed system reason
        perror("Reason");
    }
}

int main()
{
    char FileName[50];
    char Mode[10];

    printf("Enter name of file you want to open \n");

    // Secure Input from STDIN 
    fgets(FileName,sizeof(FileName),stdin);

    // New Line Removal
    char *NewLine = strchr(FileName , '\n');

    if (NewLine) *NewLine = '\0';

    printf("Enter Mode (R/W/X) for opening the file \n");

    fgets(Mode,sizeof(Mode),stdin);

    NewLine = strchr(Mode , '\n');

    if (NewLine) *NewLine = '\0';

    FileAccess(FileName,Mode);

    return 0;
}