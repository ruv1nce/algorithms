#include "libft.h"
#include "towers_of_hanoi.h"
#include <stdio.h>

static t_list	*print_disc(t_list *l, int mode)
{
	if (mode)
	{
		if (l && l->num)
		{
			printf(" | %i | ", l->num);
			return (l->next);
		}
		else
			printf(" | 0 | ");
		return (l);
	}
	else
	{
		if (l && l->num)
		{
			if (l->num < 10)
				printf(" |  %i | ", l->num);
			else
				printf(" | %i | ", l->num);
			return (l->next);
		}
		else
			printf(" |  0 | ");
		return (l);
	}
}

static void	print_towers(t_list *a, t_list *b, t_list *c, int size)
{
	int	mode;

	mode = (size < 10) ? 1 : 0;
	if (mode)
		printf("  ___    ___    ___\n");
	else
		printf("  ____    ____    ____\n");
	while (--size >= 0)
	{
		a = print_disc(a, mode);
		b = print_disc(b, mode);
		c = print_disc(c, mode);
		printf("\n");
	}
	if (mode)
		printf(" aaaaa  bbbbb  ccccc\n");
	else
		printf(" aaaaaa  bbbbbb  cccccc\n");
}

static int	pop(t_list **stack)
{
	t_list	*tmp;
	int		num;

	if (!stack || !*stack)
		return (-1);
	tmp = *stack;
	num = (*stack)->num;
	*stack = (*stack)->next;
	free(tmp);
	return (num);
}

static void push(int num, t_list **stack)
{
	t_list	*new;

	if (!(new = malloc(sizeof(*new))))
		return ;
	new->num = num;
	if (*stack)
		new->next = *stack;
	else
		new->next = NULL;
	*stack = new;
}


static void	move_tower(t_list **a, t_list **b, t_list **c, int discs)
{
	if (discs == 1)
		push(pop(a), b);
	else
	{
		move_tower(a, c , b, discs - 1);
		push(pop(a), b);
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

static void	delete_lst(t_list **x)
{
	t_list	*tmp;

	while (*x)
	{
		tmp = *x;
		*x = (*x)->next;
		free(tmp);
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
	delete_lst(&a);
	delete_lst(&b);
	delete_lst(&c);
}
