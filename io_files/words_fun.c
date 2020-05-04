/*
 * create.c
 *
 * Description: Create and add new words to a file
 *      Author: Michal Gruszczynski
 *        Date: 21.05.2017
 *     Version: 1.0.0
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 41


int main(int argc, char *argv[])
{
    FILE *wp;
    char words[MAX];
    
    if((wp = fopen("slowa", "a+")) == NULL)
    {
        fprintf(stdin, "Can't open file 'slowa'\n");
        exit(EXIT_FAILURE);
    }

    puts("Provide words to add them to a file.\n");
    puts("To end enter: # \n");

    while((fscanf(stdin, "%40s", words) == 1) && (words[0] != '#'))
    {
        fprintf(wp, "%s", words);
        fprintf(wp, "%s", " ");
    }

    rewind(wp);

    puts("Content of file: \n");
    while(fscanf(wp, "%s", words) == 1)
    {
        puts(words);
    }

    puts("\nDone!\n");

    if(fclose(wp) != 0)
    {
        fprintf(stderr, "Error while closing file!\n");
    }

    return 0;
}


