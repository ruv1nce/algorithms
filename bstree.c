#include "bstree.h"

/* implement a list of equal values for each node */

int		bstree_insert(t_node **root, int value)
{
	t_node	*new;
	t_node	*spot;

	if (!(new = malloc(sizeof(*new))))
		return (0);
	new->value = value;
	new->p = NULL;
	new->l = NULL;
	new->r = NULL;
	if (!*root)
		*root = new;
	else
	{
		spot = *root;
		while (spot)
		{
			new->p = spot;
			if (value < spot->value)
				spot = spot->l;
			else
				spot = spot->r;
		}
		if (value < new->p->value)
			new->p->l = new;
		else
			new->p->r = new;
	}
	return (1);
}

t_node	*bstree_search(t_node *root, int value)
{
	while (root)
	{
		if (value == root->value)
			return (root);
		else if (value < root->value)
			root = root->l;
		else
			root = root->r;
	}
	return (NULL);
}

t_node	*bstree_min(t_node *root)
{
	if (!root)
		return (NULL);
	while (root->l)
		root = root->l;
	return (root);
}

t_node	*bstree_max(t_node *root)
{
	if (!root)
		return (NULL);
	while (root->r)
		root = root->r;
	return (root);
}

void	bstree_transplant(t_node *root, t_node *trunk, t_node *sprout)
{
	/* if sprout goes in place of root */
	if (trunk == root)
		root = sprout;
	else
	{
		/* make sprout to be trunk parent's child */
		if (trunk == trunk->p->l)
			trunk->p->l = sprout;
		else
			trunk->p->r = sprout;
	}
	/* update sprout's parent */
	if (sprout)
		sprout->p = trunk->p;
}

void	bstree_delete(t_node *root, t_node *node)
{
	t_node	*successor;

	if (!node->l)
		bstree_transplant(root, node, node->r);
	else if (!node->r)
		bstree_transplant(root, node, node->l);
	else
	{
		successor = bstree_min(node->r);
		/* if successor is not node's right child, replace successor with
		 * its right child, then update successor's right child with node's */
		if (successor->p != node)
		{
			bstree_transplant(root, successor, successor->r);
			successor->r = node->r;
			successor->r->p = successor;
		}
		/* either if successor is node's right child or after replacing the successor,
		 * replace node with successor and update its left child with node's */
		bstree_transplant(root, node, successor);
		successor->l = node->l;
		successor->l->p = successor;
	}
	free(node);
}

void	bstree_burn(t_node **root)
{
	if (!*root)
		return ;
	bstree_burn(&(*root)->l);
	bstree_burn(&(*root)->r);
	free(*root);
	*root = NULL;
}

void	bstree_inorder(t_node *root)
{
	if (!root)
		return ;
	bstree_inorder(root->l);
	printf("%i ", root->value);
	bstree_inorder(root->r);
}

void	bstree_preorder(t_node *root)
{
	if (!root)
		return ;
	printf("%i ", root->value);
	bstree_preorder(root->l);
	bstree_preorder(root->r);
}

void	bstree_postorder(t_node *root)
{
	if (!root)
		return ;
	bstree_postorder(root->l);
	bstree_postorder(root->r);
	printf("%i ", root->value);
}

t_node	*bstree_successor(t_node *node)
{
	t_node	*parent;

	if (!node)
		return (NULL);
	/* if node has a right child, successor is the min node in node->r subtree */
	if (node->r)
		return (bstree_min(node->r));
	/* else successor the first (grand)parent which is connected to the subtree
	 * containing input node via a "->l" pointer */
	parent = node->p;
	while (parent && node == parent->r)
	{
		node = parent;
		parent = parent->p;
	}
	return (parent);
}

t_node	*bstree_predecessor(t_node *node)
{
	t_node	*parent;

	if (!node)
		return (NULL);
	/* if node has a left child, predecessor is the max node in node->l subtree */
	if (node->l)
		return (bstree_max(node->l));
	/* else successor the first (grand)parent which is connected to the subtree
	 * containing input node via a "->r" pointer */
	parent = node->p;
	while (parent && node == parent->l)
	{
		node = parent;
		parent = parent->p;
	}
	return (parent);
}

int		main(int argc, char **argv)
{
	t_node	*root;
	t_node	*tmp;
	int		i;

	/* arguments for testing: 24 13 56 3 22 43 42 -5 8 99 5 9 7 6 23 */
	if (argc > 1)
	{
		root = NULL;
		i = 0;
		while (++i < argc)
			if (!(bstree_insert(&root, atoi(argv[i]))))
				return (1);
		printf("in   ");
		bstree_inorder(root);
		printf("\n");
		printf("pre  ");
		bstree_preorder(root);
		printf("\n");
		printf("post ");
		bstree_postorder(root);
		printf("\n");

		if ((tmp = bstree_max(root)))
			printf("max %i, ", tmp->value);
		if ((tmp = bstree_min(root)))
			printf("min %i\n", tmp->value);

		if ((tmp = bstree_search(root, 13)))
			printf("%2i's suc ", tmp->value);
		if ((tmp = bstree_successor(tmp)))
			printf("%2i\n", tmp->value);
		if ((tmp = bstree_search(root, 8)))
			printf("%2i's suc ", tmp->value);
		if ((tmp = bstree_successor(tmp)))
			printf("%2i\n", tmp->value);

		if ((tmp = bstree_search(root, 13)))
			printf("%2i's pre ", tmp->value);
		if ((tmp = bstree_predecessor(tmp)))
			printf("%2i\n", tmp->value);
		if ((tmp = bstree_search(root, 42)))
			printf("%2i's pre ", tmp->value);
		if ((tmp = bstree_predecessor(tmp)))
			printf("%2i\n", tmp->value);

		if ((tmp = bstree_search(root, 3)))
			bstree_delete(root, tmp);
		printf("in   ");
		bstree_inorder(root);
		printf("\n");
		if ((tmp = bstree_search(root, 9)))
			bstree_delete(root, tmp);
		printf("in   ");
		bstree_inorder(root);
		printf("\n");
		if ((tmp = bstree_search(root, 43)))
			bstree_delete(root, tmp);
		printf("in   ");
		bstree_inorder(root);
		printf("\n");
		if ((tmp = bstree_search(root, 22)))
			bstree_delete(root, tmp);
		printf("in   ");
		bstree_inorder(root);
		printf("\n");

		bstree_burn(&root);
		printf("%p\n", root);
		bstree_inorder(root);
	}
}
