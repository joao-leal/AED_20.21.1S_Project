#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

FILE *CheckCall(int argc, char const *arg){

    int len=0, i=0, p;
    char *sufix=NULL, *name=NULL;
    FILE *input;

    if(argc != 2)
    {
        if(fprintf(stderr, "ERROR: Input file not given!\n"))
        exit(0);
    }

    len = strlen(arg);
    printf("%d\n", len);
    
    i = strlen(".routes0");
    sufix = (char*) calloc(i+2, sizeof(char));
    strcpy(sufix, ".routes0");
    sufix[i+1] = '\0';
    printf("%d\n", i);

    name = (char*) calloc((len-i+1), sizeof(char));
    strncpy(name, arg, len-i+1);
    name[len-i+1] = '\0';

    printf("%s\n", name);

    
    for(p = len; i+2 > 0; i--, p--)
    {
        printf("%c %c\n", arg[p-1], sufix[i-1]);
        if( arg[p-1] != sufix[i-1] )
        {
            free(name);
            exit(0);  
        } 
    }   

    input = fopen(name, "r");


    return input;
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


