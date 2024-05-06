#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == NULL && src == NULL)
	{
		return (NULL);
	}
	d = dest;
	s = src;
	while (num--)
	{
		*d++ = *s++;
	}
	return (dest);
}
