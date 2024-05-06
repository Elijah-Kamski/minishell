#include "../../minishell.h"

static int	init_info_struct_helper(void)
{
	if (info()->commands && info()->commands[0]
		&& !info()->commands[0][0])
	{
		free(info()->commands[0]);
		info()->commands[0] = NULL;
	}
	if (info()->commands && !info()->commands[0])
	{
		free(info()->commands);
		info()->commands = NULL;
	}
	if (!info()->commands || !info()->commands[0]
		|| !info()->commands[0][0])
		return (1);
	return (0);
}

static int	init_info_struct(void)
{
	char	*input;

	if (info()->cmplt_inp != NULL)
		free(info()->cmplt_inp);
	info()->cmplt_inp = NULL;
	info()->commands = NULL;
	info()->pipes = NULL;
	input = readline("minishell$   ");
	if (!input)
		return (2);
	if (input[0] == '\0' || ft_strlen(input) == 0)
		return (1);
	add_history(input);
	info()->commands = get_cmds(input);
	return (init_info_struct_helper());
}

static void	free_commands(void)
{
	int		i;
	int		j;

	if (info()->commands != NULL)
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
	}
}

static void	main_loop_helper(int i)
{
	if (has_only_one_command(info()->commands))
	{
		i = preload_heredocs(1);
		if (i != 130 && get_inputs(info()->commands[0]) == 0)
			one_command_handler(info()->commands[0]);
	}
	else
		execute_pipeline(i);
	dup2(info()->old_std[0], STDIN_FILENO);
	dup2(info()->old_std[1], STDOUT_FILENO);
	free_commands();
}

void	main_loop(void)
{
	int		i;

	i = init_info_struct();
	if (i == 2)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		return (exit_minishell(NULL, 0));
	}
	else if (i == 1 || !info()->commands || info()->commands[0] == NULL)
	{
		free_commands();
		return (main_loop());
	}
	if (info()->commands[0] != NULL && info()->commands[1] == NULL
		&& ft_strncmp(info()->commands[0][0], "exit", 5) == 0)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		return (exit_minishell(info()->commands[0], 0));
	}
	i = 0;
	while (info()->commands[i] != NULL)
		i++;
	main_loop_helper(i);
	main_loop();
}
