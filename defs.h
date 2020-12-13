#ifndef _DEFS_H_
#define _DEFS_H_


#include "interfaces.h"





void BuildGraph(Graph *, FILE *);
void sort(Edge **, int);


/*Returns the depth of the vertice given as input*/
void A1(Graph *);
/*Returns the route and its cost if there's one route between the two airports, otherwise returns -1*/
double B1(); 

/**/
void C1(); 

/**/
void D1(); 

void E1(); 


#endif