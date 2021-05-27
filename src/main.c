#include <stdio.h>
#include "graph.h"

/* ------------------------------------------------------------------------------ */

int main (void)
{
  graph_t *g = read_graph("new_graph", stdin);
  printf("info:\n\nvertices: %d\nedges: %d\n\n", vertex_count(g), edge_count(g));
  printf("formatted output:\n\n");
  print_graph(g);
  printf("\n\nnormal output:\n\n");
  write_graph(g, stdout);
  destroy_graph(g);
  return 0;
}
