#include "../../minishell.h"

static char	*pipe_split_helper_2(char *end, int *aux,
				char **res, int *pipe_curr_idx)
{
	int		aux_pipe_skip;
	char	*s;

	if (!res[*aux])
	{
		while (*aux > 0)
			free(res[--(*aux)]);
		free(res);
		return (NULL);
	}
	s = end;
	aux_pipe_skip = 0;
	while (*s == '|')
	{
		s++;
		if (aux_pipe_skip == 1)
			(*pipe_curr_idx)++;
		aux_pipe_skip = 1;
	}
	(*aux)++;
	if (end == (s + ft_strlen(s)))
		(*pipe_curr_idx)++;
	return (s);
}

static char	**pipe_split_helper(char *s, int pc, int *pipe_quotes_array)
{
	char	**res;
	int		pipe_curr_idx;
	int		aux;
	char	*end;

	pipe_curr_idx = 0;
	res = (char **)malloc((pipes_outside_quotes(pipe_quotes_array,
					pc) + 2) * sizeof(char *));
	if (!res)
		return (NULL);
	aux = 0;
	while (pipe_curr_idx < (pc + 1))
	{
		end = pipe_strchr(s, pipe_quotes_array, &pipe_curr_idx);
		if (end == NULL)
			end = s + ft_strlen(s);
		res[aux] = strndup(s, end - s);
		s = pipe_split_helper_2(end, &aux, res, &pipe_curr_idx);
	}
	res[aux] = NULL;
	return (res);
}

int	detect_consecutive_pipes(char *str)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	if (str == NULL || str[i] == '\0')
		return (-1);
	while (str[i + 1] != '\0')
	{
		if (str[i] != '|' && !ft_isspace(str[i]))
			flag = 0;
		if (str[i] == '|' && flag == 1)
			return (1);
		if (str[i] == '|')
			flag = 1;
		i++;
	}
	return (0);
}

char	**pipe_split(char *str)
{
	int		pc;
	int		*pipe_quotes_array;
	char	**result;

	if (!str)
		return (NULL);
	pc = count_pipes(str);
	build_pipe_quotes_array(str, &(pipe_quotes_array), pc);
	if (!pipe_quotes_array)
		return (NULL);
	result = pipe_split_helper(str, pc, pipe_quotes_array);
	free(pipe_quotes_array);
	return (result);
}
