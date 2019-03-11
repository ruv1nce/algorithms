#include "libft.h"
#include "graph.h"
#include <stdio.h>

/* requires list functions from graph_list.c for adjacency list representaion */

void		bfs(t_vert *graph, int s);
void		show_path(t_vert	*graph, int dest);
static void	print_edges(t_edge *egraph, int edgecount);
static void	print_matrix(t_madj **mgraph, int vertexcount);
static void	print_adjlist(t_ladj **lgraph, int vertexcount);
static void	print_vstructadjlist(t_vert *bfsgraph, int vertexcount);

static void	fill_edge(t_edge *egraph, int linecount, char *line)
{
	egraph[linecount].x = atoi(line);
	while (*line != ',')
			line++;
	line++;
	egraph[linecount].y = atoi(line);
	while (*line != ',')
			line++;
	line++;
	egraph[linecount].weight = atoi(line);
}

int	 		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		resume;
	int		linecount;
	int		edgecount;
	int		vertexcount;
	int		i;
	int		j;
	int		source;
	int		dest;
	t_edge	*egraph;
	t_madj	**mgraph;
	t_ladj	**lgraph;
	t_vert	*bfsgraph;

	if (argc < 2)
	{
		printf("File name missing\n");
		return (0);
	}

	/* edge representation */
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Invalid filename\n");
		return (0);
	}
	resume = 1;
	linecount = -2;
	while ((resume = ft_gnl(fd, &line)) > 0)
	{
		if (*line != '#')
		{
			if (linecount == -2)
			{
				edgecount = atoi(line);
				if (!(egraph = malloc(edgecount * sizeof(*egraph))))
					return (1);
			}
			else if (linecount == -1)
				vertexcount = atoi(line);
			else
				fill_edge(egraph, linecount, line);
			linecount++;
		}
		free(line);
	}
	free(line);
	close(fd);
	print_edges(egraph, edgecount);
	printf("\n");

	/* adjacency matrix representation */
	if (!(mgraph = malloc(vertexcount * sizeof(*mgraph))))
		return (1);
	i = 0;
	while (i < vertexcount)
	{
		if(!(*(mgraph + i) = malloc(vertexcount * sizeof(**mgraph))))
			return (1);
		i++;
	}
	i = -1;
	while (++i < vertexcount)
	{
		j = -1;
		while (++j < vertexcount)
		{
			mgraph[i][j].vertex = 0;
			mgraph[i][j].weight = 0;
		}
	}
	i = 0;
	while (i < edgecount)
	{
		mgraph[egraph[i].x][egraph[i].y].vertex = 1;
		mgraph[egraph[i].x][egraph[i].y].weight = egraph[i].weight;
		mgraph[egraph[i].y][egraph[i].x].vertex = 1;
		mgraph[egraph[i].y][egraph[i].x].weight = egraph[i].weight;
		i++;
	}
	print_matrix(mgraph, vertexcount);
	printf("\n");

	/* adjacency list representation */
	if (!(lgraph = malloc(vertexcount * sizeof(*lgraph))))
		return (1);
	i = -1;
	while (++i < vertexcount)
		*(lgraph + i) = NULL;
	i = -1;
	while (++i < vertexcount)
	{
		j = -1;
		while (++j < edgecount)
		{
			if (egraph[j].x == i)
			{
				if (!(lstadd_sort(&lgraph[i], egraph[j].y, egraph[j].weight)))
					return (1);
			}
			else if (egraph[j].y == i)
			{
				if (!(lstadd_sort(&lgraph[i], egraph[j].x, egraph[j].weight)))
					return (1);
			}
		}
	}
	print_adjlist(lgraph, vertexcount);
	printf("\n");

	/* adjacency lists with vertices struct array */
	if (!(bfsgraph = malloc(vertexcount * sizeof(*bfsgraph))))
		return (1);
	i = -1;
	while (++i < vertexcount)
	{
		bfsgraph[i].color = white;
		bfsgraph[i].distance = -1;
		bfsgraph[i].parent = -1;
		bfsgraph[i].kids = NULL;
	}
	i = -1;
	while (++i < vertexcount)
	{
		j = -1;
		while (++j < edgecount)
		{
			if (egraph[j].x == i)
			{
				if (!(lstadd_sort(&bfsgraph[i].kids, egraph[j].y, egraph[j].weight)))
					return (1);
			}
			else if (egraph[j].y == i)
			{
				if (!(lstadd_sort(&bfsgraph[i].kids, egraph[j].x, egraph[j].weight)))
					return (1);
			}
		}
	}
	print_vstructadjlist(bfsgraph, vertexcount);
	printf("\n");

	source = 4;
	bfs(bfsgraph, source);
	dest = 5;
	printf("path from %i to %i: ", source, dest);
	show_path(bfsgraph, dest);
	printf("\n\n");

	print_vstructadjlist(bfsgraph, vertexcount);

	/* free memory */
	free(egraph);
	free(mgraph);
	i = -1;
	while (++i < vertexcount)
		lstdel(&lgraph[i]);
	free(lgraph);
	i = -1;
	while (++i < vertexcount)
		lstdel(&bfsgraph[i].kids);
	free(bfsgraph);
}

static void	print_edges(t_edge *egraph, int edgecount)
{
	int		i;

	printf("edges: v1, v2, weight\n");
	i = -1;
	while (++i < edgecount)
		printf("%i,%i,%i\n", egraph[i].x, egraph[i].y, egraph[i].weight);

	printf("\n");
}

static void	print_matrix(t_madj **mgraph, int vertexcount)
{
	int		i;
	int		j;

	printf("adj matrix: vertix.edge_weight\n");
	printf("     0   1   2   3   4   5   6\n");
	printf("-------------------------------\n");
	i = -1;
	while (++i < vertexcount)
	{
		printf("%i | ", i);
		j = -1;
		while (++j < vertexcount)
			printf("%i.%i ", mgraph[i][j].vertex, mgraph[i][j].weight);
		printf("\n");
	}
}

static void	print_adjlist(t_ladj **lgraph, int vertexcount)
{
	int		i;
	t_ladj	*tmp;

	printf("adj list: *(vertix + i): vertix.edge_weight\n");
	i = -1;
	while (++i < vertexcount)
	{
		tmp = *(lgraph + i);
		printf("V%i: ", i);
		while (tmp)
		{
			printf("%i.%i ", tmp->vertex, tmp->weight);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

static void	print_vstructadjlist(t_vert *bfsgraph, int vertexcount)
{
	int		i;
	t_ladj	*tmp;

	printf("adj list: vertix[i]: vertix.edge_weight\n");
	i = -1;
	while (++i < vertexcount)
	{
		tmp = bfsgraph[i].kids;
		printf("V%i, color %i, distance %i, parent %i, kids: ", i, bfsgraph[i].color, bfsgraph[i].distance, bfsgraph[i].parent);
		while (tmp)
		{
			printf("%i.%i ", tmp->vertex, tmp->weight);
			tmp = tmp->next;
		}
		printf("\n");
	}
}
