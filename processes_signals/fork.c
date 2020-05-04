#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main(void)
{
    pid_t pid; 
    pid_t ch_pid;
    int status;

    pid = fork();
    if(pid == -1)
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    if(pid == 0)
    {
        sleep(10);
        printf("I'm a child with pid: %d\n", (int) getpid());
        printf("Fork returned: %d\n", (int) pid);
        // _exit(1);
        abort();
    }
    if(pid > 0)
    {
        printf("PARENT >> I'm a parent with PID: %d\n", (int) getpid());
        printf("PARENT >> Fork returned: %d\n", (int) pid);
        ch_pid = wait(&status);
        printf("PARENT >> PID %d ended. Exit status: %d\n", (int) ch_pid, WEXITSTATUS(status));
        if(WIFEXITED(status))
        {
            printf("Normal execution\n");
        }
        if(WIFSIGNALED(status))
        {
            printf("Program signaled");
        }
    }

    return 0;
}

