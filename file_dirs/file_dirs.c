#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    int i = 0;
    struct stat buf;
    char *ptr;
    int mode;
    char perm[] = "---------";

    DIR *d;
    struct dirent *dir;

    for(i = 1; i < argc; i++)
    {
        printf("%s : ", argv[i]);
        if(lstat(argv[i], &buf) == -1)
        {
            printf("Error file: %s\n", argv[i]);
            continue;
        }
        if(S_ISREG(buf.st_mode)) {
            ptr = "regular";
        } else if(S_ISDIR(buf.st_mode)) {
            ptr = "directory";
        } else {
            ptr = "** other type or unknown **";
        }

        printf("%s\n", ptr);

        if(buf.st_mode & S_IRUSR) perm[0] = 'r';
        if(buf.st_mode & S_IWUSR) perm[1] = 'w';
        if(buf.st_mode & S_IXUSR) perm[2] = 'x';

        if(buf.st_mode & S_IRGRP) perm[3] = 'r';
        if(buf.st_mode & S_IWGRP) perm[4] = 'w';
        if(buf.st_mode & S_IXGRP) perm[5] = 'x';

        if(buf.st_mode & S_IROTH) perm[6] = 'r';
        if(buf.st_mode & S_IWOTH) perm[7] = 'w';
        if(buf.st_mode & S_IXOTH) perm[8] = 'x';


        printf("\t%s\n", perm);
        printf("\tSize: %d\n", (int) buf.st_size);
    }

    printf("\n\nListing files:\n");

    d = opendir("/etc");
    if(d != NULL) {
        while((dir = readdir(d)) != NULL) 
        {
            //printf("\t%s\n", dir->d_name);
            if(dir->d_type == DT_DIR) {
                printf("\t%s\n", dir->d_name);
            }
        }
        closedir(d);
    } else {
        printf("Open dir error\n");
    }

    printf("\n\n\nChange mode of 'test.txt' file: ");
    if(stat("test.txt", &buf) == -1) {
        printf("Error opening file\n\n");
    } else
    {
        if(chmod("test.txt", (buf.st_mode | S_IRGRP | S_IWGRP | S_IXGRP)) == -1)
        {
            printf("Chmod error\n\n");
        }
    }
    
    printf("\n\nCreate a directory:\n");
    if(mkdir("test_dir", (S_IRUSR | S_IWUSR | S_IXUSR | S_IXGRP | S_IXOTH)) == -1) {
        printf("Error creating a directory\n");
    }
    
    return 0;
}
