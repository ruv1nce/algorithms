#include "libft.h"
#include <stdio.h>
#include <unistd.h>

static char **cut_area(char **area, int mode, int size)
{
	char	**part;
	int	i;

	part = malloc(size/2 * sizeof(part));
	/* upper left */
	if (mode == 1)
	{
		i = -1;
		while (++i < size/2)
			*(part + i) = *(area + i);
	}
	/* upper right */
	else if (mode == 2)
	{
		i = -1;
		while (++i < size/2)
			*(part + i) = *(area + i) + size/2;
	}
	/* lower right */
	else
	{
		i = size/2;
		while (i < size)
		{
			*(part + i - size/2) = *(area + i) + size/2;
			i++;
		}
	}
	return (part);
}

static void	sierpinski(char **area, int size, int freecnt)
{
	if (size == 1)
		**area = 'x';
	else
	{
		sierpinski(cut_area(area, 1, size), size/2, freecnt+1);
		sierpinski(cut_area(area, 2, size), size/2, freecnt+1);
		sierpinski(cut_area(area, 3, size), size/2, freecnt+1);
	}
	if (freecnt)
		free(area);
}

int			main(int argc, char **argv)
{
	size_t	size;
	size_t		i;
	size_t		j;
	char **area;

	if (argc != 2)
	{
		printf("Specify gasket size\n");
		return (0);
	}
	size = atoi(argv[1]);
	if (size < 0 || !(ft_is_powof2(size)))
	{
		printf("The size has to be power of 2\n");
		return (0);
	}

	/* allocate for area */
	area = malloc(size * sizeof(area));
	i = 0;
	while (i < size)
	{
		area[i] = ft_strnew(size);
		ft_bchar(area[i], '.', size);
		i++;
	}

	/* print original area */
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			write(1, &area[i][j], 1);
			write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}

	/* print addresses */
/*	printf("addr of head %p\n", &area);
	i = 0;
	while (i < size)
	{
		printf("ptr%zu %p\n", i, area + i);
		j = 0;
		while (j < size)
		{
			printf("  str%zu, char%zu=%c %p\n", i, j, *(*(area + i) + j), *(area + i) + j);
			j++;
		}
		i++;
	}
*/
	printf("\n");

	sierpinski(area, size, 0);

	/* print modified area */
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			write(1, &area[i][j], 1);
			write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}

	/* free memory */
	i = 0;
	while (i < size)
	{
		free(area[i]);
		i++;
	}
	free(area);
}
