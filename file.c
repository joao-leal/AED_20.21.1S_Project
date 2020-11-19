#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

char *CheckCall(int argc, char const *arg){

    int len, i, p;
    char *sufix = NULL;

    if(argc != 2)
    {
        if(fprintf(stderr, "ERROR: Input file not given!\n"))
        exit(0);
    }

    len = strlen(arg);
    i = strlen(".routes0");

    sufix = (char*) malloc(i * sizeof(char));
    strcpy(sufix, ".routes0");
    
    for(p = len; i > 0; i--, p--)
    {
        if( arg[p] != sufix[i] ) return -1;
    }   
}

FILE *OpenFile(char * name)
{
    FILE* fp;
    
    fp= fopen(name, "r");

    return fp;
}

FILE *OutputFile(char *name)
{   
    FILE *fp;
    char *output = NULL;

    int len = strlen(name) + strlen(".queries") + 1;

    output = (char*) malloc(len * sizeof(char));

    strcat(output, name);
    strcat(output, ".queries");
    
    fp = fopen(output, "a");    
    free(output);

    return fp;
}


