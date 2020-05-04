#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int ret; 

    printf("Before exec\n");

    ret = execl("/usr/bin/vi", "vi", "/tmp/michalg.txt", NULL);
    if(ret == -1)
    {
        fprintf(stderr, "error\n");
        return 1;
    }

    printf("After successful fork\n");

    return 0;
}