#include "queue.h"
#include "graph.h"

/* requires graph_create.c, queue_func.c, graph_list.c to compile */

void	bfs(t_vert *graph, int s)
{
	queue	q;
	int		v;
	t_ladj	*tmp;
	
	qinit(&q);
	graph[s].color = gray;
	graph[s].distance = 0;
	enqueue(&q, s);
	while (q.head)
	{
		s = dequeue(&q);
		tmp = graph[s].kids;
		while (tmp)
		{
			v = tmp->vertex;
			if (graph[v].color == white)
			{
				graph[v].color = gray;
				graph[v].distance = graph[s].distance + 1;
				graph[v].parent = s;
				enqueue(&q, v);
			}
			tmp = tmp->next;
		}
		graph[s].color = black;
	}
}
