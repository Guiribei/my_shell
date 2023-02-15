/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott <etachott@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:16:49 by coder             #+#    #+#             */
/*   Updated: 2023/02/15 16:13:37 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
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
# define HEREDOC "/tmp/heredoc"

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef enum e_where
{
	STD_IN,
	STD_OUT,
	FILE_IN,
	FILE_OUT,
	PIPE_0,
	PIPE_1
}			t_where;

typedef struct s_cmd
{
	char		*cmd;
	char		**cmds;
	int			is_heredoc;
	int			fd_in;
	int			fd_out;
	int			flag_quit;
	char		*path_cmd;
	int			pid;
	t_where		where_read;
	t_where		where_write;
	int			pipe[2];
}				t_cmd;

typedef struct s_token
{
	char	*name;
	int		size;
	int		is_sentinel;
}			t_token;

typedef struct s_string
{
	char	*final;
	char	*temp1;
	char	*temp2;
	char	*temp3;
}			t_string;

typedef struct sigaction	t_sigaction;

typedef struct s_data
{
	char	*cmd;
	char	*cwd;
	char	**envp;
	char	**fenvp;
	char	**prompt;
	char	*prompt_name;
	char	*str;
	int		index;
	int		exit_status;
	int		std_in_fd;
	int		std_out_fd;
	int		flag_quit;
	int		error_flag;
	int		i;
	int		j;
	int		skip;
	t_cmd	*cmds;
	t_token	*tokens;
}			t_data;

/*Initialization functions*/

void		init_global(t_data *d);
char		*set_prompt(const char *name);
void		set_execute_signals(int child_pid);
void		set_signals(struct sigaction *act, struct sigaction *act_2);

/*Builtins and it's aux functions*/

void		append_to_fake_envp(char *name);
void		append_to_envp(char *name, int i);
int			env_export_no_arg(void);
int			cd(char **envp, char **folder);
char		**change_exit_status(char **envp, int status);
int			echo(char **str);
int			builtin_env(void);
void		builtin_exit(char **args);
int			builtin_export(char **argv);
int			builtin_run_fork(char **prompt);
int			builtin_run_unfork(char **prompt, char **envp);
int			builtin_run(char **prompt, char **envp);
int			builtin_unset(char **argv);
int			is_builtin_fork(char **prompt);
int			is_builtin_unfork(char **prompt);
int			pwd(void);

/*Enviroment functions*/

char		**change_env(char **envp, char *key, char *value);
char		*expand_str(char *str);
void		expand_variables(char **input);
void		ft_envfree(t_list **env);
int			is_expansible(char *str);
char		*read_env(char **env, char *key);
char		**recreate_envp(t_list *env_lst);
char		**set_env(char *envp[]);

/*Memory and fd clearing functions*/

void		break_free(t_data *data);
void		close_fds(void);
int			count_rows(char **matrix);
void		exit_with_error(char *cmd, char *msg, int error);
int			error_syntax(char *token);
void		free_cmds(t_cmd *cmds);
void		free_tokens(t_token *tokens);
void		full_close(t_cmd *cmd);
void		half_break_free(t_data *data);
void		perror_handler(char *str1, char *str2, int status, t_cmd *cmds);
int			perror_handler_int(char *str1, char *str2, int status, t_cmd *cmds);
void		strclear(char **str);
void		strsclear(char **ptrs);

/*Parsing functions*/

void		allocate_double(int *curr_token, int *curr_token_size, char *line,
				int *i);
void		allocate_greater(int *curr_token, int *curr_token_size, char *line,
				int *i);
void		allocate_pipe(int *curr_token, int *curr_token_size, int *i);
void		allocate_single(int *curr_token, int *curr_token_size, char *line,
				int *i);
void		allocate_less(int *curr_token, int *curr_token_size,
				char *line, int *i);
t_token		*allocate_tokens(char *line);
t_token		*allocate_tokens_content(char *line, t_token *tokens,
				int curr_token, int curr_token_size);
void		count_as_token(char *line, int *i, int *tokens);
void		fill_double(int *i, char *line, int *curr_token, t_token **tokens);
void		fill_single(int *i, char *line, int *curr_token, t_token **tokens);
void		fill_pipe(t_token **tokens, int *curr_token, char *line, int *i);
void		fill_greater(t_token **tokens, int *curr_token, int *i, char *line);
void		fill_less(t_token **tokens, int *curr_token, int *i, char *line);
char		*fill_non_printable(void);
char		*fill_non_space(void);
t_token		*fill_tokens_content(char *line, t_token *tokens, int curr_token,
				int i);
int			greater_than_middle_syntax(t_token *tokens, int *i);
void		init_heredoc(t_cmd *cmds, t_token *tokens, int *i, int *j);
void		init_less_than(t_cmd *cmds, t_token *tokens, int *i, int *j);
void		init_greater_than(t_cmd *cmds, t_token *tokens, int *i, int *j);
void		init_normal(t_cmd *cmds, t_token *tokens, int *i, int *j);
void		init_pipe(t_cmd *cmds, int *j);
int			pipe_middle_syntax(t_token *tokens, int *i);
int			lesser_than_middle_syntax(t_token *tokens, int *i);
int			ft_isspace(char c);
int			count_tokens(char *line);
t_token		*tokenize(char *line);
long long	ft_atoi_long(char *str);
int			is_token(char c);
int			is_quote(char c);
t_bool		is(const char *s, int c);
void		print_cmd(t_cmd *cmd);
void		skip_gt(int *i, int *tokens, char *line);
void		skip_lt(int *i, int *tokens, char *line);
void		skip_double_quotes(char *line, int *i, int *tokens);
void		skip_single_quotes(char *line, int *i, int *tokens);
void		skip_space(int *i);
void		skip_double_quotes(char *line, int *i, int *tokens);
void		skip_single_quotes(char *line, int *i, int *tokens);
void		skip_pipe(int *i, int *tokens);
void		skip_pipe(int *i, int *tokens);
void		skip_gt(int *i, int *tokens, char *line);
void		skip_lt(int *i, int *tokens, char *line);

/*Execution functions*/

void		append_slash_to_path(char **paths);
int			append_syntax(t_token *tokens, int *i);
int			check_syntax(t_token *tokens, int i, int count);
t_bool		cmp(char *s1, char *s2);
int			core(t_cmd *cmds, char **envp, int exitcode, int i);
int			count_iterations(t_cmd *cmds);
int			executor(char **prompt, char **envp);
char		*find_command(char *command, char **paths, int i);
char		**get_paths(char **envp);
int			heredoc(t_cmd *cmds, char *delimiter);
int			heredoc_syntax(t_token *tokens, int *i);
t_cmd		*init_cmd_table(t_token *tokens);
char		*join_three(char *s1, char *s2, char *s3);
void		safe_init(t_cmd *cmds, int size);
void		select_inout(t_cmd *cmds, int i);
void		split_cmds(t_cmd *cmds);
void		open_input_file(t_cmd	*cmds, char *file);
void		open_output_file(t_cmd	*cmds, char *file);
void		open_append_file(t_cmd	*cmds, char *file);

#endif