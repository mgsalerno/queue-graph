#ifndef _GRAPH_H
#define _GRAPH_H

/* ------------------------------------------------------------------------------ */

#define STRING_SIZE 4096

/* ------------------------------------------------------------------------------ */

typedef struct graph_t graph_t ;
typedef struct vertex_t vertex_t ;
typedef struct edge_t edge_t ;

/* ------------------------------------------------------------------------------
 * structure: graph
 * ------------------------------------------------------------------------------
 * vertices: vertices in that graph
 * name: name of that graph
 * ------------------------------------------------------------------------------ */

struct graph_t
{
  vertex_t *vertices ;
  char *name ;
} ;

/* ------------------------------------------------------------------------------
 * structure: vertex
 * ------------------------------------------------------------------------------
 * prev: pointer to the previous vertex
 * next: pointer to the next vertex
 * edges: pointer to a list of edges that connect to the vertex
 * name: name of the vertex
 * degree: current degree of the vertex
 * ------------------------------------------------------------------------------ */

struct vertex_t
{
  vertex_t *prev, *next ;
  edge_t *edges ;
  char *name ;
  int degree ;
} ;

/* ------------------------------------------------------------------------------
 * structure: edge
 * ------------------------------------------------------------------------------
 * prev: pointer to the previous edge
 * next: pointer to the next edge
 * vertex: vertex connected to the edge
 * ------------------------------------------------------------------------------ */

struct edge_t
{
  edge_t *prev, *next ;
  vertex_t *vertex ;
} ;

/* ------------------------------------------------------------------------------
 * function: create_graph 
 * ------------------------------------------------------------------------------
 * creates a graph with a given name
 *
 * name: name of the graph to be created
 * 
 * returns: pointer to the created graph
 * ------------------------------------------------------------------------------ */

graph_t *create_graph(char *name) ;

/* ------------------------------------------------------------------------------
 * function: add_vertex 
 * ------------------------------------------------------------------------------
 * inserts a vertex in the graph
 *
 * g: graph in which the vertex will be inserted
 * name: name of the vertex that will be inserted
 * 
 * returns: 0 if an error has ocurred or 1 if no errors
 * ------------------------------------------------------------------------------ */

int add_vertex(graph_t *g, char *name) ;

/* ------------------------------------------------------------------------------
 * function: remove_vertex 
 * ------------------------------------------------------------------------------
 * removes a vertex from the graph
 *
 * g: graph from which the vertex will be removed
 * v: vertex to be removed
 * 
 * returns: 0 if an error has ocurred or 1 if no errors
 * ------------------------------------------------------------------------------ */

int remove_vertex(graph_t *g, vertex_t *v) ;

/* ------------------------------------------------------------------------------
 * function: add_edge 
 * ------------------------------------------------------------------------------
 * inserts an edge between two vertices
 *
 * g: graph that the vertices belong to
 * v1: first vertex that will belong to that edge
 * v2: second vertex that will belong to that edge
 * 
 * returns: 0 if an error has ocurred or 1 if no errors
 * ------------------------------------------------------------------------------ */

int add_edge(graph_t *g, vertex_t *v1, vertex_t *v2) ;

/* ------------------------------------------------------------------------------
 * function: remove_edge 
 * ------------------------------------------------------------------------------
 * removes an edge between two vertices
 *
 * g: graph that the vertices belong to
 * v1: first vertex that will have the edge removed
 * v2: second vertex that will have the edge removed
 * 
 * returns: 0 if an error has ocurred or 1 if no errors
 * ------------------------------------------------------------------------------ */

int remove_edge(graph_t *g, vertex_t *v1, vertex_t *v2) ;

/* ------------------------------------------------------------------------------
 * function: search_edge 
 * ------------------------------------------------------------------------------
 * search for a specific edge in the vertex
 *
 * g: graph that the vertex and the edge belong to
 * e: specific edge to search
 * v: vertex to which the edge connects
 * 
 * returns: pointer to the edge found or NULL if not found
 * ------------------------------------------------------------------------------ */

edge_t *search_edge(graph_t *g, edge_t *e, vertex_t *v) ;

/* ------------------------------------------------------------------------------
 * function: print_graph 
 * ------------------------------------------------------------------------------
 * prints the graph with formatted output
 *
 * g: graph to be printed
 * ------------------------------------------------------------------------------ */

void print_graph(graph_t *g) ;

/* ------------------------------------------------------------------------------
 * function: vertex_count
 * ------------------------------------------------------------------------------
 * counts the number of vertices in a graph
 *
 * g: graph to have the vertices counted
 * 
 * returns: the number of vertices in that graph
 * ------------------------------------------------------------------------------ */

unsigned int vertex_count(graph_t *g) ;

/* ------------------------------------------------------------------------------
 * function: edge_count 
 * ------------------------------------------------------------------------------
 * counts the number of edges in a graph
 *
 * g: graph to have the edges counted
 * 
 * returns: the number of edges in that graph
 * ------------------------------------------------------------------------------ */

unsigned int edge_count(graph_t *g) ;

/* ------------------------------------------------------------------------------
 * function: get_vertex_by_name 
 * ------------------------------------------------------------------------------
 * searches for a vertex with a specific name in a graph
 *
 * g: graph in which the vertex will be searched
 * name: name of the vertex to be found
 * 
 * returns: pointer to the vertex found or NULL if not found
 * ------------------------------------------------------------------------------ */

vertex_t *get_vertex_by_name(graph_t *g, char *name) ;

/* ------------------------------------------------------------------------------
 * function: search_neighbourhood 
 * ------------------------------------------------------------------------------
 * verifies if there is neighbourhood between two vertices
 *
 * g: graph in which the vertices belong
 * v1: first vertex to search
 * v2: second vertex to search
 * 
 * returns: 1 if there is neighbourhood or 0 if there is not
 * ------------------------------------------------------------------------------ */

int search_neighbourhood(graph_t *g, vertex_t *v1, vertex_t *v2) ;

/* ------------------------------------------------------------------------------
 * function: search_array 
 * ------------------------------------------------------------------------------
 * searches for a vertex in an array of vertices
 *
 * g: graph in which the vertex belong to
 * v: vertex to be found
 * array: array of vertices
 * array_size: size of the array
 * 
 * returns: 1 if the vertex is found or 0 if it is not found
 * ------------------------------------------------------------------------------ */

int search_vertex_in_array(graph_t *g, vertex_t *v, vertex_t **array, unsigned int array_size) ;

/* ------------------------------------------------------------------------------
 * function: read_graph 
 * ------------------------------------------------------------------------------
 * reads a graph from an input
 *
 * name: name of the graph
 * input: input from which the graph will be read
 * 
 * returns: pointer to the read graph
 * ------------------------------------------------------------------------------ */

graph_t *read_graph(char *name, FILE *input) ;

/* ------------------------------------------------------------------------------
 * function: write_graph 
 * ------------------------------------------------------------------------------
 * writes a graph in the same format used in read_graph to an output
 *
 * g: graph that will be written
 * output: output in which the graph will be written
 * 
 * returns: pointer to the written graph or NULL if an error has ocurred
 * ------------------------------------------------------------------------------ */

graph_t *write_graph(graph_t *g, FILE *output) ;

/* ------------------------------------------------------------------------------
 * function: destroy_graph 
 * ------------------------------------------------------------------------------
 * deallocate all the memory used in a graph
 *
 * g: graph to have the memory deallocated
 * 
 * returns: 0 if an error has ocurred or 1 if no errors
 * ------------------------------------------------------------------------------ */

int destroy_graph(graph_t *g) ;

/* ------------------------------------------------------------------------------ */

#endif
