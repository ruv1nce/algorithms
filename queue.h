#ifndef QUEUE_H
# define QUEUE_H

typedef struct		node
{
	int				vertex;
	struct s_list	*next;
}					node;

typedef struct		queue
{
	int				count;
	node			*first;
	node			*last;
}					queue;

#endif
