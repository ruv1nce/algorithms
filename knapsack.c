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
	int		load;
	int		sum;
	loot	*sack;
}			cell;

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

//void	put_in_sack(cell *dest, item *stuff, cell *src)
//{
//	loot	*tmp;
//	loot	*addloot;
//
//	dest->load += src->load;
//	dest->sum += src->sum;
//	/* put item in sack */
//	if (stuff)
//	{
//		dest->load += stuff->wt;
//		dest->sum += stuff->val;
//		dest->sack = new_loot(stuff);
//		addloot = dest->sack->next;
//	}
//	else
//		addloot = dest->sack;
//	tmp = src->sack;
//	/* copy loot from previous solution cell */
//	while (tmp)
//	{
//		addloot = new_loot(tmp->stolen);
//		tmp = tmp->next;
//		addloot = addloot->next;
//	}
//}	

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
			}
			/* if it doesn't fit, copy from previous row */
			else
				put_in_sack(&grid[r][c], NULL, &grid[r - 1][c]);
		}
	}
	return (1);
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
		(*store + 0)->name = "     ";
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
			grid[j][i].load = 0;
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
	loot	*tmp;
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
	}
}
