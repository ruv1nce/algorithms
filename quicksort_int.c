#include <stdio.h>
#include <stdlib.h>

static int	partition(int *tab, int p)
{
	int	q;
	int	j;
	int tmp;

	q = 0;
	j = -1;
	while (++j <= p)
	{
		/* finish or move lower int to left side */
		if ((j == p && q != p) || tab[j] < tab[p])
		{
			tmp = tab[q];
			tab[q] = tab[j];
			tab[j] = tmp;
			/* if not finish, move q */
			if (j != p)
				q++;
		}
	}
	return (q);
}

static void	quicksort(int **tab, int p)
{
	int	q;
	int	*tmp;

	if (p == 0)
		return ;
	q = partition(*tab, p);
	/* sort left part */
	if (q > 0)
		quicksort(tab, q - 1);
	/* sort right part */
	tmp = *tab + q + 1;
	if (q < p)
		quicksort(&tmp, p - q);
}

int	main(int argc, char **argv)
{
	int	*tab;
	int	size;

	if (argc < 2)
	{
		printf("Gimme at least one number!\n");
		return (0);
	}
	argc--;
	size = argc;
	if (!(tab = malloc(argc * sizeof(*tab))))
		return (0);
	while (argc)
	{
		tab[argc - 1] = atoi(argv[argc]);
		argc--;
	}
	/* print unsorted */
/*	argc = -1;
	while (++argc < size)
		printf("%i ", tab[argc]);
	printf("\n");*/
	quicksort(&tab, size - 1);
	/* print sorted */
	argc = -1;
	while (++argc < size)
		printf("%i ", tab[argc]);
	printf("\n");
	free(tab);
}
