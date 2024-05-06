#include "../minishell.h"

static int	redirect_output(char *filename, char *redir)
{
	int		fd;

	if (ft_strncmp(redir, ">", 2) == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, PERMS);
	else if (ft_strncmp(redir, ">>", 3) == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, PERMS);
	else
		return (-1);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

static int	get_input_helper_helper(char **tkn, int *i)
{
	int		fd;
	char	*fn;

	if ((!ft_strncmp(tkn[*i], "<", 2) && !access(tkn[*i + 1], R_OK))
		|| !ft_strncmp(tkn[*i], "<<", 3))
	{
		if (!ft_strncmp(tkn[*i], "<<", 3))
			fn = append(ft_strdup(TMP_FN), ft_itoa(info()->nb), 1);
		else
			fn = ft_strdup(tkn[*i + 1]);
		fd = open(fn, O_RDONLY);
		if (fd != -1 && !ft_strncmp(tkn[*i], "<<", 3))
			unlink(fn);
		free(fn);
		if (fd == -1)
			return (0);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (!ft_strncmp(tkn[*i], ">", 1) && (!access(tkn[*i + 1], \
		W_OK) || access(tkn[*i + 1], F_OK)))
		redirect_output(tkn[*i + 1], tkn[*i]);
	else
		return (-1);
	return (0);
}

static int	get_input_helper(char **tkn, int *i)
{
	DIR		*dir;

	if (tkn[*i + 1] != NULL && !rdr_qts(info()->cmplt_inp, info()->cur_redir))
	{
		dir = opendir(tkn[*i + 1]);
		if (dir != NULL)
		{
			closedir(dir);
			ft_putendl_fd("minishell: Redirect target is a directory", 2);
			return (-1);
		}
		free(dir);
		if (get_input_helper_helper(tkn, i) == -1)
		{
			ft_putstr_fd(tkn[*i + 1], STDERR_FILENO);
			if (errno == ENOENT)
				ft_putendl_fd(": File does not exist", STDERR_FILENO);
			else if (errno == EACCES)
				ft_putendl_fd(": minishell: Permission denied", STDERR_FILENO);
			return (-1);
		}
		remove_fr_arr(tkn, --(*i), 2);
	}
	return (0);
}

int	unexpected_token(void)
{
	ft_putendl_fd(ERR_UNXPC_TOK, 2);
	return (-1);
}

int	get_inputs(char **tkn)
{
	int		i;

	i = -1;
	while (tkn[++i] != NULL)
	{
		if (!ft_strncmp(tkn[i], "<<<", 3) || !ft_strncmp(tkn[i], ">>>", 3))
			return (unexpected_token());
		else if (!ft_strncmp(tkn[i], "<", 2) || !ft_strncmp(tkn[i], ">", 2)
			|| !ft_strncmp(tkn[i], "<<", 3)
			|| !ft_strncmp(tkn[i], ">>", 3))
		{
			if (!rdr_qts(info()->cmplt_inp, info()->cur_redir) && (!tkn[i + 1]
					|| ((!ft_strncmp(tkn[i + 1], "<", 1)
							|| !ft_strncmp(tkn[i + 1], ">", 1))
						&& !rdr_qts(info()->cmplt_inp, info()->cur_redir + 1))))
				return (unexpected_token());
			if (get_input_helper(tkn, &i) == -1)
				return (-1);
		}
		if (tkn != NULL && i >= 0 && tkn[i] != NULL)
			info()->cur_redir += count_redirects(tkn[i]);
	}
	return (0);
}
