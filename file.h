#ifndef _FIRD_H_
#define _FIRD_H_

#include "interfaces.h"

typedef struct _i_o_name
{
    char *i_name;
    char *o_name;
} i_o_name;

typedef struct _out_write
{
    int V;
    int A;
    char *mode;
    int v_i;
    int v_j;
    int E;
    int res;
    double tot_cst;
    Edge **mst;
    Edge *alt_edge;
    Edge **mst_alt;
} out_write;


i_o_name *CheckCall(int, char const *);
char *OutputFile(char *);
void WriteFile(FILE *, out_write *);


#endif