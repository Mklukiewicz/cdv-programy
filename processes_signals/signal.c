/*
 * signal.c
 *
 * Description: Singals handling
 *      Author: Michal Gruszczynski
 *        Date: 4-Jun-2017
 *     Version: 1.0.0
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static void sig_usr(int);

int main(int argc, char *argv[])
{
    if(signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
        printf("cannot catch SIGUSR1\n");
        return 1;
    }
    if(signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        printf("cannot catch SIGUSR2\n");
        return 1; 
    }

    for(;;)
        pause();
}

static void sig_usr(int signo)
{
    if(signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if(signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else
    {
        printf("received signal %d\n", signo);
    }
}

