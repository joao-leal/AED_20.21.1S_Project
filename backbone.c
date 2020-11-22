#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "file.h"
#include "interfaces.h"

int main(int argc, char const *argv[])
{
    Graph *G = NULL;
    FILE *input, *output;
    i_o_name *fnames;
    
    
    input = fopen((fnames = (CheckCall(argc, (char*) argv[1])))->i_name, "r");
    if(input == NULL) exit(0);
    /*if the arguments are correct, CheckCall returns the name of the input file*/
    output = fopen(fnames->o_name, "a");
    if(output == NULL) exit(0);

    free(fnames->o_name);
    free(fnames);

    do
    {
        int Apts, Rts, v_i, v_j, origin, dest;
        double weight;
        char mode[3] = "";

        Apts = Rts = v_i = v_j = origin = dest = 0;
        weight += 0;

        if(fscanf(input, "%d %d %s %d", &Apts, &Rts, mode, &v_i) != 4) 
        {
            if(!strcmp(mode, "B0"))
            {
                fscanf(input, "%d", &v_j);
            }
            else exit(0);
        }
        else if (!strcmp(mode, "B0"))
        {
            fscanf(input, "%d", &v_j);
        }

        fprintf(stdout, "%d %d %s %d ", Apts, Rts, mode, v_i);
        if(!strcmp(mode, "B0")) fprintf(stdout, "%d\n", v_j);
        else fprintf(stdout, "\n");

        G = GRAPHinit(Apts, Rts);
        GRAPHpopulate(G, input);

        switch (mode[0])
        {
        case 'A':
            if(mode[1] == '0')
            {
                A0();
            }
            break;

        case 'B':
            if(mode[1] == '0')
            {
                B0(G, v_i, v_j);
            }
            break;        

        case 'C':
            if(mode[1] == '0')
            {
                C0();
            }
            break;

        case 'D':
            if(mode[1] == '0')
            {
                /*D0();*/
            }
            break;

        default:
            exit(0);
        }

    } while (feof(input));
    

    FreeGraph(G);
    fclose(input);
    fclose(output);

    return 0;
    
}



void A0()
{

}

double B0(Graph *G, int v_i, int v_j)
{
    if(v_i > v_j && G->adj[v_i][v_j] > 0) return G->adj[v_i][v_j];
    else if(G->adj[v_j][v_i] > 0) return G->adj[v_j][v_i];
    else return 0; 
}

void C0(){

}

void D0(Graph *G){

}


