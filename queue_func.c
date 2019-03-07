#include "queue.h"
#include "graph.h"

void	qinit(queue *q)
{
	q->count = 0;
	q->head = NULL;
	q->tail = NULL;
}

int		enqueue(queue *q, int value)
{
	node	*new;

	if (!(new = malloc(sizeof(*new))))
		return (0);
	new->vertex = value;
	new->next = NULL;
	if (!(q->head))
	{
		q->head = new;
		q->tail = new;
	}
	else
	{
		q->tail->next = new;
		q->tail = new;
	}
	q->count++;
	return (1);
}

int		dequeue(queue *q)
{
	int		value;
	node	*tmp;

	if (!(q->count))
		return (DEQ_ERR);
	tmp = q->head;
	value = tmp->vertex;
	q->head = q->head->next;
	if (!(q->count--))
		q->tail = NULL;
	free(tmp);
	return (value);
}

void	qdel(queue *q)
{
	node	*tmp;

	while (q->head)
	{
		tmp = q->head;
		q->head = q->head->next;
		free(tmp);
	}
	q->count = 0;
	q->head = NULL;
	q->tail = NULL;
}
