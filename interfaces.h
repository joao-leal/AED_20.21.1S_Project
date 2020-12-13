#ifndef _GRAPH_H_
#define _GRAPH_H_


#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define more(A, B) (key(A) > key(B))
#define exch(A, B) {Item t = A; A = B; B = t; }
#define compexch(A, B) if (less(B,A)) exch(A, B)


typedef void * Item;

typedef struct edge
{
    int v;
    int w;
    double wt;
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
    Edge **adj;
} Graph;

typedef struct queue
{
    link * first;
    link * last; 
} Q;

Edge *EDGE(int, int, double);
void Item_swap(Item *, Item *);


/*---------- Graph Interface --------- */
Graph *GRAPHinit(int, int); 
void GRAPHpopulate(Graph *, FILE *);
void GRAPHinsertE(Graph *, Edge *, int);
void GRAPHremoveE(Graph *, Edge *);
void FreeGraph(Graph *);

/****************************************/

/*----------- Algorithms -------------*/
void bfs(Graph *, Edge *);
double Kruskal(Graph *, Edge **);
/*****************************************/

/*--------------Union Find------------*/
int * UFinit(int);
int UFfind(int *, int);
void UFunion(int *, int, int);
int UFis_cycle(int *, int, int);

/*------------------------------------*/

/*----------- SORT -------------*/
void bubble(Edge **, int, int);
void insertion(Edge **, int, int);
void shell(Edge**, int, int);

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