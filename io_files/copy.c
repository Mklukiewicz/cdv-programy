#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 8192


int main(int argc, char *argv[])
{
    int input_fd, output_fd;    // fd of files
    ssize_t ret_in, ret_out;    // No of bytes returend by read/write
    char buffer[BUF_SIZE];      // Char buffer

    if(argc != 3 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: copy file_origin file_destinationi\n");
        return 1;
    }

    // Open file for reading
    input_fd = open(argv[1], O_RDONLY);
    if(input_fd == -1) {
        perror("open");
        return 1;
    }

    // Create file for writing
    output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if(output_fd == -1) {
        perror("create");
        return 1;
    }

    // Copy
    while((ret_in = read(input_fd, &buffer, BUF_SIZE)) > 0) {
        ret_out = write(output_fd, &buffer, (ssize_t) ret_in);
        if(ret_out != ret_in) {
            perror("write");
            return 2;
        }
    }

    close(input_fd);
    close(output_fd);

    return 0;

}


