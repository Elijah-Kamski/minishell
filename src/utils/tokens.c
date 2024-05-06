#include "../../minishell.h"

int	has_only_one_command(char ***commands)
{
	int		count;

	count = 0;
	while (commands[count] != NULL)
	{
		count++;
	}
	return (count == 1);
}

void	tokenize_path(char *input, char *tokens[MAX_TOKENS], int *num_tokens)
{
	char	*token;

	*num_tokens = 0;
	token = ft_strtok(input, ':');
	while (token != NULL && *num_tokens < MAX_TOKENS)
	{
		tokens[*num_tokens] = append(token, "/", 0);
		(*num_tokens)++;
		token = ft_strtok(NULL, ':');
	}
	if (token != NULL)
		free(token);
	tokens[*num_tokens] = NULL;
}

static void	get_cmd_tokens_helper(char *str, int *i, char **tok, \
	int *cur_dolsig)
{
	char	q;
	char	*s;
	int		l;

	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	if (!str[*i])
		return ;
	q = 0;
	s = str + *i - 1;
	while (*(++s))
	{
		if (*s == '$')
			(*cur_dolsig)++;
		if ((((str[*i] == '<' || str[*i] == '>' || *s == '<' || *s == '>')
					&& *s != str[*i]) || *s == ' ') && q == 0)
			break ;
		if (*s == '"' && q != '\'')
			q = '"' - q;
		else if (*s == '\'' && q != '"')
			q = '\'' - q;
	}
	l = s - str - *i;
	*tok = ft_substr(str, *i, l);
	*i += l - 1;
}

void	get_cmd_tokens(char *str, char **cmd)
{
	int		tok;
	int		i;
	int		cur_dolsig;
	char	*tmp;

	cur_dolsig = -1;
	tok = 0;
	i = -1;
	while ((i == -1 || str[i]) && str[++i])
	{
		cmd[tok] = NULL;
		get_cmd_tokens_helper(str, &i, cmd + tok, &cur_dolsig);
		if (tok == 0 || (cmd[tok - 1] && ft_strncmp(cmd[tok - 1], "<<", 3)))
		{
			tmp = parse_env(cmd[tok]);
			free(cmd[tok]);
			cmd[tok] = NULL;
			if (tmp)
				cmd[tok] = parse_input(tmp, 0);
		}
		tok++;
	}
	cmd[tok] = NULL;
}

void	tkn_to_str(char **tokens, int start)
{
	int		t;

	t = start;
	while (tokens[t] != NULL)
	{
		printf("%s", tokens[t]);
		if (tokens[++t] != NULL)
			printf(" ");
	}
}
