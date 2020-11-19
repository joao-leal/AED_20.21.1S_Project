#ifndef _GRAPH_H_
#define _GRAPH_H_


typedef void * Item;

typedef struct edge
{
    int v;
    int w;
    int weight;
} Edge;

typedef struct _list
{
    Item item;
    struct _list *next;
} list;

typedef struct graph
{
    int V;
    int E;
    Item *adj;
} Graph;
typedef struct queue
{
    list * first;
    list * last; 
} Q;



Edge *EDGE(int, int, int);


/*---------- Graph Interface --------- */
Graph *GRAPHinit(int); 
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

/*-----------  List Interface -----------*/
list *LISTNewEl(list *, Item);
void LISTFreeEl(list *);
void LISTDelNext(list *);
list *LISTNext(list *);
Item LISTGetEl(list *);
/***************************************/

/*---------- Queue Interface ----------*/
void QueueDump(Q *);
Q *QueueInit(int);
int QueueEmpty(Q*);
void QueuePut(Q*, Item);
Item QueueGet(Q*);
Item QueueNew(Item, list*);
/*-------------------------------------*/






#endif