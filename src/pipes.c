#include "../minishell.h"

static void	sigpipe_handler(int signo)
{
	(void)signo;
	exit(cleanup(0));
}

static int	pipeline_fork_helper(int num_commands, int i)
{
	int		aux;

	aux = -1;
	info()->nb = i;
	while (info()->pipes[++aux] != NULL)
	{
		if (aux != i)
			close(info()->pipes[aux][1]);
		if (aux != i - 1)
			close(info()->pipes[aux][0]);
	}
	if (i > 0)
	{
		dup2(info()->pipes[i - 1][0], STDIN_FILENO);
		close(info()->pipes[i - 1][0]);
		close(info()->pipes[i - 1][1]);
	}
	if (i < num_commands - 1)
		dup2(info()->pipes[i][1], STDOUT_FILENO);
	if (get_inputs(info()->commands[i]) == -1)
		exit(cleanup(2));
	command_handler(info()->commands[i]);
	return (1);
}

static int	pipeline_fork(int num_commands)
{
	int		i;

	i = -1;
	while (++i < num_commands)
	{
		info()->pid_array[i] = fork();
		if (info()->pid_array[i] == -1)
		{
			perror("fork");
			exit(cleanup(EXIT_FAILURE));
		}
		if (info()->pid_array[i] == 0)
		{
			pipeline_fork_helper(num_commands, i);
			return (0);
		}
		if (i > 0)
		{
			close(info()->pipes[i - 1][0]);
			close(info()->pipes[i - 1][1]);
		}
	}
	return (1);
}

static int	pipeline_helper(int num_commands, int *status, int i)
{
	pid_t	terminated_pid;
	int		j;

	if (info()->pid_array != NULL)
		free(info()->pid_array);
	info()->pid_array = malloc((num_commands + 1) * sizeof(pid_t));
	if (pipeline_fork(num_commands) == 0)
		return (0);
	while (i < num_commands)
	{
		terminated_pid = wait(status);
		j = 0;
		while (terminated_pid != info()->pid_array[j]
			&& info()->pid_array[j] != 0)
			j++;
		if (j == num_commands - 1)
			get_status(WEXITSTATUS(*status));
		if (info()->pid_array[j] != 0)
		{
			if (--j >= 0)
				free(info()->pipes[j]);
			i++;
		}
	}
	return (1);
}

void	execute_pipeline(int num_commands)
{
	int		i;
	int		status;

	signal(SIGPIPE, sigpipe_handler);
	info()->pipes = malloc((num_commands) * sizeof (int [2]));
	i = -1;
	while (++i < num_commands - 1)
		pipe(info()->pipes[i] = malloc(2 * sizeof(int)));
	info()->pipes[num_commands - 1] = NULL;
	status = preload_heredocs(num_commands);
	if (status != 130 && pipeline_helper(num_commands, &status, 0) == 0)
		return ;
	else if (status == 130)
	{
		i = -1;
		while (info()->pipes[++i] != NULL)
		{
			close(info()->pipes[i][0]);
			close(info()->pipes[i][1]);
			free(info()->pipes[i]);
		}
	}
	free(info()->pipes);
	info()->pipes = NULL;
}
