#include "../../minishell.h"

char	*ft_strtok(char *input, char delim)
{
	int			i;
	static char	*str;
	char		*ret;
	char		*tmp;

	if (input != NULL)
	{
		if (str != NULL)
			free(str);
		str = ft_strdup(input);
	}
	if (str == NULL)
		return (NULL);
	if (delim == '\0')
		return (str);
	i = 0;
	while (str[i] != '\0' && str[i] != delim)
		i++;
	ret = ft_substr(str, 0, i);
	tmp = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	free(str);
	str = tmp;
	return (ret);
}

char	*append(char *s1, char *s2, int free_s2)
{
	char	*ret;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (s2);
	ret = ft_strjoin(s1, s2);
	free(s1);
	if (free_s2)
		free(s2);
	return (ret);
}

static char	*append_c(char *s, char c)
{
	char	*ret;
	char	*tmp;

	tmp = malloc(2 * sizeof(char));
	tmp[0] = c;
	tmp[1] = '\0';
	ret = ft_strjoin(s, tmp);
	free(s);
	free(tmp);
	return (ret);
}

char	*parse_input(char *input, int flag)
{
	int		i;
	char	*str;
	char	in;

	str = malloc(sizeof(char));
	str[0] = '\0';
	in = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '"' && (in == 0 || in == '"'))
			in = '"' - in;
		else if (input[i] == '\'' && (in == 0 || in == '\''))
			in = '\'' - in;
		else
		{
			if (!((flag == 1) && input[i] == '$'
					&& (input[i + 1] == '"' || input[i + 1] == '\'')))
				str = append_c(str, input[i]);
		}
		i++;
	}
	free(input);
	return (str);
}

int	are_quotes_even(char *str)
{
	int		i;
	int		single_open;
	int		double_open;

	single_open = -1;
	double_open = -1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && double_open == -1)
			single_open = -single_open;
		if (str[i] == '\"' && single_open == -1)
			double_open = -double_open;
		i++;
	}
	if (single_open != -1 || double_open != -1)
		return (0);
	return (1);
}
