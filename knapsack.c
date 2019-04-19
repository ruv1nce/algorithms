#include "knapsack.h"

void	print_grid(cell **grid, item *store, int c, int r)
{
	int	i;
	int	j;

	printf("\n         ");
	i = -1;
	while (++i <= c)
		printf("    %2i    ", i);
	printf("\n---------");
	i = -1;
	while (++i <= c)
		printf("----------");
	printf("\n");
	j = -1;
	while (++j <= r)
	{
		printf("%.5s ", store[j].name);
		printf("%i | ", j);
		i = -1;
		while (++i <= c)
		{
			printf("%2i %2i ", grid[j][i].load, grid[j][i].sum);
			if (!grid[j][i].sack)
				printf("0 | ");
			else
				printf("+ | ");
		}
		printf("\n");
	}
	printf("---------");
	i = -1;
	while (++i <= c)
		printf("----------");
	printf("\n");
}

loot	*new_loot(item *stuff)
{
	loot	*new;

	if (stuff)
	{
		if (!(new = malloc(sizeof(*new))))
			return (NULL);
		new->stolen = stuff;
		new->next = NULL;
		return (new);
	}
	return (NULL);
}

void	put_in_sack(cell *dest, item *stuff, cell *src)
{
	loot	*add_here;

	add_here = NULL;
	if (stuff)
	{
		dest->load += stuff->wt;
		dest->sum += stuff->val;
		dest->sack = new_loot(stuff);
		add_here = dest->sack;
	}
	dest->load += src->load;
	dest->sum += src->sum;
	if (!add_here)
		dest->sack = src->sack;
	else
		add_here->next = src->sack;
}

int		steal(item *store, cell **grid, int capacity, int item_count)
{
	/* row and column */
	int r;
	int	c;

	r = 0;
	/* iterate on items */
	while (++r <= item_count)
	{
		c = 0;
		/* iterate on subknapsacks */
		while (++c <= capacity)
		{
			/* will current item fit? */
			if (store[r].wt <= c)
			{
				/* Is it worth taking?
				 * Combine current item's value with the total value of loot for the remaining space.
				 * If (1) value is greater than previous solution for this capacity or
				 * (2) values are equal, but taking new item leaves more free space */
				if ((store[r].val + grid[r - 1][c - store[r].wt].sum > grid[r - 1][c].sum) 
						|| ((store[r].val + grid[r - 1][c - store[r].wt].sum == grid[r - 1][c].sum) 
							&& (grid[r - 1][c - store[r].wt].load + store[r].wt < grid[r - 1][c].load)))
				{
					put_in_sack(&grid[r][c], &store[r], &grid[r - 1][c - store[r].wt]);
				}
				else
					/* else copy from previous row */
					put_in_sack(&grid[r][c], NULL, &grid[r - 1][c]);
			}
			/* if it doesn't fit, also copy from previous row */
			else
				put_in_sack(&grid[r][c], NULL, &grid[r - 1][c]);
		}
	}
	return (1);
}

int		fill_store(item **store, char **s, int cnt)
{
	int	i;
	int	j;

	if (!(*store = malloc(sizeof(item) * cnt)))
		return (0);
	(*store)[0].name = "     ";
	(*store)[0].wt = 0;
	(*store)[0].val = 0;
	i = 0;
	j = 0;
	while (++j < cnt)
	{
		(*store)[j].name = s[i];
		(*store)[j].wt = atoi(s[i + 1]);
		(*store)[j].val = atoi(s[i + 2]);
		i += 3;
	}
	return (1);
}

cell	**create_grid(cell **grid, int c, int r)
{
	int	i;
	int	j;

	if (!(grid = malloc(sizeof(*grid) * r)))
		return (NULL);
	j = -1;
	while (++j < r)
	{
		if (!(grid[j] = malloc(sizeof(cell) * c)))
			return (NULL);
		i = -1;
		while (++i < c)
		{
			grid[j][i].load = 0;
			grid[j][i].sum = 0;
			grid[j][i].sack = NULL;
		}
	}
	return (grid);
}

void	free_grid(cell **grid, int c, int r)
{
	int		x;
	int		y;
	loot	*tmp;
	loot	*prev;

	/* first go: mark and detach */
	/*iterate on rows and columns */
	y = -1;
	while (++y <= r)
	{
		x = -1;
		while (++x <= c)
		{
			tmp = grid[y][x].sack;
			/* if sack is pointing to a marked data, detach it */
			if (tmp && !tmp->stolen)
				grid[y][x].sack = NULL;
			else
			{
				/* traverse the list and mark all data; if encountered marked data in next - detach */
				while (tmp)
				{
					tmp->stolen = NULL;
					if (tmp->next && !tmp->next->stolen)
						tmp->next = NULL;
					tmp = tmp->next;
				}
			}
		}
	}
	/* second go: free */
	y = -1;
	while (++y <= r)
	{
		x = -1;
		while (++x <= c)
		{
			tmp = grid[y][x].sack;
			while (tmp)
			{
				prev = tmp;
				tmp = tmp->next;
				free(prev);
			}
		}
		free(grid[y]);
	}
	free(grid);
}

int		main(int argc, char **argv)
{
	int		capacity;
	int		item_count;
	item	*store;
	cell	**grid;
	loot	*tmp;
	int		i;

	if ((argc - 2) % 3)
		printf("usage: ./bin <knapsack_capacity> <item_1_name> <item_1_weight> <item_1_value> ... <item_n_name> <item_n_weight> <item_n_value>\n");
	else
	{
		capacity = atoi(argv[1]);
		item_count = (argc - 2) / 3;
		/* first item is a dummy to simplify syntax */
		if (!(fill_store(&store, argv + 2, item_count + 1)))
			return (10);

		/* print vars and store */
		printf("capacity %i, item count %i\n", capacity, item_count);
		i = 0;
		while (++i <= item_count)
			printf("%s w%i v%i, ", (store + i)->name, (store + i)->wt, (store + i)->val);
		printf("\n");

		/* capacity = 0 and item = 0 will be zeroed grid margins */
		grid = NULL;
		if (!(grid = create_grid(grid, capacity + 1, item_count + 1)))
			return (10);

		print_grid(grid, store, capacity, item_count);
		
		steal(store, grid, capacity, item_count);

		print_grid(grid, store, capacity, item_count);

		printf("total loot value: %i, total loot weight: %i (of %i capacity)\nstolen items: ", grid[item_count][capacity].sum, grid[item_count][capacity].load, capacity);
		tmp = grid[item_count][capacity].sack;
		while (tmp)
		{
			printf("%s ", tmp->stolen->name);
			tmp = tmp->next;
		}
		printf("\n");
		free_grid(grid, capacity, item_count);
		free(store);
	}
}
