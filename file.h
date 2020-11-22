#ifndef _FIRD_H_
#define _FIRD_H_

typedef struct _i_o_name
{
    char *i_name;
    char *o_name;
} i_o_name;

i_o_name *CheckCall(int, char const *);
char *OutputFile(char *);
FILE *GetFile(char *);


#endif