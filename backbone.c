#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "file.h"
#include "interfaces.h"

int main(int argc, char const *argv[])
{
    int i;
    Graph *G = NULL;
    FILE *input, *output;
    
    input = fopen(CheckCall(argc, (char*) argv[1]), "r"); 
    /*if the arguments are correct, CheckCall returns the name of the input file*/

    

    G = GRAPHinit(5);


    do
    {
        /* code */
    } while (feof());
    

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


