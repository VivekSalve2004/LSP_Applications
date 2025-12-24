#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<dirent.h>                  // Directory Entry
#include<sys/types.h>               // for DIR
#include<string.h>

const char *dtype_to_string(unsigned char t) 
{
    switch (t) 
    {
        case DT_REG:  return "regular file";
        case DT_DIR:  return "directory";
        case DT_LNK:  return "symlink";
        case DT_CHR:  return "char device";
        case DT_BLK:  return "block device";
        case DT_FIFO: return "FIFO";
        case DT_SOCK: return "socket";
        case DT_UNKNOWN:
        default:      return "unknown";
    }
}

void DirectoryListing(char Directory[])
{
    DIR* dp = NULL;
    struct dirent *ptr = NULL;
    dp = opendir(Directory);

    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
        return ;
    }
    else
    {
        while(ptr = readdir(dp))
        {
            if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    // use strcmp instead of directly comparing strings
            {
                continue;
            }
            else
            {
                printf("File Name : %s\t\t File Type : %s\n",ptr->d_name,dtype_to_string(ptr->d_type));
                
            }
        }
    }

    closedir(dp);
}

int main(int argc , char *argv[])
{
    int n = 0;
    if(argc != 2)
    {
        printf("Usage : %s <DirectoryPath> \n",argv[0]);     // Usage
        exit(1);
    }

    DirectoryListing(argv[1]);

    return 0;
}