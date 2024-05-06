#include "../../minishell.h"

int	pipes_outside_quotes(int *pipe_quotes_array, int pc)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (i < pc)
	{
		if (pipe_quotes_array[i] == 0)
			count++;
		i++;
	}
	return (count);
}

char	*pipe_strchr(const char *s,
		int *pipe_quotes_array, int *pipe_curr_idx)
{
	while (*s != '\0')
	{
		if (*s == '|' && pipe_quotes_array[*pipe_curr_idx] == 0)
		{
			(*pipe_curr_idx)++;
			return ((char *)s);
		}
		else if (*s == '|' && pipe_quotes_array[*pipe_curr_idx] == 1)
		{
			(*pipe_curr_idx)++;
			s++;
		}
		s++;
	}
	return (NULL);
}
