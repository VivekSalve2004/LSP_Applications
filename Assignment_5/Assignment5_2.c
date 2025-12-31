#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define PATH_MAX_LEN PATH_MAX

// Get file type 
char get_type_marker(struct dirent *entry, const char fullpath[]) 
{
    if (entry->d_type == DT_DIR) return 'D';
    if (entry->d_type == DT_REG) return 'F';
    if (entry->d_type == DT_LNK) return 'L';
    return '?';
}

// Check if entry is a directory (avoid symlink dirs)
int is_directory(char fullpath[]) 
{
    struct stat st;
    if (lstat(fullpath, &st) == -1) return 0;
    return S_ISDIR(st.st_mode) && !S_ISLNK(st.st_mode);  // Don't follow symlink dirs
}

// Print indentation based on recursion depth
void print_indent(int depth) 
{
    for (int i = 0; i < depth; i++) 
    {
        printf("│   ");
    }
}

// Print tree branch connector
void print_branch(int depth, int is_last) 
{
    print_indent(depth);
    if (is_last) 
    {
        printf("└── ");
    } 
    else 
    {
        printf("├── ");
    }
}

// Print single directory entry with type marker
void print_entry(int depth, int is_last, char name[], char type) 
{
    print_branch(depth, is_last);
    printf("[%c] %s\n", type, name);
}

// Recursively traverse directory tree (core logic)
int traverse_directory(char dirpath[], int depth) 
{
    DIR *dp = opendir(dirpath);
    if (dp == NULL) 
    {
        print_indent(depth);
        printf("[?] Cannot open: %s\n", dirpath);
        return -1;
    }

    struct dirent *entry;
    int entry_count = 0;
    
    // count non-hidden entries (skip . and ..)
    while ((entry = readdir(dp)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        
        entry_count++;
    }
    rewinddir(dp);

    int printed_count = 0;
    while ((entry = readdir(dp)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (entry->d_name[0] == '.') continue;

        char fullpath[PATH_MAX_LEN];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, entry->d_name);
        
        char type = get_type_marker(entry, fullpath);
        print_entry(depth, ++printed_count == entry_count, entry->d_name, type);

        if (type == 'D' && is_directory(fullpath)) 
        {
            traverse_directory(fullpath, depth + 1);
        }
    }

    closedir(dp);
    return 0;
}

// Main function
int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);
    }

    char dirpath[PATH_MAX_LEN];
    if (realpath(argv[1], dirpath) == NULL) 
    {
        perror("realpath");
        exit(1);
    }

    printf("[D] %s\n", dirpath);
    traverse_directory(dirpath, 0);

    return 0;
}
