#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t num)
{
	char	*d;

	d = dest + ft_strlen(dest);
	while (*src && num--)
	{
		*d++ = *src++;
	}
	*d = '\0';
	return (dest);
}
