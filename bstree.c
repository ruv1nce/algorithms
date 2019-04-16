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
	new->left = NULL;
	new->right = NULL;
	new->desc = 0;
	if (!*root)
		*root = new;
	else
	{
		spot = *root;
		while (spot)
		{
			new->p = spot;
			if (value < spot->value)
				spot = spot->left;
			else
				spot = spot->right;
		}
		if (value < new->p->value)
			new->p->left = new;
		else
			new->p->right = new;
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
			root = root->left;
		else
			root = root->right;
	}
	return (NULL);
}

t_node	*bstree_min(t_node *root)
{
	if (!root)
		return (NULL);
	while (root->left)
		root = root->left;
	return (root);
}

t_node	*bstree_max(t_node *root)
{
	if (!root)
		return (NULL);
	while (root->right)
		root = root->right;
	return (root);
}

void	bstree_transplant(t_node **root, t_node *trunk, t_node *sprout)
{
	/* if sprout goes in place of root */
	if (trunk == *root)
		*root = sprout;
	else
	{
		/* make sprout to be trunk parent's child */
		if (trunk == trunk->p->left)
			trunk->p->left = sprout;
		else
			trunk->p->right = sprout;
	}
	/* update sprout's parent */
	if (sprout)
		sprout->p = trunk->p;
}

void	bstree_delete(t_node **root, t_node *node)
{
	t_node	*successor;

	if (!node->left)
		bstree_transplant(root, node, node->right);
	else if (!node->right)
		bstree_transplant(root, node, node->left);
	else
	{
		successor = bstree_min(node->right);
		/* if successor is not node's right child, replace successor with
		 * its right child, then update successor's right child with node's */
		if (successor->p != node)
		{
			bstree_transplant(root, successor, successor->right);
			successor->right = node->right;
			successor->right->p = successor;
		}
		/* either if successor is node's right child or after replacing the successor,
		 * replace node with successor and update its left child with node's */
		bstree_transplant(root, node, successor);
		successor->left = node->left;
		successor->left->p = successor;
	}
	free(node);
}

void	bstree_burn(t_node **root)
{
	if (!*root)
		return ;
	bstree_burn(&(*root)->left);
	bstree_burn(&(*root)->right);
	free(*root);
	*root = NULL;
}

/* mode == 1 - print with descendants count */
void	bstree_inorder(t_node *root, int mode)
{
	if (!root)
		return ;
	bstree_inorder(root->left, mode);
	printf("%i", root->value);
	if (mode == 1)
		printf(".%i", root->desc);
	printf(" ");
	bstree_inorder(root->right, mode);
}

void	bstree_preorder(t_node *root)
{
	if (!root)
		return ;
	printf("%i ", root->value);
	bstree_preorder(root->left);
	bstree_preorder(root->right);
}

void	bstree_postorder(t_node *root)
{
	if (!root)
		return ;
	bstree_postorder(root->left);
	bstree_postorder(root->right);
	printf("%i ", root->value);
}

t_node	*bstree_successor(t_node *node)
{
	t_node	*parent;

	if (!node)
		return (NULL);
	/* if node has a right child, successor is the min node in node->right subtree */
	if (node->right)
		return (bstree_min(node->right));
	/* else successor is the first (grand)parent which is connected to the subtree
	 * containing input node via a "->left" pointer */
	parent = node->p;
	while (parent && node == parent->right)
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
	/* if node has a left child, predecessor is the max node in node->left subtree */
	if (node->left)
		return (bstree_max(node->left));
	/* else successor the first (grand)parent which is connected to the subtree
	 * containing input node via a "->right" pointer */
	parent = node->p;
	while (parent && node == parent->left)
	{
		node = parent;
		parent = parent->p;
	}
	return (parent);
}

int	bstree_descendants(t_node *root)
{
	int	desc;

	if (root)
	{
		desc = 0;
		desc += bstree_descendants(root->left);
		desc += bstree_descendants(root->right);
		root->desc = desc;
		return (desc + 1);
	}
	return (0);
}

t_node	*bstree_dup(t_node *root, t_node *p)
{
	t_node	*node;

	node = NULL;
	if (root)
	{
		/* create new node */
		node = malloc(sizeof(*node));
		node->value = root->value;
		node->desc = root->desc;
		/* if a parent exists, connect it to node */
		if (p)
		{
			node->p = p;
			if (root == root->p->left)
				node->p->left = node;
			else	
				node->p->right = node;
		}
		else
			node->p = NULL;
		/* go left if there's a left child, then right, else put NULL */
		if (root->left)
			bstree_dup(root->left, node);
		else
			node->left = NULL;
		if (root->right)
			bstree_dup(root->right, node);
		else
			node->right = NULL;
	}
	return (node);
}

int		main(int argc, char **argv)
{
	t_node	*root;
	t_node	*newtree;
//	t_node	*tmp;
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
		bstree_inorder(root, 0);
		printf("\n");
		printf("pre  ");
		bstree_preorder(root);
		printf("\n");
		printf("post ");
		bstree_postorder(root);
		printf("\n");

/*		if ((tmp = bstree_max(root)))
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

		printf("root: %i\n", root->value);
		if ((tmp = bstree_search(root, 3)))
			bstree_delete(&root, tmp);
		printf("in   ");
		bstree_inorder(root, 0);
		printf("\n");
		if ((tmp = bstree_search(root, 9)))
			bstree_delete(&root, tmp);
		printf("in   ");
		bstree_inorder(root, 0);
		printf("\n");
		if ((tmp = bstree_search(root, 43)))
			bstree_delete(&root, tmp);
		printf("in   ");
		bstree_inorder(root, 0);
		printf("\n");
		if ((tmp = bstree_search(root, 22)))
			bstree_delete(&root, tmp);
		printf("in   ");
		bstree_inorder(root, 0);
		printf("\n");

		bstree_delete(&root, root);
		printf("in   ");
		bstree_inorder(root, 0);
		printf("\n");
		printf("new root: %i\n", root->value);*/

		/* convert_bst exam question 
		printf("circular\n");
		root = convert_bst(root);
		tmp = root;
		i = 1;
		while (i || tmp != root)
		{
			printf("%i ", root->value);
			root = root->right;
			i = 0;
		}
		printf("\n full circle %i\n", root->value);*/

		printf("descendants\n");
		printf("in   ");
		bstree_inorder(root, 1);
		bstree_descendants(root);
		printf("\nin   ");
		bstree_inorder(root, 1);
		printf("\n");

		printf("duplicate\n");
		newtree = bstree_dup(root, NULL);
		printf("in   ");
		bstree_inorder(newtree, 1);
		printf("\n");

//		can_split(root);

		printf("width: %i\n", width_tree(root));
		printf("width: %i\n", width_tree(NULL));

		bstree_burn(&root);
//		printf("%p\n", root);
//		bstree_inorder(root, 0);

		bstree_burn(&newtree);
//		printf("%p\n", newtree);
//		bstree_inorder(newtree, 0);
	}
}
