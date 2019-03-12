#include <stdio.h>
#include "libft.h"
#define SIZE 10

static void	permute(char *elem, char *sol, char *dp, int i, int len)
{
	int	k;

	if (i == len)
		printf("%s\n", sol);
	else
	{
		k = -1;
		while (++k < len)
		{
			if (!dp[k])
			{
				sol[i] = elem[k];
				dp[k] = elem[k];
				permute(elem, sol, dp, i + 1, len);
				sol[i] = '\0';
				dp[k] = '\0';
			}
		}
	}
}

int	main(void)
{
	char	elem[SIZE] = "abcdefghi\0";
	char	sol[SIZE];
	char	dp[SIZE];

	ft_bzero(sol, SIZE);
	ft_bzero(dp, SIZE);
	permute(elem, sol, dp, 0, ft_strlen(elem));
}
