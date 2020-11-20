#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "file.h"
#include "interfaces.h"

int main(int argc, char const *argv[])
{
    Graph *G = NULL;
    FILE *input, *output;
    
    input = CheckCall(argc, (char*) argv[1]); 
    /*if the arguments are correct, CheckCall returns the name of the input file*/

    
    do
    {
        int Apts, Rts, v_i, v_j, origin, dest;
        double weight;
        char mode[3] = "";

        Apts = Rts = v_i = v_j = origin = dest = 0;

        if(fscanf(input, "%d %d %s %d", &Apts, &Rts, mode, &v_i) != 4) 
        {
            if(!strcmp(mode, "B0"))
            {
                fscanf(input, "%d", &v_j);
            }
            exit(0);
        }

        fprintf(stdout, "%d %d %s %d", Apts, Rts, mode, v_i);
        if(!strcmp(mode, "B0")) fprintf(stdout, "%d", v_j);
        else fprintf(stdout, "\n");

        G = GRAPHinit(Apts, Rts);

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
    fclose(input);



    return 0;
    
}



void A0()
{

}

int B0(Graph *G, int v, int w)
{

   return 0; 
}

void C0(){

}

void D0(Graph *G){

}


