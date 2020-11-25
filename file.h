#ifndef _FIRD_H_
#define _FIRD_H_

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
    int result;
    double weight;
} out_write;


i_o_name *CheckCall(int, char const *);
char *OutputFile(char *);
void WriteFile(FILE *fp, out_write *result);


#endif