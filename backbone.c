#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "defs.h"
#include "file.h"
#include "interfaces.h"


int main(int argc, char const *argv[])
{
    Graph *A_N = NULL; /*A_N stands for Airport Network*/ 
    FILE *input, *output;
    i_o_name *fnames; /*struct with the strings for the input & output file names*/

    /*if the arguments are correct, CheckCall returns the name of the input file and stores the output file name in fnames->o_name*/
    input = fopen((fnames = (CheckCall(argc, (char*) argv[1])))->i_name, "r");
    if(input == NULL) exit(0);
 
    output = fopen(fnames->o_name, "a+");
    if(output == NULL) exit(0);

    free(fnames->o_name);
    free(fnames); 

    do
    {
        int Apts, Rts, v_i, v_j;
        char mode[3] = "";

        Apts = Rts = v_i = v_j = 0;

        if(fscanf(input, "%d %d %s", &Apts, &Rts, mode) != 3) exit(0);/*Reads the 3 first args from the header*/
        fprintf(stdout, "%d %d %s ", Apts, Rts, mode);

        A_N = GRAPHinit(Apts, Rts);

        switch (mode[0])
        {
        case 'A':
            if(mode[1] == '1')
            {
                printf("\n");
                BuildGraph(A_N, input);
                
                A1(A_N);
                out_write result;
                /*WriteFile(output, &result);*/
            }
            break;

        case 'B':
            if(mode[1] == '1')
            {
                if(fscanf(input, "%d %d\n", &v_i, &v_j) != 2) exit(0);
                fprintf(stdout, "%d %d\n", v_i, v_j);
                
                BuildGraph(A_N, input);

                out_write result;
                /*WriteFile(output, &result);*/
                
            }
            break;        

        case 'C':
            if(mode[1] == '1')
            {
                if(fscanf(input, "%d %d\n", &v_i, &v_j) != 2) exit(0);
                fprintf(stdout, "%d %d\n", v_i, v_j);
                BuildGraph(A_N, input);

            }
            break;

        case 'D':
            if(mode[1] == '1')
            {
                if(fscanf(input, "%d\n", &v_i) != 1) exit(0);
                fprintf(stdout, "%d\n", v_i);
                BuildGraph(A_N, input);

            }
            break;

        case 'E':
            if(mode[1] == '1')
            {
                printf("\n");
                BuildGraph(A_N, input);
                
            }
            break;

        default:
            exit(0);
        }

    } while (!feof(input));

    FreeGraph(A_N);
    fclose(input);
    fclose(output);
    printf("Ta");

    return 0;
    
}


void search(Graph *G)
{


}


void BuildGraph(Graph *G, FILE *fp)
{
    int i, v, w;
    double wt;

    for(i = 0; i < G->E; i++)
    {
        if(fscanf(fp, "%d %d %lf\n", &v, &w, &wt) != 3) exit(0);

        GRAPHinsertE(G, EDGE(v, w, wt), i);
        printf("{%d - %d : %.2lf}\n", G->adj[i]->v, G->adj[i]->w, G->adj[i]->wt);
    }

    printf("\n");
    sort(G->adj, G->E);

    for(i = 0; i < G->E; i++) printf("{%d - %d : %.2lf}\n", G->adj[i]->v, G->adj[i]->w, G->adj[i]->wt);
    printf("\n");
      
}


void A1(Graph *G)
{
    int i;
    double total_wt;
    Edge **mst = (Edge **) malloc(G->V * sizeof(Edge *));
    for(i = 0; i < G->V; i++) mst[i] == NULL;

    total_wt = Kruskal(G, mst);

    for(i = 0; mst[i] != NULL; i++) printf("{%d - %d : %.2lf}\n", mst[i]->v, mst[i]->w, mst[i]->wt);
    printf("%.2lf", total_wt);
}

double B1(Graph *G, int v_i, int v_j)
{
 /*    int x = v_i - 1, y = v_j - 1;

    if(v_i > v_j && G->adj[x][y] >= 0.0) return G->adj[x][y];
    else if(G->adj[y][x] >= 0.0) return G->adj[y][x];
    else return -1;  */
    return 0;
}

void C1(){

}

void D1(){

}

void E1(){

}



void sort(Edge **a, int E)
{
    // bubble(a, 0, E-1);
    // insertion(a, 0, E-1);
    shell(a, 0, E-1);
}