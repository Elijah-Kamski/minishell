#include "../minishell.h"

static int	execute_helper(char	**tokens)
{
	int		i;
	char	*tmp;
	char	*path[MAX_TOKENS];
	char	**env;

	env = get_environ();
	execve(tokens[0], tokens, env);
	tmp = getenv_from_array("PATH");
	tokenize_path(tmp, path, &i);
	free(tmp);
	i = 0;
	while (path[i] != NULL)
	{
		tmp = append(path[i++], tokens[0], 0);
		execve(tmp, tokens, env);
		free(tmp);
	}
	ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	ft_putendl_fd(tokens[0], STDERR_FILENO);
	i = 0;
	while (env[i] != NULL)
		free(env[i++]);
	free(env);
	exit(cleanup(127));
}

static int	execute(char **tokens)
{
	int		i;
	int		pid;

	info()->paused = true;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		execute_helper(tokens);
	}
	waitpid(pid, &i, 0);
	info()->paused = false;
	if (i == 2 && get_status(-1) == 130)
		return (130);
	if (i < 256)
		return (i);
	return (WEXITSTATUS(i));
}

static void	builtin_commands(char **tokens, int *status)
{
	if (strncmp(tokens[0], "echo", 5) == 0)
		echo(tokens);
	else if (strncmp(tokens[0], "pwd", 4) == 0)
		pwd();
	else if (strncmp(tokens[0], "cd", 3) == 0)
	{
		if (tokens[1] && tokens[2])
		{
			*status = 2;
			ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		}
		else
			*status = cd(tokens[1]);
	}
	else if (strncmp(tokens[0], "exit", 5) == 0)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit_minishell(tokens, 1);
	}
	env_builtins(tokens);
}

void	command_handler(char **tokens)
{
	int		status;

	status = 0;
	if (tokens == NULL || tokens[0] == NULL)
		exit(cleanup(0));
	if (strncmp(tokens[0], "echo", 5) == 0
		|| strncmp(tokens[0], "pwd", 4) == 0
		|| strncmp(tokens[0], "cd", 3) == 0
		|| strncmp(tokens[0], "export", 7) == 0
		|| strncmp(tokens[0], "unset", 6) == 0
		|| strncmp(tokens[0], "env", 4) == 0)
		builtin_commands(tokens, &status);
	else if (strncmp(tokens[0], "exit", 5) == 0)
		exit_minishell(tokens, 1);
	else
		status = execute(tokens);
	exit(cleanup(status));
}

void	one_command_handler(char **tokens)
{
	int		status;

	status = 0;
	if (tokens == NULL || tokens[0] == NULL)
		return ;
	if (strncmp(tokens[0], "echo", 5) == 0
		|| strncmp(tokens[0], "pwd", 4) == 0
		|| strncmp(tokens[0], "cd", 3) == 0
		|| strncmp(tokens[0], "export", 7) == 0
		|| strncmp(tokens[0], "unset", 6) == 0
		|| strncmp(tokens[0], "env", 4) == 0
		|| strncmp(tokens[0], "exit", 5) == 0)
		builtin_commands(tokens, &status);
	else
		status = execute(tokens);
	get_status(status);
}
