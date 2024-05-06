#include "../../minishell.h"

static int	valid_nnl_option(char *opt)
{
	int		i;

	if (opt[0] != '-')
		return (false);
	i = 0;
	while (opt[++i])
	{
		if (opt[i] != 'n')
			return (false);
	}
	return (true);
}

void	echo(char **tokens)
{
	int		start;

	start = 1;
	while (tokens[start] != NULL && valid_nnl_option(tokens[start]))
		start++;
	tkn_to_str(tokens, start);
	if (start == 1)
		printf("\n");
}
