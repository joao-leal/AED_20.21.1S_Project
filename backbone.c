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
        // fprintf(stdout, "%d %d %s ", Apts, Rts, mode);

        A_N = GRAPHinit(Apts, Rts);

        switch (mode[0])
        {
        case 'A':
            if(mode[1] == '1')
            {
                out_write result;

                result.V = A_N->V;
                result.A = A_N->E;
                result.mode = mode;
                BuildGraph(A_N, input);
                
                A1(A_N, &result);
                WriteFile(output, &result);
                free(result.mst);

            }
            break;

        case 'B':
            if(mode[1] == '1')
            {
                out_write result;

                if(fscanf(input, "%d %d\n", &v_i, &v_j) != 2) exit(0);

                result.V = A_N->V;
                result.A = A_N->E;
                result.mode = mode;
                result.v_i = v_i;
                result.v_j = v_j;
                
                BuildGraph(A_N, input);

                A1(A_N, &result);
                WriteFile(output, &result);
                
            }
            break;        

        case 'C':
            if(mode[1] == '1')
            {
                out_write result;

                if(fscanf(input, "%d %d\n", &v_i, &v_j) != 2) exit(0);

                result.V = A_N->V;
                result.A = A_N->E;
                result.mode = mode;
                result.v_i = v_i;
                result.v_j = v_j;

                BuildGraph(A_N, input);

                A1(A_N, &result);
                WriteFile(output, &result);

            }
            break;

        case 'D':
            if(mode[1] == '1')
            {
                out_write result;

                if(fscanf(input, "%d\n", &v_i) != 1) exit(0);

                result.V = A_N->V;
                result.A = A_N->E;
                result.mode = mode;
                result.v_i = v_i;

                BuildGraph(A_N, input);

                A1(A_N, &result);
                WriteFile(output, &result);

            }
            break;

        case 'E':
            if(mode[1] == '1')
            {
                out_write result;


                result.V = A_N->V;
                result.A = A_N->E;
                result.mode = mode;

                BuildGraph(A_N, input);

                A1(A_N, &result);
                WriteFile(output, &result);

            }
            break;

        default:
            exit(0);
        }

    } while (!feof(input));

    FreeGraph(A_N);
    fclose(input);
    fclose(output);
    // printf("Ta\n");

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
        // printf("{%d - %d : %.2lf}\n", G->adj[i]->v, G->adj[i]->w, G->adj[i]->wt);
    }

    sort(G->adj, G->E);

    // for(i = 0; i < G->E; i++) printf("{%d - %d : %.2lf}\n", G->adj[i]->v, G->adj[i]->w, G->adj[i]->wt);
      
}


void A1(Graph *A_N, out_write *result)
{
    int i, E;
    double *exP, tot_wt; /*Exit parameters, total cost and the number of edges*/

    Edge **mst = (Edge **) malloc((A_N->V-1) * sizeof(Edge *));
    for(i = 0; i < A_N->V-1; i++) mst[i] = NULL;

    exP = Kruskal(A_N, mst);
    E = (int) exP[0]; tot_wt = exP[1];

    shell(mst, 0, E-1, less_v);

   /*  for(i = 0; i < E; i++) 
    {
        // if(mst[i] == NULL) continue;
        printf("{%d - %d : %.2lf}\n", mst[i]->v, mst[i]->w, mst[i]->wt);
    }
    printf("%d %.2lf\n", E, tot_wt);
 */
    free(exP);

    result->E = E;
    result->tot_cst = tot_wt;
    result->mst = mst;
}

double B1(Graph *A_N, int v_i, int v_j)
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


