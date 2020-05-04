/*
 * lseek_hole.c
 *
 * Description: Create file with "holes" 
 *      Author: Michal Gruszczynski
 *        Date: 14-Apr-2018
 *     Version: 1.0.0
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char buf1[] = "abcdefghij";
    char buf2[] = "ABCDEFGHIJ";

    int fd, openFlags;
    
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    
    fd = open("file.hole", openFlags, 0644);
    if(fd == -1) {
        perror("create");
        return 1;
    }

    // Write our first buffer to file
    if(write(fd, buf1, 10) != 10) {
        perror("write");
    }

    // Go away after the end of file
    // After this operation, offset is 16384
    if(lseek(fd, 163840000000, SEEK_SET) == -1) {
        perror("lseek");
    }

    // offset will be 16394
    if(write(fd, buf2, 10) != 10) {
        perror("write2");
    }

    return 0;
}


