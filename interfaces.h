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


/*---------- Graph Interface --------*/
Graph *GRAPHinit(int, int); 
void GRAPHpopulate(Graph *, FILE *);
void GRAPHinsertE(Graph *, Edge *, int);
void GRAPHremoveE(Graph *, Edge *);
void GRAPHcopy(Graph*, Graph *);
void FreeGraph(Graph *, int);

/*----------------------------------*/


/*--------------- SORT -------------*/
void bubble(Edge **, int, int);
void insertion(Edge **, int, int);
int less_v(Edge *, Edge *);
int less_w(Edge *, Edge *);
int less_wt(Edge * , Edge *);
void sort(Edge **, int);
void shell(Edge**, int, int, int());
/*----------------------------------*/


/*--------------Union Find----------*/
int * UFinit(int);
int UFfind(int *, int);
void UFunion(int *, int, int);
int UFis_cycle(int *, int, int);
/*----------------------------------*/


/*----------- Algorithms -----------*/
void bfs(Graph *, Edge *);
double *Kruskal(Graph *, Edge **);
/*----------------------------------*/


/*--------- CLEAN UP --------------*/
/*---------------------------------*/


#endif