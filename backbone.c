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
                shell(result.mst, 0, result.E-1, less_v);

                WriteFile(output, &result);
                free(result.mst);

            }
            break;

        case 'B':
            if(mode[1] == '1')
            {
                if(fscanf(input, "%d %d\n", &v_i, &v_j) != 2) exit(0);
                int i;
                Graph *copy = NULL;
                Edge **f;
                out_write result;

                BuildGraph(A_N, input);
                copy = GRAPHinit(A_N->V, A_N->E);
                GRAPHcopy(A_N, copy);

                result.V = A_N->V;
                result.A = A_N->E;
                result.mode = "B1";
                (v_i > v_j) ? (result.v_i = v_j, result.v_j = v_i) : (result.v_i = v_i, result.v_j = v_j);

                A1(A_N, &result);
                f = B1(copy, result.mst, &result, result.v_i, result.v_j, output);
                shell(result.mst, 0, result.E-1, less_v);
                fprintf(output, "%d %d %s %d %d %d %.2lf %d\n", result.V, result.A,
                result.mode, v_i, v_j, result.E, result.tot_cst, result.res);

                if(result.res == 0)
                {
                    for(i = 0; i < result.E; i++) fprintf(output, "%d %d %.2lf\n", result.mst[i]->v, result.mst[i]->w, result.mst[i]->wt);
                    fprintf(output, "\n");
                    FreeGraph(copy, copy->E);

                }
                else
                {
                    for(i = 0; i < result.E; i++) fprintf(output, "%d %d %.2lf\n", result.mst[i]->v, result.mst[i]->w, result.mst[i]->wt);
                    if(result.res != -1)fprintf(output, "%d %d %.2lf\n", f[result.E-1]->v, f[result.E-1]->w, f[result.E-1]->wt);
                    for(i = 0; i < result.E-1; i++) free(f[i]);
                    for(; i < copy->E; i++) free(copy->adj[i]);
                    free(f);
                    free(copy->adj);
                    free(copy);
                }
                fprintf(output, "\n");
                
                free(result.mst);
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
                free(result.mst);


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
                free(result.mst);


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
                free(result.mst);


            }
            break;

        default:
            exit(0);
        }

    } while (!feof(input));

    FreeGraph(A_N, A_N->E);
    fclose(input);
    fclose(output);
    // printf("Ta\n");

    return 0;
    
}

void BuildGraph(Graph *G, FILE *fp)
{
    int i, v, w;
    double wt;

    for(i = 0; i < G->E; i++)
    {
        if(fscanf(fp, "%d %d %lf\n", &v, &w, &wt) != 3) exit(0);

        GRAPHinsertE(G, EDGE(v, w, wt), i);
    }
}


void A1(Graph *A_N, out_write *result)
{
    int i, E;
    double *exP, tot_wt; /*Exit parameters, total cost and the number of edges*/

    Edge **mst = (Edge **) malloc((A_N->V-1) * sizeof(Edge *));
    for(i = 0; i < A_N->V-1; i++) mst[i] = NULL;

    sort(A_N->adj, A_N->E);
    // for(i = 0; i < G->E; i++) printf("{%d - %d : %.2lf}\n", G->adj[i]->v, G->adj[i]->w, G->adj[i]->wt);

    exP = Kruskal(A_N, mst);
    E = (int) exP[0]; tot_wt = exP[1];

    free(exP);
    

    result->E = E;
    result->tot_cst = tot_wt;
    result->mst = mst;
}

Edge **B1(Graph *G, Edge **mst, out_write *result, int v_i, int v_j, FILE *output)
{
    int i, p, E = result->E;
    Edge **a = G->adj, **alt_mst = NULL;
    double *exP;

    alt_mst = (Edge**) malloc(E * sizeof(Edge*));
    for(i = 0, p = 0; i < E; i++)
    {
        alt_mst[i] = NULL;
        if(mst[i]->v != v_i || mst[i]->w != v_j)
        {
            alt_mst[p] = (Edge*) calloc(1, sizeof(Edge));
            alt_mst[p]->v = mst[i]->v;
            alt_mst[p]->w = mst[i]->w;
            alt_mst[p]->wt = mst[i]->wt;
            p++;

        }
    }
    
    if(p == E)
    {
        result->res = 0;
        for(i = 0; i < p; i++) free(alt_mst[i]);
        free(alt_mst);
        return NULL;
    } 
    else
    {
        for(i = 0; i < G->E && (a[i]->v != v_i || a[i]->w != v_j); i++);
        // printf("\n{(%d %d) %d / %d - %d : %.2lf}\n\n", v_i, v_j, i, a[i]->v, a[i]->w, a[i]->wt);
        for(; i < G->E-1; i++) exch(a[i], a[i+1]);
        /*leads the edge for removal to the last position of the edges' vector*/
        for(; i < G->E; i++) free(a[i]);
        G->E--;
        sort(a, G->E);

        // for(i = 0; i < G->E; i++) printf("{%d - %d : %.2lf}\n", a[i]->v, a[i]->w, a[i]->wt);

        exP = Kruskal(G, alt_mst);
        if(exP[0] < E) result->res = -1;
        else result->res = 1;
        result->E = (int) exP[0];
        free(exP);

        return alt_mst;
    }
}

void C1(){

}

void D1(){

}

void E1(){

}


