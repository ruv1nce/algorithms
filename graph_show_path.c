#include "graph.h"
#include <stdio.h>

void	show_path(t_vert *graph, int dest)
{
	if (graph[dest].parent == -1)
		printf("%i ", dest);
	else
	{
		show_path(graph, graph[dest].parent);
		printf("%i ", dest);
	}
}
