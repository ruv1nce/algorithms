#include "libft.h"
#include "graph.h"
#include <stdio.h>
#include <fcntl.h>

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
	int		k;
	t_edge	*egraph;
	t_adj	**agraph;
	t_adj	**lgraph;

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

	/* adjacency list representation DO WITH A LINKED LIST*/
	if (!(lgraph = malloc((vertexcount + 1) * sizeof(*lgraph))))
		return (1);
	lgraph[vertexcount] = NULL;
	i = -1;
	while (++i < vertexcount)
	{
		j = -1;
		k = 0;
		while (++j < edgecount)
		{
			if (egraph[j].x == i)
				k++;
			else if (egraph[j].y == i)
				k++;
		}
		printf("i %i j %i k %i\n", i, j, k);
		if (!(*(lgraph + i) = malloc(k * sizeof(**lgraph))))
			return (1);
	}
	i = -1;
	while (++i < vertexcount)
	{
		j = -1;
		k = 0;
		while (++j < edgecount)
		{
			if (egraph[j].x == i)
			{
				lgraph[i][k].vertex == egraph[j].y;
				lgraph[i][k].weight == egraph[j].weight;
				k++;
			}
			else if (egraph[j].y == i)
			{
				lgraph[i][k].vertex == egraph[j].x;
				lgraph[i][k].weight == egraph[j].weight;
				k++;
			}
		}
	}

	free(egraph);
	free(agraph);
	free(lgraph);
}
