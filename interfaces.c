#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "interfaces.h"


Edge *EDGE(int v, int w, double wt)
{
    Edge *E = (Edge*) malloc(sizeof(Edge)) ;
    E->v = v;
    E->w = w;
    E->wt = wt;
    
    return E;
}


 /*---------------- Graph Interface ----------------*/
Graph *GRAPHinit(int V, int A)
{
    int v;
    Graph *G = (Graph*) calloc(1, sizeof(Graph));
    if(G == NULL) exit(0);

    G->V = V; G->E = A; 
    G->adj = (Edge **) malloc(G->E * sizeof(struct edge *)); 
    for(v = 0; v < A; v++) G->adj[v] = NULL;
    if(G->adj == NULL) exit(0);
    
    return G;
}

void GRAPHinsertE(Graph *G, Edge *e, int i)
{
    G->adj[i] = e;
}

void GRAPHcopy(Graph *a, Graph *b)
{
    int i;

    b->V = a->V; b->E = a->E;

    for(i = 0; i < a->E; i++)
    {
        b->adj[i] = (Edge*) malloc(sizeof(Edge));
        (b->adj[i])->v = (a->adj[i])->v;
        (b->adj[i])->w = (a->adj[i])->w;
        (b->adj[i])->wt = (a->adj[i])->wt;
    }
    
}

void FreeGraph(Graph *G, int E)
{
    int i;

    for(i = 0; i < E; i++)
    {
        if(G->adj[i] != NULL) free(G->adj[i]);
    }
    free(G->adj);
    free(G);
}
/*------------------------------------------------*/


/*----------------- SORTING -------------------*/
void bubble(Edge **a, int l, int r)
{
    int i, j;

    for (j = r; j > l; j--)
        for (i = l; i < j; i++)
            if(more(a[i]->wt, a[i+1]->wt)) exch(a[i], a[i+1]);
}

void insertion(Edge **a, int l, int r)
{
    int i, j;

    for (i = l+1; i <= r; i++)
    {
        Edge *v = a[i];
        j = i;
        while (j > l && less(v->wt, a[j-1]->wt))
        {
            a[j] = a[j-1];
            j--;
        }
        a[j] = v;
    }
}

int less_wt(Edge *a, Edge *b)
{
    return less(a->wt, b->wt);
}

int less_w(Edge *a, Edge *b)
{
    return less(a->w, b->w);
}

int less_v(Edge *a, Edge *b)
{   
   if(a->v == b->v) return less_w(a, b);
   else return less(a->v, b->v);
}

void sort(Edge **a, int E)
{
    /* bubble(a, 0, E-1);
    insertion(a, 0, E-1); */
    shell(a, 0, E-1, less_wt);
}

void shell(Edge **a, int l, int r, int(*less_)() )
{
    int i, j, k;

    int incs[16] = {1391376, 463792, 198768, 86961, 33936, 13776, 4592, 1968, 861, 336, 112, 48, 21, 7, 3, 1};

    for ( k = 0; k < 16; k++)
    {
        int h = incs[k];

        for (i = l+h; i <= r; i++)
        {
            Edge *v = a[i];
            j = i;
            while (j-h >= l && less_(v, a[j-h]))
            {
                exch(a[j], a[j-h]);
                j-=h;
            }
            a[j] = v;
        }
    }
}
/*-----------------------------------------------*/


 
/*--------------Union Find------------*/

int * UFinit(int V)
{
    int v;
    int *parent;

    parent = (int*) malloc(V * sizeof(int));
    for(v = 0; v < V; v++) parent[v] = -1;

    return parent;
}

int UFfind(int *p, int v)
{
    if(p[v-1] == -1)
        return v;
    return UFfind(p, p[v-1]);
}

void UFunion(int *p, int v, int w)
{
    int v_set, w_set;
    v_set = UFfind(p, v); w_set = UFfind(p, w);

    if(v_set != w_set) p[v_set-1] = w_set;
}

int UFis_cycle(int *p, int v, int w)
{
    return (UFfind(p, v) == UFfind(p, w));
}

/*------------------------------------*/



    
/*--------------------Kruskal Alg.--------------------*/
double *Kruskal(Graph *G, Edge **mst)
{
    int i, k, *p;
    double *wt_E;
    
    wt_E = (double*) malloc(2 * sizeof(double)); 
    wt_E[0] = 0.0; wt_E[1] = 0.0;
    Edge **a = G->adj;

    p = UFinit(G->V);
    for(i = 0, k = 0; i < G->E && k < G->V-1; i++)
    {
        if(!UFis_cycle(p, a[i]->v, a[i]->w))
        {
            UFunion(p, a[i]->v, a[i]->w);
            free(mst[k]);
            mst[k++] = a[i]; 
            wt_E[1] += a[i]->wt;    /*counter for cost*/
            wt_E[0]++;              /*counter for mst's edges*/             
        }
    }
    free(p);
    return wt_E;
}
/*----------------------------------------------------*/


/*-------------CLEAN UP------------*/

/*---------------------------------*/


/*---------- Queue Interface ----------*/
/* Item QueueNew(int v, double wt, link *pNext)
{
    link *x = (link *) malloc(sizeof(link));
    x->v = v;
    x->wt = wt;
    x->next = pNext;

    return x;
}

Q *QueueInit(int maxN)
{
    Q *pQueue = (Q*) malloc(sizeof(Q));
    pQueue->first = pQueue->last;

    return pQueue;
}

void QueuePut(Q *pQueue, Item vI)
{
    if(pQueue->first == NULL) Empty Queue
    {
        pQueue->last = QueueNew(vI, pQueue->first);
        pQueue->first = pQueue->first;
        return;
    }

    Item put in as last
    pQueue->last->next = QueueNew(vI, NULL);
    pQueue->last = pQueue->last->next;
}

Edge* QueueGet(Q *pQueue)
{
    link *l = pQueue->first->next;
    Edge *e = EDGE(pQueue->first->v,0, pQueue->first->wt);
    free(pQueue->first);
    pQueue->first = l;

    return e;
}

int QueueEmpty(Q *pQueue)
{
    return (pQueue->first == NULL);
} */
/*-------------------------------------*/


/*----------- BFS Algorithm -------------*/
/* void bfs(Graph *G, Edge *E)
{
    int v, *pre, *st, cnt;
    Q *Q;

    pre = (int*) malloc(G->V * sizeof(int));
    st = (int*) malloc(G->E * sizeof(int));


    for(v = 0; v < G->V; v++)
    {
        pre[v] = -1;
        st[v] = -1;
    }

    Q = QueueInit(G->V);
    QueuePut(Q, E);
    while(!QueueEmpty(Q))
    {
        if(pre[(E = QueueGet(Q))->w] == -1)
        {
            pre[E->w] = cnt ++;
            st[E->w] = E->v;
            for(v = 0; v < G->V; v++)
            {
                if(G->adj[E->w][v] == 1)
                    if(pre[v] == -1)
                        QueuePut(Q, EDGE(E->w, v));
            }
        }
    }

}
 */
/*---------------------------------------*/