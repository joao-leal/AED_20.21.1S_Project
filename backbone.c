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
        int origin, dest;
        double weight;
        char mode[3] = "";


        if(fscanf(input, "%d %d %s %f", &origin, &dest, mode, &weight) != 4) 
        {
            fprintf(stdin, "%d %d %s %f\n", origin, dest, mode, weight);
            exit(0);
        }

        switch (mode[0])
        {
        case 'A':
            if(mode[1] == '0')
            {
                A0();
            }
            break;

        case 'B':
            if(mode[1] == '0')
            {
                /*B0();*/
            }
            break;        

        case 'C':
            if(mode[1] == '0')
            {
                C0();
            }
            break;

        case 'D':
            if(mode[1] == '0')
            {
                /*D0();*/
            }
            break;

        default:
            exit(0);
        }

    } while (feof(input));
    

    FreeGraph(G);



    return 0;
    
}



void A0()
{

}

int B0(Graph *G, int v, int w)
{

    
}

void C0(){

}

void D0(Graph *G){

}


