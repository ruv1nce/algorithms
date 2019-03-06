#include "libft.h"
#include "graph.h"

t_ladj	*lstnew(int vert, int wt)
{
	t_ladj	*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->vertex = vert;
	new->weight = wt;
	new->next = NULL;
	return (new);
}

int		lstadd_front(t_ladj **lst, int vert, int wt)
{
	t_ladj	*new;

	if (!(new = lstnew(vert, wt)))
		return (0);
	if (*lst)
		new->next = *lst;
	*lst = new;
	return (1);
}

int		lstadd_sort(t_ladj **lst, int vert, int wt)
{
	t_ladj	*new;
	t_ladj	*tmp;

	if (!(new = lstnew(vert, wt)))
		return (0);
	if (!*lst)
		*lst = new;
	else if ((*lst)->vertex > vert)
	{
		new->next = *lst;
		*lst = new;
	}
	else
	{
		tmp = *lst;
		while (tmp->next)
		{
			if ((tmp->next)->vertex > vert)
			{
				new->next = tmp->next;
				break ;
			}
			tmp = tmp->next;
		}
		tmp->next = new;
	}
	return (1);
}

void	lstdel(t_ladj **lst)
{
	t_ladj	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
	*lst = NULL;
}
