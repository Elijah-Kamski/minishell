#include "../../minishell.h"

static t_exp	**make_new_exp(char *input, int i, char *name)
{
	char	*tmp;
	t_exp	**new_exp;

	new_exp = malloc((i + 2) * sizeof(t_exp *));
	new_exp[i + 1] = NULL;
	new_exp[i] = malloc(sizeof(t_exp));
	new_exp[i]->name = name;
	tmp = ft_strtok(NULL, '\0');
	if (tmp != NULL && tmp[0] != '\0')
		new_exp[i]->content = ft_strdup(tmp);
	else if (input[ft_strlen(name)] == '=')
		new_exp[i]->content = ft_strdup("");
	else
	{
		new_exp[i]->content = NULL;
		if (ft_strncmp(name, "OLDPWD", 7) == 0 && info()->oldpwd)
			new_exp[i]->content = ft_strdup(info()->oldpwd);
		else if (ft_strncmp(name, "PWD", 4) == 0 && info()->curpwd)
			new_exp[i]->content = ft_strdup(info()->curpwd);
	}
	return (new_exp);
}

static bool	is_valid(const char *str)
{
	int		i;

	if (str == NULL)
		return (0);
	if (str[0] == '=')
		return (0);
	i = -1;
	if (ft_isdigit(str[0]) == true)
		return (0);
	while (str[++i] != '\0' && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == false && str[i] != '_')
			return (0);
	}
	return (1);
}

static void	replace_on_env(char *input, char *name, int i)
{
	char	*tmp;

	if (info()->export[i] == NULL)
		return ;
	tmp = ft_strtok(NULL, '\0');
	if (info()->export[i]->content != NULL
		&& ((tmp != NULL && tmp[0] != '\0') || input[ft_strlen(name)] == '='))
		free(info()->export[i]->content);
	if (tmp != NULL && tmp[0] != '\0')
		info()->export[i]->content = ft_strdup(tmp);
	else if (input[ft_strlen(name)] == '=')
		info()->export[i]->content = ft_strdup("");
	if (ft_strncmp(name, "OLDPWD", 7) == 0)
	{
		if (info()->oldpwd != NULL)
			free(info()->oldpwd);
		info()->oldpwd = ft_strdup(info()->export[i]->content);
	}
	else if (ft_strncmp(name, "PWD", 4) == 0)
	{
		if (info()->curpwd != NULL)
			free(info()->curpwd);
		info()->curpwd = ft_strdup(info()->export[i]->content);
	}
	free(name);
}

static void	add_env(char *input)
{
	int		i;
	char	*name;
	t_exp	**new_exp;

	if (is_valid(input) == false)
	{
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putendl_fd(": minishell: export: not a valid identifier", 2);
		return ;
	}
	name = ft_strtok(input, '=');
	i = 0;
	while (info()->export[i] != NULL
		&& ft_strncmp(info()->export[i]->name, name, ft_strlen(name) + 1))
		i++;
	if (info()->export[i] != NULL)
		return (replace_on_env(input, name, i));
	new_exp = make_new_exp(input, i, name);
	while (--i >= 0)
		new_exp[i] = info()->export[i];
	free(info()->export);
	info()->export = new_exp;
}

void	env_builtins(char **tokens)
{
	int		token_lines_count;
	int		aux;

	aux = 0;
	token_lines_count = 0;
	while (tokens[token_lines_count] != NULL)
		token_lines_count++;
	if (strncmp(tokens[0], "export", 7) == 0)
	{
		while ((aux + 2) <= token_lines_count)
			add_env(tokens[++aux]);
		if (token_lines_count == 1)
			show_export();
	}
	else if (strncmp(tokens[0], "unset", 6) == 0)
	{
		while ((aux + 2) <= token_lines_count)
			unset_env(tokens[++aux]);
	}
	else if (strncmp(tokens[0], "env", 4) == 0)
		env();
}
