#include "../../minishell.h"

static t_exp	**copy_export(int *limit)
{
	int		i;
	t_exp	**cpy;

	*limit = 0;
	while (info()->export[*limit] != NULL)
		(*limit)++;
	cpy = malloc((*limit + 1) * sizeof(t_exp *));
	i = -1;
	while (++i <= *limit)
		cpy[i] = info()->export[i];
	return (cpy);
}

static t_exp	**sorted_export(void)
{
	t_exp	**sorted;
	t_exp	*tmp;
	int		limit;
	int		i;

	sorted = copy_export(&limit);
	while (--limit > 0)
	{
		i = -1;
		while (++i < limit)
		{
			if (ft_strncmp(sorted[i]->name, sorted[i + 1]->name, \
				ft_strlen(sorted[i]->name) + 1) > 0)
			{
				tmp = sorted[i];
				sorted[i] = sorted[i + 1];
				sorted[i + 1] = tmp;
			}
		}
	}
	return (sorted);
}

void	show_export(void)
{
	int		i;
	t_exp	**sorted;

	sorted = sorted_export();
	i = -1;
	while (sorted[++i] != NULL)
	{
		printf("declare -x %s", sorted[i]->name);
		if (sorted[i]->content != NULL)
			printf("=\"%s\"", sorted[i]->content);
		printf("\n");
	}
	free(sorted);
}
