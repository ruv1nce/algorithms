#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*lcsubstr(char *s1, int len1, char* s2, int len2)
{
	char	grid[len1 + 1][len2 + 1];
	char	*lcs;
	int		i;
	int		j;
	int		max;
	int		maxi;
	int		maxj;

	max = 0;
	maxi = 0;
	maxj = 0;
	i = -1;
	while (++i < len1)
	{
		j = -1;
		while (++j < len2)
			grid[i][j] = 0;
	}
	i = -1;
	while (s1[++i])
	{
		j = -1;
		while (s2[++j])
		{
			if (s1[i] == s2[j])
				grid[i + 1][j + 1] = grid[i][j] + 1;
			if (max < grid[i + 1][j + 1])
			{
				max = grid[i + 1][j + 1];
				maxi = i + 1;
				maxj = j + 1;
			}
		}
	}
	lcs = malloc(max + 1);
	lcs[max] = 0;
	while (--max >= 0)
	{
		lcs[max] = s2[maxj - 1];
		maxj--;
	}
	return (lcs);
}

int		main(int argc, char **argv)
{
	if (argc == 3)
	{
		printf("%s\n", lcsubstr(argv[1], strlen(argv[1]), argv[2], strlen(argv[2])));
	}
}
