#include <stdio.h>
#include <stdlib.h>

static int	*div_tab(int *tab, int part, int size)
{
	int	*x;
	int	xsize;
	int	i;
	int	odd;

	xsize = (part == 1) ? size / 2 : size - (size / 2);
	x = malloc(xsize * sizeof(int));
	i = -1;
	if (part == 1)
		while (++i < xsize)
			x[i] = tab[i];
	else
	{
		odd = (size % 2 == 0) ? 0 : 1;
		i = -1;
		while (++i < xsize)
			x[i] = tab[xsize - odd + i];
	}
	return (x);
}

static int	*combine(int *a, int *b, int asize, int bsize)
{
	int	*res;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	res = malloc((asize + bsize) * sizeof(int));
	while (k < asize + bsize)
	{
		if (j >= bsize || (i < asize && a[i] < b[j]))
		{
			res[k] = a[i];
			i++;
		}
		else
		{
			res[k] = b[j];
			j++;
		}
		k++;
	}
	return (res);
}

static int	*merge_sort_int(int *tab, int size)
{
	int	*a;
	int	*b;
	int	asize;
	int	bsize;

	if (size < 2)
		return (tab);
	asize = size / 2;
	bsize = size - asize;
	a = merge_sort_int(div_tab(tab, 1, size), asize);
	b = merge_sort_int(div_tab(tab, 2, size), bsize);
	return (combine(a, b, asize, bsize));
}

int	main(int argc, char **argv)
{
	int	*tab;
	int	size;

	if (argc < 2)
		printf("Gimme at least one number!");
	argc--;
	size = argc;
	tab = malloc(argc * sizeof(int));
	while (argc)
	{
		tab[argc - 1] = atoi(argv[argc]);
		argc--;
	}
	argc = -1;
	while (++argc < size)
		printf("%i ", tab[argc]);
	printf("\n");
	tab = merge_sort_int(tab, size);
	argc = -1;
	while (++argc < size)
		printf("%i ", tab[argc]);
	printf("\n");
}
