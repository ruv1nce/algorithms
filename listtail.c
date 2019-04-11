void	lstinit(t_list *l)
{
	l->count = 0;
	l->head = NULL;
	l->tail = NULL;
}

int		addtail(t_list *l)
{
	node	*new;

	if (!(new = malloc(sizeof(*new))))
		return (0);
	new->put = 0;
	new->next = NULL;
	if (!(l->head))
	{
		l->head = new;
		l->tail = new;
	}
	else
	{
		l->tail->next = new;
		l->tail = new;
	}
	l->count++;
	return (1);
}

void	lstdel(t_list *l)
{
	node	*tmp;

	while (l->head)
	{
		tmp = l->head;
		l->head = l->head->next;
		free(tmp);
	}
	l->count = 0;
	l->head = NULL;
	l->tail = NULL;
}
