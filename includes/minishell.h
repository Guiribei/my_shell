/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:16:49 by coder             #+#    #+#             */
/*   Updated: 2022/12/13 22:27:09 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <errno.h> //checkar

typedef enum e_bool
{
	FALSE,
	TRUE
} t_bool;

void	echo(char **str);
void	strclear(char **str);
void	strsclear(char **ptrs);
int		pwd(void);
char	*set_prompt(const char *name);
void	set_signals(struct sigaction *act, struct sigaction *act_2);
t_list	*set_env(char *envp[]);
int		builtin_env(t_list *env);
int		builtin_export(t_list *env, char *name);
t_list	*change_env(t_list *env, char *key, char *value);
int		executor(char **prompt, t_list *env, char **envp);
char	**get_paths(t_list *env);
char	*find_command(char *command, char **paths);
char	**recreate_envp(t_list *env_lst);
char	*join_three(char *s1, char *s2, char *s3);
void	ft_envfree(t_list **env);
int		builtin_cd(t_list *env, char *folder);
char	*read_env(t_list *env, char *key);
t_bool	is(const char *s, int c);

#endif
