#ifndef QUEUE_H
# define QUEUE_H

# include <stdlib.h>

# define DEQ_ERR -2147483640

typedef struct		node
{
	int				vertex;
	struct node		*next;
}					node;

typedef struct		queue
{
	int				count;
	node			*head;
	node			*tail;
}					queue;

void				qinit(queue *q);
int					enqueue(queue *q, int value);
int					dequeue(queue *q);
void				qdel(queue *q);

#endif
