#include "../../minishell.h"

static void	parse_env_helper(int i[3], char *input, char **str, int dq)
{
	char	*tmp;
	char	*sub;

	if (input[i[0]])
		i[0]++;
	if (input[i[0] - 1] == '$' && (ft_isalpha(input[i[0]]) || input[i[0]] == '?'
			|| input[i[0]] == '\'' || (input[i[0]] == '"' && dq == -1)))
	{
		*str = append(*str, ft_substr(input, i[2], i[0] - i[2] - 1), 1);
		i[2] = i[0]++;
		i[1] = 0;
		while ((input[i[0] + i[1]])
			&& (ft_isalnum(input[i[0] + i[1]]) || (input[i[0] + i[1]]) == '_'))
			i[1]++;
		i[0] += i[1];
		sub = ft_substr(input, i[2], i[0] - i[2]);
		tmp = getenv_from_array(sub);
		free(sub);
		if (tmp)
			*str = append(*str, tmp, 1);
		i[2] = i[0]--;
	}
}

char	*parse_env(char *input)
{
	int		i[3];
	char	*str;
	int		dq;

	if (input == NULL)
		return (NULL);
	str = malloc(sizeof(char));
	str[0] = '\0';
	i[2] = 0;
	i[0] = 0;
	dq = -1;
	while (input[i[0]] != '\0')
	{
		if (input[i[0]] == '\'' && input[++i[0]] && dq == -1)
			while (input[i[0]] && input[i[0]] != '\'')
				i[0]++;
		if (input[i[0]] == '\"')
			dq = -dq;
		parse_env_helper(i, input, &str, dq);
	}
	if (input[i[2]])
		str = append(str, ft_substr(input, i[2], i[0] - i[2]), 1);
	return (str);
}

static void	separate_cmds_cleaner(char ***cmd, char **tmp, int i)
{
	int		j;
	int		k;

	j = i;
	cmd[i] = NULL;
	while (tmp[i] != NULL)
		free(tmp[i++]);
	free(tmp);
	if (j >= MAX_CMDS)
	{
		ft_putendl_fd("minishell: too many commands", STDERR_FILENO);
		while (--j >= 0)
		{
			k = -1;
			while (cmd[j][++k])
				free(cmd[j][k]);
			free(cmd[j]);
		}
		cmd[0] = NULL;
	}
}

static void	separate_cmds(char *input, char ***cmd)
{
	char	**tmp;
	int		i;

	i = detect_consecutive_pipes(input);
	cmd[0] = NULL;
	if (i == 1)
		ft_putendl_fd(ERR_UNXPC_TOK, STDERR_FILENO);
	if (i != 0)
		return ;
	tmp = pipe_split(input);
	i = 0;
	while (i < MAX_CMDS && tmp[i] != NULL && tmp[i][0] != '\0')
	{
		cmd[i] = malloc(MAX_TOKENS * sizeof(char *));
		ft_strtok(tmp[i], '\0');
		get_cmd_tokens(tmp[i], cmd[i]);
		free(tmp[i++]);
	}
	separate_cmds_cleaner(cmd, tmp, i);
}

char	***get_cmds(char *input)
{
	char	***cmds;
	char	*tmp;

	if (input[0] == '|' || is_redirect_at_the_end(input) == 1)
	{
		ft_putendl_fd(ERR_UNXPC_TOK, STDERR_FILENO);
		free(input);
		return (NULL);
	}
	if (are_quotes_even(input) == 0)
	{
		ft_putendl_fd("minishell: syntax error due to unclosed quotes", 2);
		free(input);
		return (NULL);
	}
	info()->cmplt_inp = ft_strdup(input);
	info()->cur_redir = 0;
	cmds = malloc((MAX_CMDS + 1) * sizeof(char **));
	tmp = ft_strtrim(input, " \t\n");
	free(input);
	input = tmp;
	separate_cmds(input, cmds);
	free(input);
	return (cmds);
}
