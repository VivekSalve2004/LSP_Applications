#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<sys/sysmacros.h>
#include<stdint.h>
#include<stdlib.h>

void FileNameStat(char FileName[] , struct stat *sobj)
{
    int iRet = stat(FileName , sobj);

    if(iRet != -1)
    {
        printf("Total File Size : %lu\n",sobj->st_size);
        printf("Inode number : %lu\n",sobj->st_ino);
        printf("Hard Links : %lu\n",sobj->st_nlink);
        printf("Ownership: UID=%ju  GID=%ju\n" , (uintmax_t) sobj->st_uid, (uintmax_t) sobj->st_gid);
        printf("Last file access:         %s", ctime(&sobj->st_atime));
        printf("Last file modification:   %s", ctime(&sobj->st_mtime));
        printf("File type is : %d\n",sobj->st_mode);

        printf("Permissions: ");
        printf( (S_ISDIR(sobj->st_mode)) ? "d" : "-");
        printf( (sobj->st_mode & S_IRUSR) ? "r" : "-");
        printf( (sobj->st_mode & S_IWUSR) ? "w" : "-");
        printf( (sobj->st_mode & S_IXUSR) ? "x" : "-");
        printf( (sobj->st_mode & S_IRGRP) ? "r" : "-");
        printf( (sobj->st_mode & S_IWGRP) ? "w" : "-");
        printf( (sobj->st_mode & S_IXGRP) ? "x" : "-");
        printf( (sobj->st_mode & S_IROTH) ? "r" : "-");
        printf( (sobj->st_mode & S_IWOTH) ? "w" : "-");
        printf( (sobj->st_mode & S_IXOTH) ? "x" : "-");
        printf("\n");

    }
    else
    {
        perror("Stat Failed : ");
    }
}

int main(int argc , char* argv[])
{
    char FileName[50];
    struct stat sobj;

    if(argc != 2)
    {
        printf("Usage : %s <path>\n",argv[0]);
        exit(1);
    }

    FileNameStat(argv[1],&sobj);

    return 0;
}