#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(str) + 1;
	dup = malloc(len);
	if (dup == NULL)
	{
		return (NULL);
	}
	ft_memcpy(dup, str, len);
	return (dup);
}
