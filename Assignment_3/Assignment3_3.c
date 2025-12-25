#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h> 
#include<dirent.h>                  // Directory Entry
#include<sys/types.h>  
#include<errno.h>
#include<string.h>

#define size 1024

int copy_and_delete(char Source[],char Dest[])
{
    int fd1 = open(Source, O_RDONLY);
    if (fd1 == -1) 
    {
        perror("open Source");
        return -1;
    }

    int fd2 = open(Dest, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd2 == -1) 
    {
        perror("open Destination");
        close(fd1);
        return -1;
    }

    char buf[size];
    long n = 0;
    while ((n = read(fd1, buf, sizeof(buf))) > 0) 
    {
        if (write(fd2, buf, n) != n) 
        {
            perror("write");
            close(fd1);
            close(fd2);
            return -1;
        }
    }
    if (n < 0) 
    {
        perror("read");
        close(fd1);
        close(fd2);
        return -1;
    }

    close(fd1);
    close(fd2);

    if (unlink(Source) == -1)   // delete original
    {           
        perror("unlink");
        return -1;
    }
    return 0;
}

void MoveAllFiles(char Source[],char Dest[])
{
    DIR *dp = opendir(Source);
    struct dirent *ptr;
    struct stat st;
    char srcPath[size], dstPath[size];
    int moved = 0;

    if (dp == NULL) 
    {
        printf("Error opening source dir: %s\n", strerror(errno));
        return;
    }

    while ((ptr = readdir(dp)) != NULL) 
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;

        // Build full source path
        snprintf(srcPath, sizeof(srcPath), "%s/%s", Source, ptr->d_name);

        if (stat(srcPath, &st) == -1)
            continue;

        // Only regular files
        if (!S_ISREG(st.st_mode))
            continue;

        // Build destination path
        snprintf(dstPath, sizeof(dstPath), "%s/%s", Dest, ptr->d_name);

        if (rename(srcPath, dstPath) == 0) 
        {
            moved++;
        } 
        else if (errno == EXDEV) 
        {
            // Different filesystem: copy + delete
            if (copy_and_delete(srcPath, dstPath) == 0)
                moved++;
        } 
        else 
        {
            perror("rename");
        }
    }
    closedir(dp);
    printf("Total files moved: %d\n", moved);
}

int main(int argc , char *argv[])
{
    
    char Buff[size];    // Buffer bucket to read 1024 bytes at a time from file
    long n = 0;

    if(argc != 3)
    {
        printf("Usage : %s <SourceDirectoryPath> <DestinationDirectoryPath>\n",argv[0]);     // Usage
        exit(1);
    }

    MoveAllFiles(argv[1],argv[2]);

    // => ./mv demo hello

    return 0;
}