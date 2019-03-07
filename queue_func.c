#include "queue.h"
#include "graph.h"

void	qinit(queue *q)
{
	q->count = 0;
	q->first = NULL;
	q->last = NULL;
}

int		enqueue(queue *q, int value)
{
	node	*new;

	if (!(new = malloc(sizeof(*new))))
		return (0);
	new->next = NULL;
	if (!(q->first))
	{
		q->first = new;
		q->last = new;
	}
	else
	{
		q->last->next = new;
		q->last = new;
	}
	return (1);
}

int		dequeue(queue *q)
{
	int		value;
	node	*tmp;

	tmp = q->first;
	value = tmp->vertex;
	q->first = q->first->next;
	q->count--;
	free(tmp);
}

void	qdel(queue *q)
{
	node	*tmp;

	while (q->first)
	{
		tmp = q->first;
		q->first = q->first->next;
		free(tmp);
	}
	q->first = NULL;
}
