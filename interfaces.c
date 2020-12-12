#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "interfaces.h"


Edge *EDGE(int v, int w, double wt)
{
    Edge *E = (Edge*) malloc(sizeof(Edge)) ;
    E->v = v;
    E->w = w;
    E->wt = wt;
    
    return E;
}


/*---------- link Interface ----------*/
link *NEW(link *ptr, int v, double wt)
{
    link *t = (link *) malloc(sizeof(link));

    t->v = v;
    t->wt = wt;
    t->next = ptr;

    return t;
}

link *LISTNext(link *ptr)
{
    return ptr->next;
}
/*-----------------------------------*/


 /*---------------- Graph Interface ----------------*/
Graph *GRAPHinit(int V, int A)
{
    int v;
    Graph *G = (Graph*) calloc(1, sizeof(Graph));
    if(G == NULL) exit(0);

    G->V = V; G->E = A; 
    G->adj = (Edge **) malloc(G->E * sizeof(struct edge *)); 
    for(v = 0; v < V; v++) G->adj[v] = NULL;
    if(G->adj == NULL) exit(0);
    
    return G;
}

void GRAPHinsertE(Graph *G, Edge *e, int i)
{
    G->adj[i] = e;
}

void FreeGraph(Graph *G)
{
    int i;

    for(i = 0; i < G->E; i++)
    {
        free(G->adj[i]);
    }
    free(G->adj);
    free(G);
}


/*------------------------------------------------*/


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