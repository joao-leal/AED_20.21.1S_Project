#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

i_o_name *CheckCall(int argc, char const *arg){

    int alen=0, slen=0, i=0, p, ll;
    char *sufix=NULL, *path=NULL, *output=NULL;
    i_o_name *fnames = NULL;

    fnames = (i_o_name *) malloc(sizeof(i_o_name));

    if(argc != 2)
    {
        exit(0);
    }

    alen = strlen(arg) + 1;
    
    slen = strlen(".routes") + 1;           
    if(alen < slen) exit(0);

    sufix = (char*) calloc(slen, sizeof(char));
    strcpy(sufix, ".routes");
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
    ll = alen-slen;
    path = (char*) calloc((alen-slen+1), sizeof(char));
    memcpy(path, arg, ll);
    path[alen-slen] = '\0';

    fnames->o_name = (output = OutputFile(path)); 

    free(sufix);
    free(path);

    return fnames;
}

char *OutputFile(char *path)
{   
    char *output = NULL;

    int len = strlen(path) + strlen(".bbones0") + 2;

    output = (char*) malloc(len * sizeof(char));

    strcpy(output, path);
    strcat(output, ".bbones0");
    output[len-1] = '\0';
    
    return output;
}

void WriteFile(FILE *fp, out_write *result)
{
    int i;
    Edge **mst = result->mst;

    switch (result->mode[0])
    {
    case 'A':

        fprintf(fp, "%d %d %s %d %.2lf\n", result->V, result->A, result->mode, result->E, result->tot_cst);
        for(i = 0; i < result->E; i++) fprintf(fp, "%d %d %.2lf\n", mst[i]->v, mst[i]->w, mst[i]->wt);
        fprintf(fp, "\n");
        break;
    
    case 'B':
        fprintf(fp, "%d %d %s %d %d %d %.2lf %d\n", result->V, result->A, result->mode, result->v_i, result->v_j, result->E, result->tot_cst, result->res);
        
        for(i = 0; i < result->E; i++) fprintf(fp, "%d %d %.2lf\n", mst[i]->v, mst[i]->w, mst[i]->wt);
        fprintf(fp, "\n");
        break;

    default:
        break;
    }

    return;
}
