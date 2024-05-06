#include "../minishell.h"

static void	too_many_args(int inside_pipe)
{
	int		i;
	int		j;

	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	get_status(1);
	if (inside_pipe == 0)
	{
		i = 0;
		while (info()->commands[i] != NULL)
		{
			j = 0;
			while (info()->commands[i][j] != NULL)
				free(info()->commands[i][j++]);
			free(info()->commands[i++]);
		}
		free(info()->commands);
		return (main_loop());
	}
	else
		exit(cleanup(1));
}

static long	exit_atoi(const char *str)
{
	long int	result;
	int			sign;
	int			i;
	long long	tempnum;

	result = 0;
	sign = 1;
	i = -1;
	while (ft_isspace(str[i + 1]))
		i++;
	if (str[++i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	tempnum = 0;
	while (ft_isdigit(str[i]))
	{
		if ((ft_numlen(result) == 18)
			&& ((sign == 1 && (str[i] > '7' || (tempnum > (long long) 922337203685477580)))
				|| (sign == -1 && (str[i] > '8' || (tempnum > (long long) 922337203685477580)))
				|| (ft_numlen(result) > 18)))
			return (0);
		result = result * 10 + (str[i] - '0');
		if (ft_numlen(result) == 18)
			tempnum = result;
		i++;
	}
	return (sign * result);
}

void	exit_minishell(char **tokens, int inside_pipe)
{
	long	val;
	int		i;

	if (tokens == NULL || tokens[0] == NULL || tokens[1] == NULL)
	{
		rl_clear_history();
		exit(cleanup(0));
	}
	val = exit_atoi(tokens[1]);
	i = 0;
	while (tokens[1][i] == '-' || tokens[1][i] == '+')
		i++;
	while (tokens[1][i] != '\0' && ft_isdigit(tokens[1][i]))
		i++;
	if ((val == 0 && tokens[1][0] != '0') || tokens[1][i] != '\0')
	{
		ft_putstr_fd(tokens[1], STDERR_FILENO);
		ft_putendl_fd(": minishell: exit: numeric argument required", 2);
		rl_clear_history();
		exit(cleanup(2));
	}
	if (tokens && tokens[0] && tokens[1] && tokens[2] != NULL)
		return (too_many_args(inside_pipe));
	exit(cleanup(val));
}

static void	main_helper(int i, char **envp)
{
	int		j;

	info()->export[i] = malloc(sizeof(t_exp));
	(info())->export[i]->name = ft_strtok(envp[i], '=');
	(info())->export[i]->content = ft_strdup(ft_strtok(NULL, '\0'));
	if (ft_strncmp(info()->export[i]->name, "SHLVL", 6) == 0)
	{
		j = ft_atoi(info()->export[i]->content);
		free(info()->export[i]->content);
		info()->export[i]->content = ft_itoa(j + 1);
	}
	else if (ft_strncmp(info()->export[i]->name, "OLDPWD", 7) == 0)
		info()->oldpwd = ft_strdup(info()->export[i]->content);
	else if (ft_strncmp(info()->export[i]->name, "PWD", 4) == 0)
		info()->curpwd = ft_strdup(info()->export[i]->content);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;

	(void)argc;
	(void)argv;
	info()->nb = 0;
	info()->paused = false;
	info()->cmplt_inp = NULL;
	info()->pid_array = NULL;
	i = 0;
	while (envp[i] != NULL)
		i++;
	info()->export = malloc((i + 1) * sizeof(t_exp *));
	if (info()->export == NULL)
		exit(cleanup(1));
	info()->export[i] = NULL;
	while (--i >= 0)
		main_helper(i, envp);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	info()->old_std = malloc(2 * sizeof(int));
	info()->old_std[0] = dup(STDIN_FILENO);
	info()->old_std[1] = dup(STDOUT_FILENO);
	main_loop();
	return (0);
}
