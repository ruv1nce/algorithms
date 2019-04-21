#include <stdio.h>
#include <stdlib.h>

void	insertion_sort_int(int *tab, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (++i < size)
	{
		if (tab[i] < tab[i - 1])
		{
			tmp = tab[i];
			j = i;
			while (--j >= 0 && tmp < tab[j])
				tab[j + 1] = tab[j];
			tab[++j] = tmp;
		}
	}
}

int	main(int argc, char **argv)
{
	int	*tab;
	int	size;
	int	i;

	if (argc < 2)
	{
		printf("Gimme at least one number!\n");
		return (1);
	}
	size = argc - 1;
	tab = malloc(size * sizeof(int));
	i = 0;
	while (++i <= size)
		tab[i - 1] = atoi(argv[i]);
	/* print unsorted */
	i = -1;
	while (++i < size)
		printf("%i ", tab[i]);
	printf("\n"); 
	insertion_sort_int(tab, size);
	/* print sorted */
	argc = -1;
	while (++argc < size)
		printf("%i ", tab[argc]);
	printf("\n");
	free(tab);
}
