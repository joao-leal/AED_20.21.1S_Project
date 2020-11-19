/* Include Libraries */
#include "utils.h"

/* Function: Print_Menu
	- Prints out menu and reads the option chosen by user
	- Prints the menu while the user doesn't choose a valid option
*/
int Print_Menu()
{
	int temp = -1; // variable for choosing the option
	char buffer[VECTOR_SIZE];

	// Prints the menu while the user doesn't choose a valid option
	do
	{
		system("clear");
		printf("Choose the number corresponding the algorythm's operation you want\n");
		printf("1 - Determine whether or not an input internet is connected\n");
		printf("2 - Determine whether or not an input internet is link biconnected;\n");
		printf("3 - Determine whether or not an input internet is commercially acyclic\n");
		printf("4 - Determine whether or not an input internet is commercially connected\n");
		printf("0 - Exit App\n");

		fflush(stdin);
		fgets(buffer, VECTOR_SIZE, stdin);

	}while(sscanf(buffer, "%d", &temp) != 1 || temp < 0 || temp > 4);

	return temp;
}

/* Function: Open_File
	- Used to open files.
	- Receives the pointer, filename and open option
	- Returns the pointer to the opened file
*/
FILE* Open_File(FILE* fp, char *File_Name, char *option)
{
	// Opens and verifies if it is really opened
  fp = fopen(File_Name, option);
  if(fp==NULL){
		printf("No file with such name.\nExiting...\n");
    exit(0);
	}

  return fp;
}

/* Function: Create_node_list
	- Used to create the node vector with the link list for each node
	- Each node is added through the function add_node
*/
void Create_node_list(FILE*fp, Nodes** node_list){

		char buffer[MAX_FILE_LINE_SIZE];
		int first=0, second=0, type=0; // Auxiliary integers for the link translation

		// Alocate the vector for the nodes
		*node_list = (Nodes*) malloc(sizeof(Nodes)*(MAX_NODES+1));

		// Add a node or a link while there are still new lines being read
		while(fgets(buffer, MAX_FILE_LINE_SIZE, fp)){
			sscanf(buffer, "%d %d %d", &first, &second, &type);
			// add node or link to the node vector
			add_node(first, second, type, node_list);
		}
}

/* Function: add_node
	- Adds the link to the graph
	- Checks if the head of the connection is already on the node vector
	- If it wasn't adds it and if it was iterates it's links and adds the new one on the end of the list
*/
void add_node(int first, int second, int type, Nodes** list){
	Nodes aux_n;
	Links* aux_l = NULL;
	// Checks if the head of the new link is already in the vector
	if ((*list)[first].link_list == NULL){ // If it isn't it alocates and initiates the memory needed
		node_count += 1;
		(*list)[first].link_list = (Links*)malloc(sizeof(Links));
		(*list)[first].link_list->self = second;
		(*list)[first].link_list->type = type;
		(*list)[first].link_list->next = NULL;
	} else { // If it is adds the new link to the end of the link list
		aux_n = (*list)[first];
		aux_l = aux_n.link_list;
		// Find the end of link list
		while(aux_l->next != NULL) {
			aux_l = aux_l->next;
		}
		aux_l->next = (Links*)malloc(sizeof(Links));
		aux_l = aux_l->next;
		aux_l->self = second;
		aux_l->type = type;
		aux_l->next = NULL;
	}
}

/* Function: free_nodes
	- Fuction that iterates all nodes and if the nodes have links calls free_links to free them
*/
void free_nodes(Nodes* node_list){
	for ( int i = 0; i<=MAX_NODES; i++){
		free_links(node_list[i].link_list);
	}
	free(node_list);
}

/* Function: free_links
	- Recursive function that iterates until the end of a link list and starts freeing the space from there
*/
void free_links(Links* link){
	if (link != NULL){
		free_links(link->next);
	} else {
		return;
	}
	free(link);
}
