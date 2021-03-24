#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "queue.h"

/* ------------------------------------------------------------------------------ */

graph_t *create_graph(char *name)
{
  graph_t *g;

  if (!(g = (graph_t *) malloc(sizeof(graph_t))))
  {
    perror("memory allocation failed");
    exit(1);
  }

  if (!(g->name = (char *) malloc(strlen(name))))
  {
    perror("memory allocation failed");
    exit(1);
  }

  strncpy(g->name, name, strlen(name));

  return g;
}

/* ------------------------------------------------------------------------------ */

int add_vertex(graph_t *g, char *name)
{
  if (!g || !name)
    return 0;

  vertex_t *new_vertex;

  if (!(new_vertex = (vertex_t *) malloc(sizeof(vertex_t))))
  {
    perror("memory allocation failed");
    exit(1);
  }

  new_vertex->degree = 0;

  if (!(new_vertex->name = (char *) malloc(strlen(name))))
  {
    perror("memory allocation failed");
    exit(1);
  }

  strncpy(new_vertex->name, name, strlen(name));
  queue_append((queue_t **) &(g->vertices), (queue_t *) new_vertex);
  return 1;
}

/* ------------------------------------------------------------------------------ */

int remove_vertex(graph_t *g, vertex_t *v)
{
  if (!g || !v)
    return 0;

  while(v->edges)
    remove_edge(g, v, v->edges->vertex); // removes all the edges from the vertex

  free(v->name);
  free(queue_remove((queue_t **) &(g->vertices), (queue_t *) v)); // removes the vertex

  return 1;
}

/* ------------------------------------------------------------------------------ */

int add_edge(graph_t *g, vertex_t *v1, vertex_t *v2)
{
  if (!g || !v1 || !v2)
    return 0;

  edge_t *aux_edge;

  if (!(aux_edge = (edge_t *) malloc(sizeof(edge_t))))
  {
    perror("memory allocation failed");
    exit(1);
  }

  aux_edge->vertex = v2;
  queue_append((queue_t **) &(v1->edges), (queue_t *) aux_edge); // inserts v2 em v1
  v1->degree++;

  if (!(aux_edge = (edge_t *) malloc(sizeof(edge_t))))
  {
    perror("memory allocation failed");
    exit(1);
  }

  aux_edge->vertex = v1;
  queue_append((queue_t **) &(v2->edges), (queue_t *) aux_edge); // inserts v1 em v2
  v2->degree++;

  return 1;
}

/* ------------------------------------------------------------------------------ */

int remove_edge(graph_t *g, vertex_t *v1, vertex_t *v2)
{
  if (!g || !v1 || !v2)
    return 0;

  edge_t *aux_edge;

  if ((aux_edge = search_edge(g, v1->edges, v2)))
  {
    free(queue_remove((queue_t **) &(v1->edges), (queue_t *) aux_edge)); // removes v2 from v1
    v1->degree--;
  }

  if ((aux_edge = search_edge(g, v2->edges, v1)))
  {
    free(queue_remove((queue_t **) &(v2->edges), (queue_t *) aux_edge)); // removes v1 from v2
    v2->degree--;
  }

  return 1;
}

/* ------------------------------------------------------------------------------ */

edge_t *search_edge(graph_t *g, edge_t *e, vertex_t *v)
{
  if (!g || !e || !v)
    return NULL;

  edge_t *aux_edge = e;

  do
    if (aux_edge->vertex == v) // if the edge is found
      return aux_edge;
  while ((aux_edge = aux_edge->next) != e);

  return NULL;
}

/* ------------------------------------------------------------------------------ */

void print_graph(graph_t *g)
{
  if (!g)
    return;

  vertex_t *aux_vertex = g->vertices;
  edge_t *aux_edge;

  printf(" graph: %s\n", g->name);

  for (unsigned int i = 0; i < queue_size((queue_t *) (g->vertices)); ++i)
  {
    printf("%2d (%s)", i, aux_vertex->name);

    if ((aux_edge = aux_vertex->edges)) // if there are edges
      do
        printf(" -> %s", aux_edge->vertex->name);
      while ((aux_edge = aux_edge->next) != aux_vertex->edges);

    aux_vertex = aux_vertex->next;
    printf("\n");
  }
}

/* ------------------------------------------------------------------------------ */

unsigned int vertex_count(graph_t *g)
{
  return queue_size((queue_t *) g->vertices);
}

/* ------------------------------------------------------------------------------ */

unsigned int edge_count(graph_t *g)
{
  vertex_t *aux_vertex = g->vertices;
  int sum = 0;

  do
    sum += aux_vertex->degree; // sum all the vertices degrees
  while ((aux_vertex = aux_vertex->next) != g->vertices);

  return (unsigned int) (sum/2);
}

/* ------------------------------------------------------------------------------ */

vertex_t *get_vertex_by_name(graph_t *g, char *name)
{
  vertex_t *aux_vertex = g->vertices;

  for (unsigned int i = 0; i < queue_size((queue_t *) g->vertices); ++i)
  {
    if (!strncmp(aux_vertex->name, name, strlen(name))) // if the vertex has that name 
      return aux_vertex;

    aux_vertex = aux_vertex->next;
  }

  return NULL;
}

/* ------------------------------------------------------------------------------ */

int search_neighbourhood(graph_t *g, vertex_t *v1, vertex_t *v2)
{
  if (!g || !v1 || !v2)
    return 0;

  int hasEdge = 0;
  edge_t *aux_edge;

  if ((aux_edge = v1->edges))
    do
      if (aux_edge->vertex == v2) // checks if v1 has v2 as a neighbour
        hasEdge++;
    while ((aux_edge = aux_edge->next) != v1->edges);

  if ((aux_edge = v2->edges))
    do
      if (aux_edge->vertex == v1) // checks if v2 has v1 as a neighbour
        hasEdge++;
    while ((aux_edge = aux_edge->next) != v2->edges);

  return hasEdge ? 1 : 0; // returns 1 if it has an edge or 0 if it has not
}

/* ------------------------------------------------------------------------------ */

int search_vertex_in_array(graph_t *g, vertex_t *v, vertex_t **array, unsigned int array_size)
{
  if (!g || !v || !array)
    return 0;

  for (unsigned int i = 0; i < array_size; ++i)
    if (array[i] == v) // if the vertex is found
      return 1;

  return 0;
}

/* ------------------------------------------------------------------------------ */

graph_t *read_graph(char *name, FILE *input)
{
  char *graph_name;

  if (!(graph_name = (char *) malloc(strlen(name))))
  {
    perror("memory allocation failed");
    exit(1);
  }

  strncpy(graph_name, name, strlen(name));

  char *vertex_name[2];
  char str[STRING_SIZE]; // read input containing the vertices names

  graph_t *g = create_graph(graph_name);
  vertex_t *vertex_1, *vertex_2;

  while (fgets(str, STRING_SIZE, input) != NULL) // while reads something from the input
    if (str[0] != '\n') // ignores the line breaks
      if ((vertex_name[0] = strtok(str, " \n"))) // if there is a vertex
      {
        if (!get_vertex_by_name(g, vertex_name[0])) // checks if the vertex already exists
          add_vertex(g, vertex_name[0]);

        if ((vertex_name[1] = strtok(NULL, " \n"))) // if there is another vertex to add
        {
          if (!get_vertex_by_name(g, vertex_name[1]))
            add_vertex(g, vertex_name[1]);

          vertex_1 = get_vertex_by_name(g, vertex_name[0]);
          vertex_2 = get_vertex_by_name(g, vertex_name[1]);

          if (!search_neighbourhood(g, vertex_1, vertex_2)) // checks if an edge between the two vertices already exists
            add_edge(g, vertex_1, vertex_2);
        }
      }

  return g;
}

/* ------------------------------------------------------------------------------ */

graph_t *write_graph(graph_t *g, FILE *output)
{
  if (!g || !output)
  {
    perror("Output failed");
    return NULL;
  }

  edge_t *aux_edge;
  vertex_t *aux_vertex, **visited;
  unsigned int vertex_list_size = queue_size((queue_t *) g->vertices), i = 0, array_size = 0;

  if (!(visited = (vertex_t **) malloc((long unsigned int) vertex_list_size * sizeof(vertex_t *))))
  {
    perror("memory allocation failed");
    exit(1);
  }

  if ((aux_vertex = g->vertices))
    do
    {
      if ((aux_edge = aux_vertex->edges)) // if it has edges
        do
          if (!search_vertex_in_array(g, aux_edge->vertex, visited, array_size)) // if the vertex was not written
            fprintf(output, "%s %s\n", aux_vertex->name, aux_edge->vertex->name);
        while ((aux_edge = aux_edge->next) != aux_vertex->edges);
      else
        fprintf(output, "%s\n", aux_vertex->name);

      visited[i++] = aux_vertex;
      array_size++;
    }
    while ((aux_vertex = aux_vertex->next) != g->vertices);

  free(visited);
  return g;
}

/* ------------------------------------------------------------------------------ */

int destroy_graph(graph_t * g)
{
  if (!g)
  {
    perror("Could not free memory");
    return 0;
  }

  while (g->vertices) // while there is vertices to be removed
    remove_vertex(g, g->vertices);

  free(g->name);
  free(g);
  return 1;
}
