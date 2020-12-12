#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "file.h"
#include "interfaces.h"

#define maxINT 1000


int main(int argc, char const *argv[])
{
    Graph *A_N = NULL; /*A_N stands for Airport Network*/ 
    FILE *input, *output;
    i_o_name *fnames;

    /*if the arguments are correct, CheckCall returns the name of the input file*/
    input = fopen((fnames = (CheckCall(argc, (char*) argv[1])))->i_name, "r");
    if(input == NULL) exit(0);
 
    output = fopen(fnames->o_name, "a+");
    if(output == NULL) exit(0);

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

        A_N = GRAPHinit(Apts, Rts);
        BuildGraph(A_N, input);

        switch (mode[0])
        {
        case 'A':
            if(mode[1] == '0')
            {
                out_write result = {Apts, Rts, mode, v_i, 0, A1(A_N), 0 };
                /*WriteFile(output, &result);*/
            }
            break;

        case 'B':
            if(mode[1] == '0')
            {
                out_write result = {Apts, Rts, mode, v_i, v_j, 0, B0(A_N, v_i, v_j)};
                /*WriteFile(output, &result);*/
                
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

    FreeGraph(A_N);
    fclose(input);
    fclose(output);
    printf("Ta");

    return 0;
    
}


void search(Graph *G)
{


}

void GRAPHmstV(Graph *G, int st[], double val[])
{
    int v, w, min;
    link *aux;

    for( v = 0; v < G->V; v++)
    {
        st[v] = -1; fr[v] = v; val[v] = -1;
    }

    min = 0; st[0] = 0;
    for(v = 0; min != G->V; v = min, st[v] = fr[v])
    {
        for(w = 0, min = G->V; w < G->V; w++)
        {
            if(st[w] == -1)
            {
                (G->adj[w] != NULL) ? aux = G->adj[w] : exit(0);
                for(; aux->v != w; (aux->next != NULL) ? aux = aux->next : exit(0))
                if(aux->wt < val[w]) {val[w] = aux->wt; fr[w] = v;}
                if(val[w] < val[min]) min = w;
            }
            printf("%d ", st[w]);
        }
        printf("\n");
    }
}

void BuildGraph(Graph *G, FILE *fp)
{
    int i, v, w;
    double wt;

    for(i = 0; i < G->E; i++)
    {
        if(fscanf(fp, "%d %d %lf\n", &v, &w, &wt) != 3) exit(0);

        GRAPHinsertE(G, EDGE(v, w, wt)); 
       
    }
      
}


int A1(Graph *G)
{
    int i, *st = (int *) calloc(G->V, sizeof(int));
    double *val = (double *) calloc(G->V, sizeof(double));

    GRAPHmstV(G, st, val);

    for(i = 0; i < G->V; i++) printf("%d ", st[i]);
    return 0;
}

double B0(Graph *G, int v_i, int v_j)
{
 /*    int x = v_i - 1, y = v_j - 1;

    if(v_i > v_j && G->adj[x][y] >= 0.0) return G->adj[x][y];
    else if(G->adj[y][x] >= 0.0) return G->adj[y][x];
    else return -1;  */
    return 0;
}

void C0(){

}

void D0(Graph *G){

}


