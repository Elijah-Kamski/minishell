#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	size_t	s1_len;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = s1_len - 1;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	trimmed_str = ft_substr(s1, start, end - start + 1);
	return (trimmed_str);
}
