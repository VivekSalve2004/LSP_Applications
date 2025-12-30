#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUF_SIZE 1024

void ReverseFileContent(char filename[])
{
    int fd = 0;
    char buffer[BUF_SIZE];
    struct stat st;
    long file_size = 0, offset = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1) 
    {
        perror("open");
        return;
    }

    if (fstat(fd, &st) == -1) 
    {
        perror("fstat");
        close(fd);
        return;
    }

    file_size = st.st_size;
    
    // Read and print from end to start 
    for (offset = file_size; offset > 0; ) 
    {
        long n = pread(fd, buffer, (offset > BUF_SIZE) ? BUF_SIZE : offset , offset - ((offset > BUF_SIZE) ? BUF_SIZE : offset));
        
        if (n <= 0) 
        {
            break;
        }
        
        // Print buffer in reverse order 
        for (long i = n - 1; i >= 0; i--) 
        {
            write(STDOUT_FILENO, &buffer[i], 1);
        }
        
        offset -= n;
    }
    printf("\n");
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    ReverseFileContent(argv[1]);
    return 0;
}
