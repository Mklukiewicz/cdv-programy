/*
 * chcount.c
 *
 * Description: Count characters in a file
 *      Author: Michal Gruszczynski
 *        Date: 15.05.2017
 *     Version: 1.0.0
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ch;
    FILE *wp;

    unsigned long counter = 0;

    if(argc!=2)
    {
        printf("Usage: %s file_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if((wp = fopen(argv[1], "r")) == NULL)
    {
        printf("Couldn't open file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while((ch = fgetc(wp)) != EOF)
    {
        fputc(ch,stdout);
        counter++;
    }
    fclose(wp);

    printf("\nFile %s contains %lu characters.\n", argv[1], counter);

    return 0;

}


