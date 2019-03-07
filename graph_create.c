#include "libft.h"
#include "graph.h"
#include <stdio.h>

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
	t_edge	*egraph;
	t_madj	**agraph;
	t_ladj	**lgraph;
	t_ladj	*tmp;

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

	/* print edges */
	i = -1;
	while (++i < edgecount)
		printf("%i,%i,%i\n", egraph[i].x, egraph[i].y, egraph[i].weight);

	printf("\n");

	/* adjacency matrix representation */
	if (!(agraph = malloc(vertexcount * sizeof(*agraph))))
		return (1);
	i = 0;
	while (i < vertexcount)
	{
		if(!(*(agraph + i) = malloc(vertexcount * sizeof(**agraph))))
			return (1);
		i++;
	}
	i = -1;
	while (++i < vertexcount)
	{
		j = -1;
		while (++j < vertexcount)
		{
			agraph[i][j].vertex = 0;
			agraph[i][j].weight = 0;
		}
	}
	i = 0;
	while (i < edgecount)
	{
		agraph[egraph[i].x][egraph[i].y].vertex = 1;
		agraph[egraph[i].x][egraph[i].y].weight = egraph[i].weight;
		agraph[egraph[i].y][egraph[i].x].vertex = 1;
		agraph[egraph[i].y][egraph[i].x].weight = egraph[i].weight;
		i++;
	}

	/* print matrix */
	printf("     0   1   2   3   4   5   6\n");
	printf("-------------------------------\n");
	i = -1;
	while (++i < vertexcount)
	{
		printf("%i | ", i);
		j = -1;
		while (++j < vertexcount)
			printf("%i.%i ", agraph[i][j].vertex, agraph[i][j].weight);
		printf("\n");
	}
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
				if (!(lstadd_sort(&lgraph[i], egraph[j].y, egraph[j].weight)))
					return (1);
			else if (egraph[j].y == i)
				if (!(lstadd_sort(&lgraph[i], egraph[j].x, egraph[j].weight)))
					return (1);
		}
	}

	/* print adjacency lists */
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

	/* free memory */
	free(egraph);
	free(agraph);
	i = -1;
	while (++i < vertexcount)
		lstdel(&lgraph[i]);
	free(lgraph);
}
