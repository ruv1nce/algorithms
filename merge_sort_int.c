#include <stdio.h>
#include <stdlib.h>

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
	/* Only free a and b if they are product of previous combining \
	 * and aren't just parts of the original array */
	if (asize > 1)
		free(a);
	if (bsize > 1)
		free(b);
	return (res);
}

static int	*merge_sort_int(int **tab, int size)
{
	int	*a;
	int	*b;
	int	asize;
	int	bsize;
	int *tmp;

	if (size < 2)
		return (*tab);
	asize = size / 2;
	/* this way bsize works both for odd and even amount of ints */
	bsize = size - asize;
	/* set tmp to the beginning of 'b' part and then pass its address */
	tmp = *tab + asize;
	a = merge_sort_int(tab, asize);
	b = merge_sort_int(&tmp, bsize);
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
	/* print unsorted */
/*	argc = -1;
	while (++argc < size)
		printf("%i ", tab[argc]);
	printf("\n"); */
	tab = merge_sort_int(&tab, size);
	/* print sorted */
	argc = -1;
	while (++argc < size)
		printf("%i ", tab[argc]);
	printf("\n");
	free(tab);
}

/*
int main()
{
	const int	crap[6] = {10, 23, -9, 0, 0, 5};
	const int	*tab;
	int			size = 6;
	int			i = -1;

	while (++i < size)
		printf("%i ", crap[i]);
	printf("\n");
	tab = &crap[0];
	tab = merge_sort_int((int **)&tab, size);
	i = -1;
	while (++i < size)
		printf("%i ", tab[i]);
	printf("\n");
}*/
