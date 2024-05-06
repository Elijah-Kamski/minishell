#include "../../minishell.h"

static void	cleanup_helper(void)
{
	int		i;
	int		j;

	i = 0;
	while (info()->pipes != NULL && info()->pipes[i] != NULL)
	{
		close(info()->pipes[i][0]);
		close(info()->pipes[i][1]);
		free(info()->pipes[i++]);
	}
	if (info()->pipes != NULL)
		free(info()->pipes);
	i = 0;
	while (info()->commands != NULL
		&& info()->commands[i] != NULL)
	{
		j = 0;
		while (info()->commands[i][j] != NULL)
			free(info()->commands[i][j++]);
		free(info()->commands[i++]);
	}
	if (info()->commands != NULL)
		free(info()->commands);
	if (info()->cmplt_inp != NULL)
		free(info()->cmplt_inp);
}

static void	cleanup_helper_2(void)
{
	int		i;

	i = 0;
	while (info()->export[i] != NULL)
	{
		free(info()->export[i]->name);
		if (info()->export[i]->content != NULL)
			free(info()->export[i]->content);
		free(info()->export[i++]);
	}
	free(info()->export);
	if (info()->old_std != NULL)
	{
		close(info()->old_std[0]);
		close(info()->old_std[1]);
		free(info()->old_std);
	}
	if (info()->oldpwd != NULL)
		free(info()->oldpwd);
	if (info()->curpwd != NULL)
		free(info()->curpwd);
	if (info()->pid_array != NULL)
		free(info()->pid_array);
	free(info());
	free(ft_strtok(NULL, '\0'));
}

long	cleanup(long exit_code)
{
	cleanup_helper();
	cleanup_helper_2();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (exit_code);
}
