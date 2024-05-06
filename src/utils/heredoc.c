#include "../../minishell.h"

static void	ctrl_c_heredoc_handler(int signo)
{
	(void)signo;
	printf("\n");
	if (info()->hd_info.eof != NULL)
		free(info()->hd_info.eof);
	close(info()->hd_info.fd);
	exit(cleanup(130));
}

static void	handle_heredoc_helper(int *stdio_cpy, int fd_tmp, char *eof)
{
	char	*buf;
	bool	parse;

	parse = !(ft_strchr(eof, '"') || ft_strchr(eof, '\''));
	(info())->hd_info.eof = parse_input(ft_strdup(eof), 1);
	dup2(stdio_cpy[0], STDIN_FILENO);
	dup2(stdio_cpy[1], STDOUT_FILENO);
	buf = readline("> ");
	while (true)
	{
		if (buf == NULL)
			ft_putendl_fd("minishell: warning: here-doc delimited by eof", 2);
		if (buf == NULL || ft_strncmp(buf, info()->hd_info.eof, \
			ft_strlen(info()->hd_info.eof) + 1) == 0)
			break ;
		if (parse)
			buf = parse_env(buf);
		ft_putendl_fd(buf, fd_tmp);
		free(buf);
		buf = readline("> ");
	}
	free(info()->hd_info.eof);
	info()->hd_info.eof = NULL;
	close(fd_tmp);
	exit(cleanup(0));
}

static int	handle_heredoc(char *eof, int *stdio_cpy, int cur_cmd, int cur_tkn)
{
	int		i;
	int		status;
	char	*filename;

	(void)cur_tkn;
	filename = append(ft_strdup(TMP_FN), ft_itoa(cur_cmd), 1);
	(info())->hd_info.fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, PERMS);
	free(filename);
	if (info()->hd_info.fd < 0)
		exit(cleanup(1));
	i = fork();
	if (i == 0)
	{
		signal(SIGINT, ctrl_c_heredoc_handler);
		handle_heredoc_helper(stdio_cpy, info()->hd_info.fd, eof);
	}
	info()->paused = true;
	waitpid(i, &status, 0);
	info()->paused = false;
	close(info()->hd_info.fd);
	return (WEXITSTATUS(status));
}

static int	preload_heredocs_helper(int i, int j, int err)
{
	int		ret;

	ret = 0;
	if (err != 0)
		ret = err;
	else if (info()->commands[i][j + 1] == NULL
		|| ft_strncmp(info()->commands[i][j + 1], "<", 1) == 0
		|| ft_strncmp(info()->commands[i][j + 1], ">", 1) == 0)
		ret = 1;
	else if (!rdr_qts(info()->cmplt_inp, info()->cur_redir)
		&& !ft_strncmp(info()->commands[i][j], "<<", 3))
		ret = handle_heredoc(info()->commands[i][j + 1], info()->old_std, i, j);
	return (ret);
}

int	preload_heredocs(int num_commands)
{
	int		i;
	int		j;
	int		err;

	err = 0;
	i = -1;
	while (++i < num_commands)
	{
		if (err != 130)
			err = 0;
		j = -1;
		while (info()->commands[i][++j])
		{
			if ((ft_strncmp(info()->commands[i][j], "<", 1) == 0
				|| ft_strncmp(info()->commands[i][j], ">", 1) == 0)
				&& ft_strncmp(info()->commands[i][j], "<<<", 3) != 0
				&& ft_strncmp(info()->commands[i][j], ">>>", 3) != 0)
				err = preload_heredocs_helper(i, j, err);
			info()->cur_redir += count_redirects(info()->commands[i][j]);
		}
	}
	info()->cur_redir = 0;
	return (err);
}
