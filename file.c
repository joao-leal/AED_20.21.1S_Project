#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

i_o_name *CheckCall(int argc, char const *arg){

    int alen=0, slen=0, i=0, p;
    char *sufix=NULL, *path=NULL, *output=NULL;
    i_o_name *fnames = NULL;

    fnames = (i_o_name *) malloc(sizeof(i_o_name));

    if(argc != 2)
    {
        if(fprintf(stderr, "ERROR: Input file not given!\n"))
        exit(0);
    }

    alen = strlen(arg) + 1;
    
    slen = strlen(".routes0") + 1;

    if(alen < slen) exit(0);

    sufix = (char*) calloc(slen, sizeof(char));
    strcpy(sufix, ".routes0");
    sufix[slen-1] = '\0';

    /*checks if the extension is correct and if there's nothing after it*/
    for(p = alen, i = slen; i > 0; i--, p--)
    {
        if( arg[p-1] != sufix[i-1] )
        {
            free(path);
            free(sufix);
            free(fnames);
            exit(0);  
        } 
    }   

    fnames->i_name = (char *) arg;

    path = (char*) calloc((alen-slen+1), sizeof(char));
    strncpy(path, arg, alen-slen);
    path[alen-slen] = '\0';
    printf("%s\n", path);

    fnames->o_name = (output = OutputFile(path)); 

    free(sufix);
    free(path);

    return fnames;
}

char *OutputFile(char *path)
{   
    char *output = NULL;

    int len = strlen(path) + strlen(".queries0") + 2;

    output = (char*) malloc(len * sizeof(char));

    strcpy(output, path);
    strcat(output, ".queries0");
    output[len-1] = '\0';
    
    return output;
}

void WriteFile(FILE *fp, out_write *result)
{
    /*mode B0 has route*/
    if(result->result == 0)
    {
        if(result->weight > 0) fprintf(fp, "%d %d %s %d %d %.2lf\n\n", result->V, result->A, result->mode, result->v_i, result->v_j, result->weight);
        else fprintf(fp, "%d %d %s %d %d -1\n\n", result->V, result->A, result->mode, result->v_i, result->v_j);
    } 
    else
    {
        fprintf(fp, "%d %d %s %d\n\n", result->V, result->A, result->mode, result->result);
    } 
    return;
}
