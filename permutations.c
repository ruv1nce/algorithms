#include <stdio.h>
#include "libft.h"

static void	permute(char *elem, char *sol, int i, int len)
{
	int	k;

	if (i == len)
		printf("%s\n", sol);
	else
	{
		k = -1;
		while (++k < len)
		{
			if (!(ft_strchr(sol, elem[k])))
			{
				sol[i] = elem[k];
				permute(elem, sol, i + 1, len);
				sol[i] = '\0';
			}
		}
	}
}

int	main(void)
{
	char	elem[10] = "abcdefghi\0";
	char	sol[10] = "\0\0\0\0\0\0\0\0\0";

	permute(elem, sol, 0, ft_strlen(elem));
}
