#include "../../minishell.h"

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

static int	do_pipe_quotes_open(int *in_quotes, char *str, int *i, int pipe_idx)
{
	int		aux;

	aux = 0;
	while (aux <= pipe_idx)
	{
		while ((str[*i] != '|') && str[*i] != '\0')
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

int	count_pipes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

static int	build_pipe_quotes_array_helper(char *str, int pipe_idx)
{
	int		i;
	int		in_quotes[2];
	int		are_quotes;

	i = 0;
	in_quotes[0] = -1;
	in_quotes[1] = -1;
	if (pipe_idx > (count_pipes(str) - 1))
		return (-1);
	are_quotes = do_pipe_quotes_open (in_quotes, str, &i, pipe_idx);
	if (are_quotes == 0)
		return (0);
	else if (are_quotes == -1)
		return (-1);
	if (in_quotes[0] == 1 || in_quotes[1] == 1)
		return (do_quotes_close(in_quotes, str, &i));
	return (0);
}

void	build_pipe_quotes_array(char *str, int **p_qut_array,
	int pipe_count)
{
	int		pipe_idx;

	pipe_idx = 0;
	*p_qut_array = (int *)malloc(pipe_count * sizeof(int));
	while (pipe_idx < pipe_count)
	{
		(*p_qut_array)[pipe_idx] = build_pipe_quotes_array_helper(str,
				pipe_idx);
		pipe_idx++;
	}
}
