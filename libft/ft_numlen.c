#include "libft.h"

int	ft_numlen(long int n)
{
	int		len;

	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}
