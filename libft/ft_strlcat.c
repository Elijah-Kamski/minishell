#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	total_len;
	size_t	copy_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	total_len = dest_len + src_len;
	if (dest_len >= size)
	{
		return (src_len + size);
	}
	copy_len = size - dest_len - 1;
	ft_strncat(dest, src, copy_len);
	return (total_len);
}
