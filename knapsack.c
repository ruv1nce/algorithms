#include <stdio.h>
#include <stdlib.h>

typedef struct item
{
	char		*name;
	int			wt;
	int			val;
	struct item	*next;
}				item;

typedef struct loot
{
	item		*stolen;
	struct loot	*next;
}				loot;

typedef struct cell
{
	int		free;
	int		sum;
	loot	*sack;
}			cell;

void	print_grid(cell **grid, item *store, int c, int r)
{
	int	i;
	int	j;

	j = -1;
	while (++j <= r)
	{
		printf("%s ", store[j].name);
		i = -1;
		while (++i <= c)
			printf("%i %i %p | ", grid[j][i].free, grid[j][i].sum, grid[j][i].sack);
		printf("\n");
	}
}

void	put_in_sack(cell *dest, 

int		steal(item *store, cell **grid, int capacity, int item_count)
{
	/* row and column */
	int r;
	int	c;

	r = -1;
	/* iterate on items */
	while (++r < item_count)
	{
		c = 0;
		/* iterate on subknapsacks */
		while (++c <= capacity)
		{
			/* will current item fit? */
			if (store[r].wt <= grid[r][c].free)
			{
				/* Is it worth taking?
				 * Combine current item's value with the total value of loot for the remaining space.
				 * If (1) value is greater than previous solution for this capacity or
				 * (2) values are equal, but taking new item leaves more free space */
				if ((store[r].val + grid[r - 1][c - store[r].wt].sum > grid[r - 1][c].sum) 
						|| ((store[r].val + grid[r - 1][c - store[r].wt].sum == grid[r - 1][c].sum) 
							&& (grid[r - 1][c - store[r].wt].free - store[r].wt > grid[r - 1][c].free)))
				{
					put_in_sack(&grid[r][c], &store[r], &grid[r - 1][c - store[r].wt]);
				}
			}
			/* if it doesn't fit, copy from previous row */
		}
	}
}

/*
int		add_item(item **store, char *name, int wt, int val)
{
	item	*new;

	if (!(new = malloc(sizeof(*new))))
		return (0);
	new->name = name;
	new->wt = wt;
	new->val = val;
	new->next = NULL;
	if (!(*store))
		*store = new;
	else
	{
		new->next = *store;
		*store = new;
	}
	return (1);
}
*/

int		fill_store(item **store, char **s, int cnt)
{
	int	i;
	int	j;

	if (!(*store = malloc(sizeof(item) * cnt)))
		return (0);
		(*store + 0)->name = "bull";
		(*store + 0)->wt = 0;
		(*store + 0)->val = 0;
	i = 0;
	j = 0;
	while (j < cnt)
	{
		(*store + j + 1)->name = s[i];
		(*store + j + 1)->wt = atoi(s[i + 1]);
		(*store + j + 1)->val = atoi(s[i + 2]);
		i += 3;
		j++;
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
			grid[j][i].free = i;
			grid[j][i].sum = 0;
			grid[j][i].sack = NULL;
		}
	}
	return (grid);
}

int		main(int argc, char **argv)
{
	int		capacity;
	int		item_count;
	item	*store;
	cell	**grid;
	int		i;

	if ((argc - 2) % 3)
		printf("usage: ./bin <knapsack.capacity> <item_1_name> <item_1_weight> <item_1_value> ... <item_n_name> <item_n_weight> <item_n_value>\n");
	else
	{
		capacity = atoi(argv[1]);
		item_count = (argc - 2) / 3;
		/* first item is a dummy to simplify syntax */
		if (!(fill_store(&store, argv + 2, item_count + 1)))
			return (10);

		/* print vars and store */
		printf("capacity %i, item count %i\n", capacity, item_count);
		i = -1;
		while (++i <= item_count)
			printf("%s w%i v%i, ", (store + i)->name, (store + i)->wt, (store + i)->val);
		printf("\n");

		/* capacity = 0 and item = 0 will be zeroed grid margins */
		grid = NULL;
		if (!(grid = create_grid(grid, capacity + 1, item_count + 1)))
			return (10);

		print_grid(grid, store, capacity, item_count);
		
		steal(store, grid, capacity, item_count);

	}
}
