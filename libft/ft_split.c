#include "libft.h"

static void	ft_free_str_array(char **str_array)
{
	size_t	i;

	i = 0;
	while (str_array[i])
	{
		free(str_array[i]);
		i++;
	}
	free(str_array);
}

static char	**ft_split_internal(char const *s, char c, size_t wc)
{
	char		**res;
	size_t		i;
	const char	*end;

	i = 0;
	res = (char **)ft_calloc(wc + 1, sizeof(char *));
	if (!res)
		return (NULL);
	while (i < wc)
	{
		while (*s == c)
			s++;
		end = ft_strchr(s, c);
		if (!end)
			end = s + ft_strlen(s);
		res[i] = ft_substr(s, 0, end - s);
		if (!res[i])
		{
			ft_free_str_array(res);
			return (NULL);
		}
		s = end;
		i++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	size_t	wc;

	if (!s)
		return (NULL);
	wc = ft_count_words(s, c);
	return (ft_split_internal(s, c, wc));
}
