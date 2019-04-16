#include <stdio.h>
#include <stdlib.h>

typedef struct s_node	item;

struct s_node
{
	char	*name;
	int		weight;
	int		value;
	item	*next;
};

int		steal(item *store, int capacity, int item_count)
{	
}

int		create_item(item **store, char *name, int weight, int value)
{
	item	*new;

	if (!(new = malloc(sizeof(*new))))
		return (0);
	new->name = name;
	new->weight = weight;
	new->value = value;
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

int		main(int argc, char **argv)
{
	int		capacity;
	int		item_count;
	item	*store;
	int		i;

	if ((argc - 2) % 3)
		printf("usage: ./bin <knapsack.capacity> <item_1_name> <item_1_weight> <item_1_value> ... <item_n_name> <item_n_weight> <item_n_value>\n");
	else
	{
		capacity = atoi(argv[1]);
		item_count = (argc - 2) / 3;
		i = 2;
		while (i < argc)
		{
			if (!(create_item(&store, argv[i], atoi(argv[i + 1]), atoi(argv[i + 2]))))
				return (1);
			i += 3;
		}
		printf("loot = %i\n", steal(store, capacity, item_count));
/*		printf("capacity %i, item count %i\n", capacity, item_count);
		while (store)
		{
			printf("%s %i %i ", store->name, store->weight, store->value);
			store = store->next;
		}
		printf("\n");*/

	}
}
