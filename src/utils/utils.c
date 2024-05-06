#include "../../minishell.h"

t_code	*info(void)
{
	static t_code	*info;

	if (info == NULL)
		info = malloc(sizeof(t_code));
	return (info);
}

int	get_status(int new_status)
{
	static int	status;

	if (new_status >= 0)
		status = new_status;
	return (status);
}

void	remove_fr_arr(char **arr, int index, int amount)
{
	int		i;

	while (arr[++index + amount] != NULL)
	{
		free(arr[index]);
		arr[index] = ft_strdup(arr[index + amount]);
	}
	i = 0;
	while (i < amount)
	{
		free(arr[index + i]);
		arr[index + i++] = NULL;
	}
}

void	ctrl_c_handler(int signo)
{
	(void)signo;
	get_status(130);
	if (info()->paused == false)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	is_redirect_at_the_end(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && (str[i] == '\t' || str[i] == ' ' || str[i] == '\n'))
		i--;
	if (i < 0)
		return (-1);
	if (str[i] == '|')
		return (1);
	return (0);
}
