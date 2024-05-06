#include "libft.h"

void	ft_bzero(void *ptr, size_t num)
{
	unsigned char		*p;

	p = ptr;
	while (num--)
	{
		*p++ = 0;
	}
}
