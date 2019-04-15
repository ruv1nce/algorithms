#include "rbtree.h"

/* BUGS! */

/* implement a list of equal values for each node */

void	rbtree_rot_left(t_node **root, t_node *nil, t_node *x)
{
	t_node	*y;

	/* set y as x's right child */
	y = x->r;
	/* turn y's left subtree into x's right subtree */
	x->r = y->l;
	if (y->l != nil)
		y->l->p = x;
	/* set y's parent */
	y->p = x->p;
	/* if x was root, set y as new root */
	if (x->p == nil)
		*root = y;
	/* else make y appropriate child of x's parent */
	else if (x == x->p->l)
		x->p->l = y;
	else
		x->p->r = y;
	/* make x to be y's left child */
	y->l = x;
	x->p = y;
}

void rbtree_rot_right(t_node **root, t_node *nil, t_node *x)
{
	t_node	*y;

	/* set y as x's left child */
	y = x->l;
	/* turn y's right subtree into x's left subtree */
	x->l = y->r;
	if (y->r != nil)
		y->r->p = x;
	/* set y's parent */
	y->p = x->p;
	/* if x was root, set y as new root */
	if (x->p == nil)
		*root = y;
	/* else make y appropriate child of x's parent */
	else if (x == x->p->l)
		x->p->l = y;
	else
		x->p->r = y;
	/* make x to be y's right child */
	y->r = x;
	x->p = y;
}

void	rbtree_insert_fixup(t_node **root, t_node *nil, t_node *new)
{
	t_node	*uncle;

	while (new->p->color == 'r')
	{
		/* if new's parent is a left child of new's grandparent */
		if (new->p == new->p->p->l)
		{
			uncle = new->p->p->r;
			/* case 1: new's uncle is red - recolor two levels up */
			if (uncle->color == 'r')
			{
				new->p->color = 'b';
				new->p->p->color = 'r';
				uncle->color = 'b';
				new = new->p->p;
			}
			else
			{
				/* case 2: new's uncle is black and new is a right child - go up
				 * one level and left rotate the tree so case 2 transforms to case 3 */
				if (new == new->p->r)
				{
					new = new->p;
					rbtree_rot_left(root, nil, new);
				}
				/* case 3: new's uncle is black and new is a left child -
				 * recolor two levels up and right rotate the grandparent */
				new->p->color = 'b';
				new->p->p->color = 'r';
				rbtree_rot_right(root, nil, new->p->p);
			}
		}
		else
		{
			uncle = new->p->p->l;
			/* case 1: new's uncle is red - recolor two levels up */
			if (uncle->color == 'r')
			{
				new->p->color = 'b';
				new->p->p->color = 'r';
				uncle->color = 'b';
				new = new->p->p;
			}
			else
			{
				/* case 2: new's uncle is black and new is a left child - go up
				 * one level and right rotate the tree so case 2 transforms to case 3 */
				if (new == new->p->l)
				{
					new = new->p;
					rbtree_rot_right(root, nil, new);
				}
				/* case 3: new's uncle is black and new is a right child -
				 * recolor two levels up and left rotate the grandparent */
				new->p->color = 'b';
				new->p->p->color = 'r';
				rbtree_rot_left(root, nil, new->p->p);
			}
		}
	}
	(*root)->color = 'b';
}

int		rbtree_insert(t_node **root, t_node *nil, int value)
{
	t_node	*new;
	t_node	*spot;

	if (!(new = malloc(sizeof(*new))))
		return (0);
	new->value = value;
	new->p = nil;
	new->l = nil;
	new->r = nil;
	if (*root == nil)
	{
		*root = new;
		new->color = 'b';
	}
	else
	{
		new->color = 'r';
		spot = *root;
		/* find the spot to fit new node, updating new's parent in each loop */
		while (spot != nil)
		{
			new->p = spot;
			if (value < spot->value)
				spot = spot->l;
			else
				spot = spot->r;
		}
		/* put new as a left or right child of new->p */
		if (value < new->p->value)
			new->p->l = new;
		else
			new->p->r = new;
		rbtree_insert_fixup(root, nil, new);
	}
	return (1);
}

t_node	*rbtree_search(t_node *root, t_node *nil, int value)
{
	while (root != nil)
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

t_node	*rbtree_min(t_node *root, t_node *nil)
{
	if (root == nil)
		return (NULL);
	while (root->l != nil)
		root = root->l;
	return (root);
}

t_node	*rbtree_max(t_node *root, t_node *nil)
{
	if (root == nil)
		return (NULL);
	while (root->r != nil)
		root = root->r;
	return (root);
}

void	rbtree_transplant(t_node **root, t_node *trunk, t_node *sprout)
{
	/* if sprout goes in place of root */
	if (trunk == *root)
		*root = sprout;
	else
	{
		/* make sprout to be trunk parent's child */
		if (trunk == trunk->p->l)
			trunk->p->l = sprout;
		else
			trunk->p->r = sprout;
	}
	/* update sprout's parent */
	sprout->p = trunk->p;
}

void	rbtree_delete_fixup(t_node **root, t_node *nil, t_node *x)
{
	t_node	*sibling;

	while (x != *root && x->color == 'b')
	{
		if (x == x->p->l)
		{
			sibling = x->p->r;
			/* case 1: sibling is red, switch color of sibling and parent, and then
			 * perform a left rotation on parent > now sibling is black (cases 2,3,4) */
			if (sibling->color == 'r')
			{
				sibling->color = 'b';
				x->p->color = 'r';
				rbtree_rot_left(root, nil, x->p);
				sibling = x->p->r;
			}
			/* case 2: sibling is black, both of sibling's children are black */
			if (sibling->l->color == 'b' && sibling->r->color == 'b')
			{
				sibling->color = 'r';
				x = x->p;
			}
			/* case 3: sibling is black, its left child is red and right child is black;
			 * transforms to case 4 - sibling's right child is red */
			else if (sibling->r->color == 'b')
			{
				sibling->l->color = 'b';
				sibling->color = 'r';
				rbtree_rot_right(root, nil, sibling);
				sibling = x->p->r;
			}
			if (sibling->color == 'b' && sibling->r->color == 'r')
			{
				sibling->color = x->p->color;
				x->p->color = 'b';
				sibling->r->color = 'b';
				rbtree_rot_left(root, nil, x->p);
				x = *root;
			}
		}
		else
		{
			sibling = x->p->l;
			/* case 1: sibling is red, switch color of sibling and parent, and then
			 * perform a right rotation on parent > now sibling is black (cases 2,3,4) */
			if (sibling->color == 'r')
			{
				sibling->color = 'b';
				x->p->color = 'r';
				rbtree_rot_right(root, nil, x->p);
				sibling = x->p->l;
			}
			/* case 2: sibling is black, both of sibling's children are black */
			if (sibling->l->color == 'b' && sibling->r->color == 'b')
			{
				sibling->color = 'r';
				x = x->p;
			}
			/* case 3: sibling is black, its right child is red and left child is black;
			 * transforms to case 4 - sibling's left child is red */
			else if (sibling->l->color == 'b')
			{
				sibling->r->color = 'b';
				sibling->color = 'r';
				rbtree_rot_left(root, nil, sibling);
				sibling = x->p->l;
			}
			if (sibling->color == 'b' && sibling->l->color == 'r')
			{
				sibling->color = x->p->color;
				x->p->color = 'b';
				sibling->l->color = 'b';
				rbtree_rot_right(root, nil, x->p);
				x = *root;
			}
		}
	}
}

void	rbtree_delete(t_node **root, t_node *nil, t_node *node)
{
	t_node	*y;
	t_node	*x;
	char	y_orig_color;

	y = node;
	y_orig_color = y->color;
	if (node->l == nil)
	{
		x = node->r;
		rbtree_transplant(root, node, node->r);
	}
	else if (node->r == nil)
	{
		x = node->l;
		rbtree_transplant(root, node, node->l);
	}
	else
	{
		y = rbtree_min(node->r, nil);
		y_orig_color = y->color;
		x = y->r;
		/* if y is node's child, update x's parent for later fixup */
		if (y->p == node)
			x->p = y;
		/* if y is not node's child, replace y with its right
		 * child, then update y's right child with node's */
		else
		{
			rbtree_transplant(root, y, y->r);
			y->r = node->r;
			y->r->p = y;
		}
		/* either if y is node's right child or after replacing the y,
		 * replace node with y and update its left child with node's */
		rbtree_transplant(root, node, y);
		y->l = node->l;
		y->l->p = y;
		y->color = node->color;
	}
	free(node);
	if (y_orig_color == 'b')
		rbtree_delete_fixup(root, nil, x);
}

void	rbtree_burn(t_node **root)
{
	if (!*root)
		return ;
	rbtree_burn(&(*root)->l);
	rbtree_burn(&(*root)->r);
	free(*root);
	*root = NULL;
}

void	rbtree_inorder(t_node *root, t_node *nil)
{
	if (root == nil)
		return ;
	rbtree_inorder(root->l, nil);
	printf("%i%c ", root->value, root->color);
	rbtree_inorder(root->r, nil);
}

void	rbtree_preorder(t_node *root, t_node *nil)
{
	if (root == nil)
		return ;
	printf("%i%c ", root->value, root->color);
	rbtree_preorder(root->l, nil);
	rbtree_preorder(root->r, nil);
}

void	rbtree_postorder(t_node *root, t_node *nil)
{
	if (root == nil)
		return ;
	rbtree_postorder(root->l, nil);
	rbtree_postorder(root->r, nil);
	printf("%i%c ", root->value, root->color);
}

t_node	*rbtree_successor(t_node *node, t_node *nil)
{
	t_node	*parent;

	if (!node)
		return (NULL);
	/* if node has a right child, successor is the min node in node->r subtree */
	if (node->r != nil)
		return (rbtree_min(node->r, nil));
	/* else successor the first (grand)parent which is connected to the subtree
	 * containing input node via a "->l" pointer */
	parent = node->p;
	while (parent != nil && node == parent->r)
	{
		node = parent;
		parent = parent->p;
	}
	return (parent);
}

t_node	*rbtree_predecessor(t_node *node, t_node *nil)
{
	t_node	*parent;

	if (!node)
		return (NULL);
	/* if node has a left child, predecessor is the max node in node->l subtree */
	if (node->l != nil)
		return (rbtree_max(node->l, nil));
	/* else successor the first (grand)parent which is connected to the subtree
	 * containing input node via a "->r" pointer */
	parent = node->p;
	while (parent != nil && node == parent->l)
	{
		node = parent;
		parent = parent->p;
	}
	return (parent);
}

int		main(int argc, char **argv)
{
	t_node	*root;
	t_node	nil;
	nil.color = 'b';
	t_node	*tmp;
	int		i;

	/* arguments for testing: 24 13 56 3 22 43 42 -5 8 99 5 9 7 6 23 */
	if (argc > 1)
	{
		root = &nil;
		i = 0;
		while (++i < argc)
			if (!(rbtree_insert(&root, &nil, atoi(argv[i]))))
				return (1);
		printf("in   ");
		rbtree_inorder(root, &nil);
		printf("\n");
		printf("pre  ");
		rbtree_preorder(root, &nil);
		printf("\n");
		printf("post ");
		rbtree_postorder(root, &nil);
		printf("\n");

		if ((tmp = rbtree_max(root, &nil)))
			printf("max %i, ", tmp->value);
		if ((tmp = rbtree_min(root, &nil)))
			printf("min %i\n", tmp->value);

		if ((tmp = rbtree_search(root, &nil, 13)))
			printf("%2i's suc ", tmp->value);
		if ((tmp = rbtree_successor(tmp, &nil)))
			printf("%2i\n", tmp->value);
		if ((tmp = rbtree_search(root, &nil, 8)))
			printf("%2i's suc ", tmp->value);
		if ((tmp = rbtree_successor(tmp, &nil)))
			printf("%2i\n", tmp->value);

		if ((tmp = rbtree_search(root, &nil, 13)))
			printf("%2i's pre ", tmp->value);
		if ((tmp = rbtree_predecessor(tmp, &nil)))
			printf("%2i\n", tmp->value);
		if ((tmp = rbtree_search(root, &nil, 42)))
			printf("%2i's pre ", tmp->value);
		if ((tmp = rbtree_predecessor(tmp, &nil)))
			printf("%2i\n", tmp->value);

		printf("root: %i\n", root->value);
		if ((tmp = rbtree_search(root, &nil, 3)))
			rbtree_delete(&root, &nil, tmp);
		printf("in   ");
		rbtree_inorder(root, &nil);
		printf("\n");
		printf("root: %i\n", root->value);
		if ((tmp = rbtree_search(root, &nil, 9)))
			rbtree_delete(&root, &nil, tmp);
		printf("in   ");
		rbtree_inorder(root, &nil);
		printf("\n");
		printf("root: %i\n", root->value);
		if ((tmp = rbtree_search(root, &nil, 43)))
			rbtree_delete(&root, &nil, tmp);
		printf("in   ");
		rbtree_inorder(root, &nil);
		printf("\n");
		printf("root: %i\n", root->value);
		if ((tmp = rbtree_search(root,& nil, 22)))
			rbtree_delete(&root, &nil, tmp);
		printf("in   ");
		rbtree_inorder(root, &nil);
		printf("\npre  ");
		rbtree_preorder(root, &nil);
		printf("\n");

		printf("root: %i\n", root->value);
		rbtree_delete(&root, &nil, root);
		printf("in   ");
		rbtree_inorder(root, &nil);
		printf("\n");
		printf("root: %i\n", root->value);

		rbtree_burn(&root);
		printf("%p\n", root);
		rbtree_inorder(root, &nil);
	}
}
