#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

unsigned long long fib_dyn(unsigned long long *fib, int num)
{
	if (fib[num] == 4)
	{
		if (num == 0)
			fib[num] = 0;
		else if (num == 1)
			fib[num] = 1;
		else
			fib[num] = fib_dyn(fib, (num - 1)) + fib_dyn(fib, (num - 2));
	}
	return (fib[num]);
}

int	main(int argc, char **argv)
{
	unsigned long long	*fib;
	int num;
	int	i;

	if (argc < 2)
	{
		printf("Specify the number\n");
		return (0);
	}
	num = atoi(argv[1]);
	if (num < 0)
	{
		printf("Invalid number\n");
		return (0);
	}
	if (!(fib = malloc((num + 1) * sizeof(*fib))))
			return (1);
	i = -1;
	while (++i <= num)
		fib[i] = 4;
	printf("%llu\n", fib_dyn(fib, num));
}
