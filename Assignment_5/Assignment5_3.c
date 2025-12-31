#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define PATH_MAX_LEN PATH_MAX

// Global counters
long long total_files = 0;
long long total_dirs = 0;
long long total_size = 0;
char largest_file[PATH_MAX_LEN] = "";
long long largest_size = 0;

// Update largest file tracker
void update_largest_file(char filename[], long long size) 
{
    if (size > largest_size) 
    {
        largest_size = size;
        strncpy(largest_file, filename, PATH_MAX_LEN - 1);
        largest_file[PATH_MAX_LEN - 1] = '\0';
    }
}

// Process single regular file (S_ISREG only)
void process_file(char fullpath[] , struct stat *st) 
{
    if (S_ISREG(st->st_mode))   // Only regular files for size
    {  
        total_files++;
        total_size += st->st_size;
        update_largest_file(fullpath, st->st_size);
    }
}

// Check if path is regular directory (skip symlink dirs)
int is_traversable_dir(char fullpath[]) 
{
    struct stat st;
    if (lstat(fullpath, &st) == -1) return 0;
    return S_ISDIR(st.st_mode) && !S_ISLNK(st.st_mode);  // Ignore symlink targets
}

// Recursively traverse directory
void traverse_directory(char dirpath[]) 
{
    DIR *dp = opendir(dirpath);
    if (dp == NULL) return;

    // Counting directory when we enter it
    total_dirs++;

    struct dirent *entry;
    int entry_count = 0;
    
    // count entries
    while ((entry = readdir(dp)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        entry_count++;
    }
    rewinddir(dp);

    while((entry = readdir(dp)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[PATH_MAX_LEN];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, entry->d_name);

        struct stat st;
        if (lstat(fullpath, &st) == -1) continue;

        // Process files (symlinks treated as objects, not targets)
        process_file(fullpath, &st);

        // Recursing into directories only
        if (is_traversable_dir(fullpath)) 
        {
            traverse_directory(fullpath);
        }
    }

    closedir(dp);
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

    // Start traversal
    traverse_directory(dirpath);

    printf("No of Files: %lld\n", total_files);
    printf("No of Directories: %lld\n", total_dirs);
    printf("Total Size: %lld bytes\n", total_size);
    printf("Largest File: %s (%lld bytes)\n", largest_file, largest_size);

    return 0;
}
