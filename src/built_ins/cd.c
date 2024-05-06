#include "../../minishell.h"

static void	update_pwd(int i)
{
	if (ft_strncmp(info()->export[i]->name, "OLDPWD", 7) == 0
		|| ft_strncmp(info()->export[i]->name, "PWD", 4) == 0)
	{
		if (info()->export[i]->content != NULL)
			free(info()->export[i]->content);
		info()->export[i]->content = NULL;
	}
	if (ft_strncmp(info()->export[i]->name, "OLDPWD", 7) == 0
		&& info()->oldpwd != NULL)
		info()->export[i]->content = ft_strdup(info()->oldpwd);
	else if (ft_strncmp(info()->export[i]->name, "PWD", 4) == 0
		&& info()->curpwd != NULL)
		info()->export[i]->content = ft_strdup(info()->curpwd);
}

static char	*get_dir(char *input)
{
	size_t	dest_size;
	char	*dest;
	char	*home;

	dest = NULL;
	if (input == NULL || input[0] == '\0' || ft_strncmp(input, "~", 2) == 0)
		input = getenv_from_array("HOME");
	else if (ft_strncmp(input, "-", 2) == 0)
		input = getenv_from_array("OLDPWD");
	else
		input = ft_strdup(input);
	if (input != NULL && ft_strncmp(input, "~", 1) == 0)
	{
		home = getenv_from_array("HOME");
		dest_size = ft_strlen(home) + ft_strlen(input);
		dest = (char *)ft_calloc(dest_size, sizeof(char));
		ft_strncat(dest, home, ft_strlen(home) + 1);
		ft_strncat(dest, (input + 1), ft_strlen(input + 1) + 1);
		free(home);
	}
	if (dest == NULL && input != NULL)
		dest = ft_strdup(input);
	if (input != NULL)
		free(input);
	return (dest);
}

int	cd(char *input)
{
	char	*dest;
	int		i;

	dest = get_dir(input);
	if (dest == NULL || chdir(dest) != 0)
	{
		if (errno == EACCES)
			ft_putendl_fd("minishell: cd: permission denied", STDERR_FILENO);
		else
			ft_putendl_fd("minishell: cd: not a valid directory", 2);
		if (dest != NULL)
			free(dest);
		return (1);
	}
	free(dest);
	if (info()->oldpwd != NULL)
		free(info()->oldpwd);
	info()->oldpwd = info()->curpwd;
	(info())->curpwd = getcwd(NULL, 0);
	i = -1;
	while (info()->export[++i] != NULL)
		update_pwd(i);
	return (0);
}
