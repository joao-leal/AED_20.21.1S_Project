#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "file.h"
#include "interfaces.h"

int main(int argc, char const *argv[])
{

    CheckCall(argc, (char*) argv[1]);

    int i;
    Graph *G = NULL;

    G = GRAPHinit(5);

    FreeGraph(G);

    return 0;
    
}



void modeA0()
{

}

int B0(Graph *G, int v, int w)
{
    
    
}

void modeC0(){

}

void modeD0(){

}


