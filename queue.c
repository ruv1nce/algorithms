#include "queue.h"
#include "graph.h"
#include <stdio.h>

void	qprint(queue *q)
{
	node	*tmp;

	tmp = q->head;
	if (tmp)
	{
		printf("cnt %i: ", q->count);
		while (tmp)
		{
			printf("%i, ", tmp->vertex);
			tmp = tmp->next;
		}
		printf("\n");
	}
	else
	{
		printf("cnt %i: ", q->count);
		printf("<empty>\n");
	}
}

int		main(void)	
{
	queue	q;
	
	qinit(&q);
	qprint(&q);
	enqueue(&q, 5);
	qprint(&q);
	enqueue(&q, 7);
	qprint(&q);
	enqueue(&q, 10);
	qprint(&q);
	if (q.count)
		dequeue(&q);
	qprint(&q);
	if (q.count)
		dequeue(&q);
	qprint(&q);
	if (q.count)
		dequeue(&q);
	qprint(&q);
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	qprint(&q);
	qdel(&q);
	qprint(&q);
}
