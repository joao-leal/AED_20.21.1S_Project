#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

int CheckCall(int argc, char const *arg){

    int len, i, p;
    char sufix[9] = ".routes0";

    if(argc != 2)
    {
        if(fprintf(stderr, "ERROR: Input file not given!\n"))
        return -1;
    }

    len = strlen(arg);
    i = strlen(sufix);
    
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


