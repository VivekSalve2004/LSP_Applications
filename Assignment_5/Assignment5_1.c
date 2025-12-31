#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define size 1024

void mode_to_string(mode_t mode, char buf[]) 
{
    // File type indicator
    if (S_ISREG(mode)) buf[0] = '-';
    else if (S_ISDIR(mode)) buf[0] = 'd';
    else if (S_ISLNK(mode)) buf[0] = 'l';
    else if (S_ISCHR(mode)) buf[0] = 'c';
    else if (S_ISBLK(mode)) buf[0] = 'b';
    else if (S_ISFIFO(mode)) buf[0] = 'p';
    else if (S_ISSOCK(mode)) buf[0] = 's';
    else buf[0] = '?';

    // User permissions
    buf[1] = (mode & S_IRUSR) ? 'r' : '-';
    buf[2] = (mode & S_IWUSR) ? 'w' : '-';
    buf[3] = (mode & S_IXUSR) ? 'x' : '-';
    
    // Group permissions
    buf[4] = (mode & S_IRGRP) ? 'r' : '-';
    buf[5] = (mode & S_IWGRP) ? 'w' : '-';
    buf[6] = (mode & S_IXGRP) ? 'x' : '-';
    
    // Other permissions
    buf[7] = (mode & S_IROTH) ? 'r' : '-';
    buf[8] = (mode & S_IWOTH) ? 'w' : '-';
    buf[9] = (mode & S_IXOTH) ? 'x' : '-';
    
    buf[10] = '\0';
}

void build_full_path(char dir[] , char name[] , char fullpath[])
{
    size_t dir_len = strlen(dir);
    if (dir_len > 0 && dir[dir_len-1] != '/') 
    {
        snprintf(fullpath, size, "%s/%s", dir, name);
    } 
    else 
    {
        snprintf(fullpath, size, "%s%s", dir, name);
    }
}

char* dtype_to_string(unsigned char dt) 
{
    switch (dt) 
    {
        case DT_REG: return "file";
        case DT_DIR: return "dir";
        case DT_LNK: return "link";
        default:     return "other";
    }
}

void get_mod_time(time_t mtime, char timestr[]) 
{
    struct tm* mtm = localtime(&mtime);
    strftime(timestr, 64, "%Y-%m-%d %H:%M:%S", mtm);
}

int main(int argc , char *argv[])
{
    DIR* dp = NULL;
    struct dirent *ptr = NULL;
    
    if(argc != 2)
    {
        printf("Usage : %s ./<FullDirectoryPath> \n",argv[0]);
        exit(1);
    }

    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        perror("opendir");
        return -1;
    }

    while(ptr = readdir(dp))
    {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }
        else
        {
            // Building full path using helper function
            char fullpath[size];
            build_full_path(argv[1] , ptr->d_name , fullpath);

            // Get file stats
            struct stat st;
            if (lstat(fullpath, &st) == -1) 
            {
                perror("lstat");
                continue;
            }

            // Format all attributes using helper functions
            char perm[11];
            mode_to_string(st.st_mode, perm);

            char timestr[64];
            get_mod_time(st.st_mtime, timestr);

            char* type = dtype_to_string(ptr->d_type);

            // Print in required format: name type size permissions time
            printf("%s  %s  %ld  %s  %s\n" , ptr->d_name, type, (long)st.st_size, perm, timestr);

        }
    }
    //close directory
    closedir(dp);

    return 0;
}