/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:16:49 by coder             #+#    #+#             */
/*   Updated: 2023/01/20 18:45:21 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <errno.h> //checkar
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define LLONG_MAX 9223372036854775807
# define STD_IN 0
# define STD_OUT 1
# define FILE_IN 2
# define FILE_OUT 3
# define PIPE_0 4
# define PIPE_1 5

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef struct s_cmd
{
	char	*cmd;
	char	**cmds;
	int		fd_in;
	int		fd_out;
	char	*path_cmd;
	int		pid;
	int		where_read;
	int		where_write;
	int		pipe[2];
}			t_cmd;

typedef struct s_token
{
	char	*name;
	int		size;
}			t_token;

typedef struct sigaction	t_sigaction;

typedef struct s_data
{
	char	*cmd;
	char	*cwd;
	char	**envp;
	char	**prompt;
	char	*prompt_name;
	char	*str;
	int		exit_status;
	int		std_in_fd;
	int		std_out_fd;
	t_cmd	*cmds;
	t_token	*tokens;
}			t_data;

void		echo(char **str);
int			builtin_run(char **prompt, char **envp);
void		strclear(char **str);
void		strsclear(char **ptrs);
int			pwd(void);
char		*set_prompt(const char *name);
void		set_signals(struct sigaction *act, struct sigaction *act_2);
char		**set_env(char *envp[]);
int			builtin_env(void);
int			builtin_export(char *name);
int			builtin_unset(char *key);
int			count_iterations(t_cmd *cmds);
int			executor(char **prompt, char **envp);
char		**get_paths(char **envp);
char		*find_command(char *command, char **paths);
char		**recreate_envp(t_list *env_lst);
char		*join_three(char *s1, char *s2, char *s3);
void		ft_envfree(t_list **env);
int			cd(char **envp, char *folder);
char		*read_env(char **env, char *key);
char		**change_env(char **envp, char *key, char *value);
t_bool		is(const char *s, int c);
int			is_builtin(char **prompt);
int			is_token(char c);
void		builtin_exit(char **args);
void		init_global(t_data *d);
void		break_free(t_data *data);
void		half_break_free(t_data *data);
void		skip_space(int *i);
void		skip_double_quotes(char *line, int *i, int *tokens);
void		skip_single_quotes(char *line, int *i, int *tokens);
void		skip_pipe(int *i, int *tokens);
void		count_as_token(char *line, int *i, int *tokens);
int			ft_isspace(char c);
int			count_tokens(char *line);
t_token		*allocate_tokens(char *line);
t_token		*allocate_tokens_content(char *line, t_token *tokens,
			int curr_token,int curr_token_size);
t_token		*fill_tokens_content(char *line, t_token *tokens);
t_token		*tokenize(char *line);
void		exit_with_error(char *cmd, char *msg, int error);
long long	ft_atoi_long(char *str);
int			is_expansible(char *str);
char		*expand_str(char *str);
void		skip_gt(int *i, int *tokens, char *line);
void		skip_lt(int *i, int *tokens, char *line);
void		allocate_double(int *curr_token, int *curr_token_size, char *line,
			int *i);
void		allocate_single(int *curr_token, int *curr_token_size, char *line,
			int *i);
void		allocate_greater(int *curr_token, int *curr_token_size, char *line,
			int *i);
void		allocate_less(int *curr_token, int *curr_token_size,
			char *line, int *i);
void		allocate_pipe(int *curr_token, int *curr_token_size, int *i);
void		skip_double_quotes(char *line, int *i, int *tokens);
void		skip_single_quotes(char *line, int *i, int *tokens);
void		print_cmd(t_cmd *cmd);
void		skip_pipe(int *i, int *tokens);
void		skip_gt(int *i, int *tokens, char *line);
void		skip_lt(int *i, int *tokens, char *line);
void		fill_double(int *i, char *line, int *curr_token, t_token **tokens);
void		fill_single(int *i, char *line, int *curr_token, t_token **tokens);
void		fill_pipe(t_token **tokens, int *curr_token, char *line, int *i);
void		fill_greater(t_token **tokens, int *curr_token, int *i, char *line);
void		fill_less(t_token **tokens, int *curr_token, int *i, char *line);
void		full_close(t_cmd *cmd);
void		check_syntax(t_token *tokens);
t_cmd		*init_cmd_table(t_token *tokens);
t_bool		cmp(char *s1, char *s2);
void		safe_init(t_cmd *cmds, int size);
void		split_cmds(t_cmd *cmds);
int			core(t_cmd *cmds, char **envp);

#endif