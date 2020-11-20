#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "interfaces.h"



Edge *EDGE(int v, int w, int wt)
{
    Edge *E = (Edge*) malloc(sizeof(Edge)) ;
    E->v = v;
    E->w = w;
    E->weight = wt;
    
    return E;
}


/*---------- List Interface ----------*/
list *LISTNewEl(list *ptr, Item N)
{
    list *aux = (list *) calloc(1, sizeof(list));

    if(ptr == NULL)
    {
        aux->next = NULL;
    }
    else
    {
        aux->next = ptr;
    }
    
    aux->item = N;

    return aux;
}

list *LISTNext(list *ptr)
{
    return ptr->next;
}

Item LISTGetEl(list *ptr)
{
    return ptr->item;
}
/*-------------------------------------*/


 /*---------------- Graph Interface ----------------*/
Graph *GRAPHinit(int V, int A)
{

    Graph *G = NULL;

    if(V > 50)
    {
        G =  (Graph*) calloc(1, sizeof(Graph));
        if(G == NULL) exit(0);

        G->adj = NULL;
        G->V = V; G->E = A; 
        G->adj = calloc(V, sizeof(struct _list*));
        if(G->adj == NULL) fprintf(stderr, "Can't allocate Graph");
    }
    else
    {
        int i;

        G = (Graph*) calloc(1, sizeof(Graph));
        if(G == NULL) exit(0);

        G->V = V; G->E = A; 
        G->adj = calloc(V, sizeof(int *));
        for(i = 0;  i < V; i++)
        {
            G->adj[i] = (double*) calloc((i+1), sizeof(double));
        }
    }
    
    
    return G;
}

void GRAPHinsertE(Graph *G, Edge *e)
{
    int v, w, wt;
    list *ptr = NULL;

    v = e->v -1;
    w = e->w -1;
    wt = e->weight;

    if(G->adj[v] == NULL)
    {
        G->adj[v] = (list*) malloc(sizeof(struct _list));


        if(G->adj[v] == NULL) exit(0);

        ptr = G->adj[v];

        ptr->item = e;
        ptr->next = NULL;
              
    }

}

void GRAPHinsertValue(Graph *G, int v, int t)
{
}

void FreeGraph(Graph *G)
{
    int i, p;

    for(i = 0; i < G->V ; i++)
    {
        list *ptr, *aux;

        ptr = G->adj[i];
        if(ptr == NULL) free(G->adj[i]);    
        else
        {
            for(; ptr != NULL;)
            {
                aux = ptr;
                ptr = ptr->next;

                free(aux->item);
                free(aux);

            }
        }
    }
    
    free(G->adj);
    free(G);
}

/*------------------------------------------------*/




/*---------- Queue Interface ----------*/
Item QueueNew(Item vItem, list *pNext)
{
    list *x = (list *) malloc(sizeof(list));
    x->item = vItem;
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
    if(pQueue->first == NULL) /*Empty Queue*/
    {
        pQueue->last = QueueNew(vI, pQueue->first);
        pQueue->first = pQueue->first;
        return;
    }

    /*Item put in as last*/
    pQueue->last->next = QueueNew(vI, NULL);
    pQueue->last = pQueue->last->next;
}

Item QueueGet(Q *pQueue)
{
    Item item = pQueue->first->item;
    list *l = pQueue->first->next;

    free(pQueue->first);
    pQueue->first = l;

    return item;
}

int QueueEmpty(Q *pQueue)
{
    return (pQueue->first == NULL);
}
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