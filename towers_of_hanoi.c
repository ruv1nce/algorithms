#include "libft.h"
#include <stdio.h>

static void	print_towers(int *a, int *b, int *c, int discs, int size)
{
	if (size < 10)
	{
		printf("  ___    ___    ___\n");
		while (--discs >= 0)
		{
			printf(" | %i | ", a[discs]);
			printf(" | %i | ", b[discs]);
			printf(" | %i |\n", c[discs]);
		}
		printf(" aaaaa  bbbbb  ccccc\n");
	}
	else
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
	}
}

static int	top(int *stack, int size)
{
	while (--size >= 0)
		if (stack[size])
			return (stack[size]);
	return (0);
}

static void	pop(int *stack, int size)
{
	while (--size >= 0)
	{
		if (stack[size])
		{
			stack[size] = 0;
			return ;
		}
	}
}

static void push(int num, int *stack, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (!stack[i])
		{
			stack[i] = num;
			return ;
		}
	}
}


static void	move_tower(int *a, int *b, int *c, int discs, int size)
{
	if (discs == 1)
	{
		push(top(a, size), b, size);
		pop(a, size);
	}
	else
	{
		move_tower(a, c , b, discs - 1, size);
		push(top(a, size), b, size);
		pop(a, size);
		move_tower(c, b, a, discs - 1, size);
	}
}

static int	create_stacks(int discs, int **a, int **b, int **c)
{
	int	i;

	if (!(*a = malloc(discs * sizeof(a))))
		return (0);
	if (!(*b = malloc(discs * sizeof(b))))
		return (0);
	ft_bzero(*b, (discs * sizeof(int)));
	if (!(*c = malloc(discs * sizeof(c))))
		return (0);
	ft_bzero(*c, (discs * sizeof(int)));
	i = 0;
	while (discs)
	{
		*(*a + i) = discs;
		discs--;
		i++;
	}
	return (1);
}

int			main(int argc, char **argv)
{
	int	discs;
	int	*a;
	int	*b;
	int	*c;

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
	if (!(create_stacks(discs, &a, &b, &c)))
		return (0);
	print_towers(a, b, c, discs, discs);
	move_tower(a, b, c, discs, discs);
	print_towers(a, b, c, discs, discs);
	free(a);
	free(b);
	free(c);
}
