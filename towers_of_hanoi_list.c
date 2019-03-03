#include "libft.h"
#include "towers_of_hanoi.h"
#include <stdio.h>

static void	print_towers(t_list *a, t_list *b, t_list *c, int size)
{
	if (size < 10)
	{
		printf("  ___    ___    ___\n");
		while (--size >= 0)
		{
			if (a && a->num)
			{
				printf(" | %i | ", a->num);
				a = a->next;
			}
			else
				printf(" | 0 | ");
			if (b && b->num)
			{
				printf(" | %i | ", b->num);
				b = b->next;
			}
			else
				printf(" | 0 | ");
			if (c && c->num)
			{
				printf(" | %i |\n", c->num);
				c = c->next;
			}
			else
				printf(" | 0 | \n");
		}
		printf(" aaaaa  bbbbb  ccccc\n");
	}
/*	else
	{
		printf("  ____    ____    ____\n");
		while (--discs >= 0)
		{
			if (a[discs] < 10)
				printf(" |  %i | ", a[discs]);
			else
				printf(" | %i | ", a[discs]);
			if (b[discs] < 10)
				printf(" |  %i | ", b[discs]);
			else
				printf(" | %i | ", b[discs]);
			if (c[discs] < 10)
				printf(" |  %i |\n", c[discs]);
			else
				printf(" | %i |\n", c[discs]);
		}
		printf(" aaaaaa  bbbbbb  cccccc\n");
	}*/
}

static int	top(t_list **stack)
{
	if (!stack || !*stack)
		return (-1);
	return ((*stack)->num);
}

static void	pop(t_list **stack)
{
	t_list	*tmp;

	if (!stack || !*stack)
		return ;
	tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
}

static void push(int num, t_list **stack)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list *))))
		return ;
	new->num = num;
	if (*stack)
		new->next = *stack;
	*stack = new;
}


static void	move_tower(t_list **a, t_list **b, t_list **c, int discs)
{
	if (discs == 1)
	{
		push(top(a), b);
		pop(a);
	}
	else
	{
		move_tower(a, c , b, discs - 1);
		push(top(a), b);
		pop(a);
		move_tower(c, b, a, discs - 1);
	}
}

static void	create_source(int discs, t_list **a)
{
	while (discs)
	{
		push(discs, a);
		discs--;
	}
}

int			main(int argc, char **argv)
{
	int	discs;
	t_list	*a;
	t_list	*b;
	t_list	*c;

	if (argc != 2)
	{
		printf("Specify the number of discs\n");
		return (0);
	}
	discs = atoi(argv[1]);
	if (discs < 1)
	{
		printf("We need at least one disc\n");
		return (0);
	}
	a = NULL;
	b = NULL;
	c = NULL;
	create_source(discs, &a);
	print_towers(a, b, c, discs);
	move_tower(&a, &b, &c, discs);
	print_towers(a, b, c, discs);
}
