#include <stdio.h>
#include <stdlib.h>

int	*quicksort(int *tab, int size)
{
	if (size < 1)
		return (tab);

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
	tab = quicksort_int(tab, size);
	argc = -1;
	while (++argc < size)
		printf("%i ", tab[argc]);
	printf("\n");
	free(tab);
}
