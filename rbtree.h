#ifndef BSTREE_H
# define BSTREE_H

# include <stdlib.h>
# include <stdio.h>

typedef struct		s_node
{
	char			color;
	int				value;
	struct s_node	*p;
	struct s_node	*l;
	struct s_node	*r;
}					t_node;

#endif
