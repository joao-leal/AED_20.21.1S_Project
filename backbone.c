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
    
    /*if the arguments are correct, CheckCall returns the name of the input file*/
    input = fopen((fnames = (CheckCall(argc, (char*) argv[1])))->i_name, "r");
    if(input == NULL)
    {
        free(fnames->o_name);
        free(fnames);
        exit(0);
    } 
 
    output = fopen(fnames->o_name, "a+");
    if(output == NULL)
    {
        free(fnames->o_name);
        free(fnames);
        exit(0);
    } 

    free(fnames->o_name);
    free(fnames);

    do
    {
        int Apts, Rts, v_i, v_j, origin, dest;
        char mode[3] = "";

        Apts = Rts = v_i = v_j = origin = dest = 0;

        if(fscanf(input, "%d %d %s %d", &Apts, &Rts, mode, &v_i) != 4) 
        {
            if(!strcmp(mode, "B0"))
            {
                if(fscanf(input, "%d", &v_j) != 1) exit(0);
            }
            else exit(0);
        }
        else if (!strcmp(mode, "B0"))
        {
            if(fscanf(input, "%d", &v_j) != 1) exit(0);
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
                out_write result = {Apts, Rts, mode, v_i, 0, A0(G, v_i), 0 };
                WriteFile(output, &result);
            }
            break;

        case 'B':
            if(mode[1] == '0')
            {
                out_write result = {Apts, Rts, mode, v_i, v_j, 0, B0(G, v_i, v_j)};
                WriteFile(output, &result);
                
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

    } while (!feof(input));
    

    FreeGraph(G);
    fclose(input);
    fclose(output);

    return 0;
    
}



int A0(Graph *G, int v)
{
    int i, cnt = 0;

    for(i = 0; i < G->V; i++)
    {
        if( i < v-1 && G->adj[v-1][i] > 0.0) cnt++; 
        else if(i > v-1 && G->adj[i][v-1] > 0.0) cnt++;
    }

    return cnt;
}

double B0(Graph *G, int v_i, int v_j)
{
    int x = v_i - 1, y = v_j - 1;

    if(v_i > v_j && G->adj[x][y] >= 0.0) return G->adj[x][y];
    else if(G->adj[y][x] >= 0.0) return G->adj[y][x];
    else return -1; 
}

void C0(){

}

void D0(Graph *G){

}


