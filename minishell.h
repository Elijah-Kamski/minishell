#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "libft/libft.h"

# define ERR_UNXPC_TOK "minishell: syntax error near unexpected token"
# define TMP_FN "/tmp/minishell-here-document_"
# define MAX_TOKENS 64
# define MAX_CMDS 32
# define PERMS 0666

typedef struct s_export
{
	char	*name;
	char	*content;
}	t_exp;

typedef struct s_heredoc_info
{
	int		fd;
	char	*eof;
}	t_hdi;

typedef struct s_code_struct
{
	char	*oldpwd;
	char	*curpwd;
	bool	paused;
	int		cur_redir;
	int		*redirect_quotes;
	int		*old_std;
	int		**pipes;
	char	*cmplt_inp;
	t_exp	**export;
	char	***commands;
	pid_t	*pid_array;
	int		nb;
	t_hdi	hd_info;
}	t_code;

// built-in
int		cd(char *input);
void	echo(char **tokens);
char	**get_environ(void);
void	env(void);
void	show_export(void);
void	pwd(void);
void	unset_env(const char *name);

// utils
int		count_pipes(char *str);
long	cleanup(long exit_code);
char	*parse_env(char *input);
char	**pipe_split(char *str);
char	***get_cmds(char *input);
void	ctrl_c_handler(int signo);
char	*parse_input(char *input, int flag);
int		get_status(int new_status);
int		are_quotes_even(char *str);
void	env_builtins(char **tokens);
void	exit_minishell(char **tokens, int inside_pipes);
int		is_redirect_at_the_end(char *str);
int		preload_heredocs(int num_commands);
int		detect_consecutive_pipes(char *str);
char	*ft_strtok(char *input, char delim);
int		rdr_qts(char *str, int redirect_idx);
void	tkn_to_str(char **tokens, int start);
char	*getenv_from_array(const char *name);
void	get_cmd_tokens(char *str, char **cmd);
int		has_only_one_command(char ***commands);
char	*append(char *s1, char *s2, int free_s2);
void	remove_fr_arr(char **arr, int index, int amount);
int		pipes_outside_quotes(int *pipe_quotes_array, int pc);
void	tokenize_path(char *input, char *tokens[MAX_TOKENS], int *num_tokens);
void	build_pipe_quotes_array(char *str, \
			int **pipe_quotes_array, int pipe_count);
char	*pipe_strchr(const char *s, \
			int *pipe_quotes_array, int *pipe_curr_idx);
int		count_redirects(char *str);

// main
t_code	*info(void);
int		main(int argc, char **argv, char **envp);
void	main_loop(void);
void	command_handler(char **tokens);
void	one_command_handler(char **tokens);
void	execute_pipeline(int num_commands);
int		get_inputs(char **tokens);

#endif
