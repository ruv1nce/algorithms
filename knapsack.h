#ifndef KNAPSACK_H
# define KNAPSACK_H

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

#endif
