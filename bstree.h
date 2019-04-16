#ifndef BSTREE_H
# define BSTREE_H

# include <stdlib.h>
# include <stdio.h>

typedef struct		s_node
{
	int				value;
	int				desc;
	struct s_node	*p;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

struct s_node   *convert_bst(struct s_node *bst);
int				can_split(struct s_node *n);

#endif
