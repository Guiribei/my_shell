/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:16:49 by coder             #+#    #+#             */
/*   Updated: 2022/12/15 20:12:06 by tkomeno          ###   ########.fr       */
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

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef struct s_data
{
	int		exit_status;
	char	**prompt;
	char	**envp;
	char	*prompt_name;
	char	*cwd;
	char	*str;
	char	*cmd;
}			t_data;

typedef struct s_token
{
	char	*name;
	int		size;
}			t_token;

void		echo(char **str);
void		strclear(char **str);
void		strsclear(char **ptrs);
int			pwd(void);
char		*set_prompt(const char *name);
void		set_signals(struct sigaction *act, struct sigaction *act_2);
char		**set_env(char *envp[]);
int			builtin_env(void);
int			builtin_export(char *name);
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
int			builtin_exit(char **args);
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
t_token		*allocate_tokens_content(char *line, t_token *tokens);
t_token		*fill_tokens_content(char *line, t_token *tokens);
t_token		*tokenize(char *line);

#endif
