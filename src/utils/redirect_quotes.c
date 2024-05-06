#include "../../minishell.h"

static int	count_substring(char *haystack, char *needle)
{
	int		count;
	size_t	needle_len;
	char	*ptr;
	size_t	remaining_len;
	size_t	haystack_len;

	count = 0;
	needle_len = ft_strlen(needle);
	ptr = haystack;
	remaining_len = ft_strlen(haystack);
	haystack_len = remaining_len;
	ptr = ft_strnstr(ptr, needle, remaining_len);
	while (remaining_len >= needle_len && (ptr != NULL))
	{
		count++;
		ptr += needle_len;
		remaining_len = haystack_len - (ptr - haystack);
		ptr = ft_strnstr(ptr, needle, remaining_len);
	}
	return (count);
}

int	count_redirects(char *str)
{
	int		count;

	count = count_substring(str, "<") + count_substring(str, ">")
		- count_substring(str, "<<") - count_substring(str, ">>");
	return (count);
}

static int	do_quotes_open(int *in_quotes, char *str, int *i, int redirect_idx)
{
	int		aux;

	aux = 0;
	while (aux <= redirect_idx)
	{
		while ((str[*i] != '<' && str[*i] != '>') && str[*i] != '\0')
		{
			if (str[*i] == '\'')
				in_quotes[0] = -in_quotes[0];
			if (str[*i] == '"')
				in_quotes[1] = -in_quotes[1];
			(*i)++;
		}
		if (str[*i] == '\0')
			return (-1);
		while (str[*i] == str[*i + 1])
			(*i)++;
		(*i)++;
		aux++;
	}
	if (in_quotes[0] == 1 || in_quotes[1] == 1)
		return (1);
	return (0);
}

static int	do_quotes_close(int *in_quotes, char *str, int *i)
{
	while (str[*i] != '\0')
	{
		if (in_quotes[0] == 1 && in_quotes[1] == -1)
		{
			if (str[*i] == '\'')
				return (1);
		}
		else if (in_quotes[0] == -1 && in_quotes[1] == 1)
		{
			if (str[*i] == '"')
				return (1);
		}
		else
		{
			if (str[*i] == '"' || str[*i] == '\'')
				return (1);
		}
		(*i)++;
	}
	return (0);
}

int	rdr_qts(char *str, int redirect_idx)
{
	int		i;
	int		in_quotes[2];
	int		are_quotes;

	i = 0;
	in_quotes[0] = -1;
	in_quotes[1] = -1;
	if (redirect_idx > (count_redirects(str) - 1))
		return (-1);
	are_quotes = do_quotes_open (in_quotes, str, &i, redirect_idx);
	if (are_quotes == 0)
		return (0);
	else if (are_quotes == -1)
		return (-1);
	if (in_quotes[0] == 1 || in_quotes[1] == 1)
		return (do_quotes_close(in_quotes, str, &i));
	return (0);
}
