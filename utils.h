#ifndef FILE_DEALING_H_INCLUDED
#define FILE_DEALING_H_INCLUDED

/* Include the Librarys needed*/
#include "structs_n_main.h"

/* Instanciate the functions */
FILE* Open_File(FILE*, char *, char *);

int Print_Menu();

void Create_node_list(FILE*fp, Nodes** node_list);

void add_node(int first, int second, int type, Nodes** list);

void free_nodes(Nodes* node_list);

void free_links(Links* link);


#endif // FILE_DEALING_H_INCLUDED
