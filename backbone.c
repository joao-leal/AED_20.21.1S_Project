#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "file.h"
#include "interfaces.h"


#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item t = A; A = B; B = t; }
#define compexch(A, B) if (less(B,A)) exch(A, B)



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
        printf("{%d-%d : %.2lf}\n", G->adj[i]->v, G->adj[i]->w, G->adj[i]->wt);
    }
      
}


void A1()
{
    /* int i, *st = (int *) calloc(G->V, sizeof(int));
    double *val = (double *) calloc(G->V, sizeof(double));


    for(i = 0; i < G->V; i++) printf("%d ", st[i]);
    return 0; */
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
