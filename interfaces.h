#ifndef _GRAPH_H_
#define _GRAPH_H_


typedef void * Item;

typedef struct edge
{
    int v;
    int w;
    double weight;
} Edge;

typedef struct node
{
    int v;
    double wt;
    struct node *next;
} link;

typedef struct graph
{
    int V;
    int E;
    link **adj;
} Graph;

typedef struct queue
{
    link * first;
    link * last; 
} Q;

Edge *EDGE(int, int, double);


/*---------- Graph Interface --------- */
Graph *GRAPHinit(int, int); 
void GRAPHpopulate(Graph *, FILE *);
void GRAPHinsertE(Graph *, Edge *);
void GRAPHinsertValue(Graph *, int, int);
void GRAPHinsertString(Graph *, char*, int);
void GRAPHremoveE(Graph *, Edge *);
int GRAPHedges(Edge **, Graph *);
Graph *GRAPHcopy(Graph *);
void GRAPHdestroy(Graph *);
void FreeGraph(Graph *);

/****************************************/

/*----------- BFS Algorithm -------------*/
void bfs(Graph *, Edge *);
/********************************/


/*-----------  link Interface -----------*/
link *NEW(link *, int, double);
void LISTFreeEl(link *);
void LISTDelNext(link *);
link *LISTNext(link *);
Item LISTGetEl(link *);
/***************************************/



/*---------- Queue Interface ----------*/
void QueueDump(Q *);
Q *QueueInit(int);
int QueueEmpty(Q*);
void QueuePut(Q*, Item);
Item QueueGet(Q*);
Item QueueNew(Item, link*);
/*-------------------------------------*/

#endif