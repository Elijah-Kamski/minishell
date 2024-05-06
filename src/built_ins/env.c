#include "../../minishell.h"

char	*getenv_from_array(const char *name)
{
	size_t	name_len;
	int		i;

	if (name == NULL || info()->export == NULL)
		return (NULL);
	if (name[0] == '"' || name[0] == '\'')
		return (ft_substr(name, 1, ft_strlen(name) - 1));
	if (ft_strncmp(name, "?", 1) == 0)
		return (append(ft_itoa(get_status(-1)), \
			ft_substr(name, 1, ft_strlen(name) - 1), true));
	name_len = ft_strlen(name);
	i = 0;
	while (info()->export[i] != NULL)
	{
		if (ft_strncmp(info()->export[i]->name, name, name_len + 1) == 0)
		{
			if (info()->export[i]->content != NULL)
				return (ft_strdup(info()->export[i]->content));
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

char	**get_environ(void)
{
	int		i;
	int		j;
	char	**environ;

	i = 0;
	j = 0;
	while (info()->export[i] != NULL)
	{
		if (info()->export[i]->content != NULL)
			j++;
		i++;
	}
	environ = malloc((j + 1) * sizeof(char *));
	environ[j] = NULL;
	while (--i >= 0 && j >= 0)
	{
		if (info()->export[i]->content != NULL)
		{
			environ[--j] = append(append(ft_strdup(info()->export[i]->\
				name), "=", 0), info()->export[i]->content, 0);
		}
	}
	return (environ);
}

void	env(void)
{
	int		i;
	char	**environ;

	environ = get_environ();
	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		free(environ[i++]);
	}
	free(environ);
}
