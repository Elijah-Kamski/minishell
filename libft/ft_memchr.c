#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p = (const unsigned char *)s;
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (*p == (unsigned char)c)
		{
			return ((void *)p);
		}
		p++;
		i++;
	}
	return (NULL);
}
