#include "queue.h"
#include "graph.h"

int	bfs(t_ladj **lgraph)
{
	queue	q;
	
	qinit(&q);
	enqueue(&q, 5);
	enqueue(&q, 7);
	enqueue(&q, 10);
	dequeue(&q);
	dequeue(&q);
	dequeue(&q);
	dequeue(&q);
}
