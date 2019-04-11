node	*lstnew(void)
{
	node	*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->next = NULL;
	return (new);
}

int		lstadd(node **lst)
{
	node	*new;

	if (!(new = lstnew()))
		return (0);
	if (*lst)
		new->next = *lst;
	*lst = new;
	return (1);
}

void	lstdel(node **lst)
{
	node	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
	*lst = NULL;
}
