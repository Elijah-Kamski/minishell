#include "../../minishell.h"

static void	unset_pwd(const char *name)
{
	if (ft_strncmp(name, "OLDPWD", 7) == 0)
	{
		if (info()->oldpwd != NULL)
			free(info()->oldpwd);
		info()->oldpwd = NULL;
	}
	else if (ft_strncmp(name, "PWD", 4) == 0)
	{
		if (info()->curpwd != NULL)
			free(info()->curpwd);
		info()->curpwd = NULL;
	}
}

void	unset_env(const char *name)
{
	int		i;

	i = -1;
	while (info()->export[++i] != NULL)
	{
		if (ft_strncmp(info()->export[i]->name, \
			name, ft_strlen(name) + 1) == 0)
		{
			unset_pwd(name);
			free(info()->export[i]->name);
			if (info()->export[i]->content != NULL)
				free(info()->export[i]->content);
			free(info()->export[i--]);
			while (info()->export[++i + 1] != NULL)
				info()->export[i] = info()->export[i + 1];
			info()->export[i--] = NULL;
		}
	}
}
