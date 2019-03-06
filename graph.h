#ifndef GRAPH_H
# define GRAPH_H

typedef struct	s_edge
{
	int						x;
	int						y;
	int						weight;
}							t_edge;

typedef struct	s_adjacency_matrix_element
{
	int						vertex;
	int						weight;
}							t_madj;

typedef struct	s_adj_list_elem
{
	int						vertex;
	int						weight;
	struct s_adj_list_elem	*next;
}							t_ladj;

t_ladj	*lstnew(int vert, int wt);
int		lstadd_front(t_ladj **lst, int vert, int wt);
int		lstadd_sort(t_ladj **lst, int vert, int wt);
void	lstdel(t_ladj **lst);

#endif
