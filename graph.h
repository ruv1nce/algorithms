#ifndef GRAPH_H
# define GRAPH_H

typedef struct	s_edge
{
	int			x;
	int			y;
	int			weight;
}				t_edge;

typedef struct	s_adjacency_element
{
	int			vertex;
	int			weight;
}				t_adj;

#endif
