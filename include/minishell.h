/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:16:49 by coder             #+#    #+#             */
/*   Updated: 2022/11/30 16:13:44 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "../libs/libft/libft.h"
#include <stdarg.h>
#include <sys/wait.h>

int		echo(char **str);
void	strclear(char **str);
void	strsclear(char **ptrs);
int		pwd(void);
char	*set_prompt(const char *name);
void	set_signals(struct sigaction *act, struct sigaction *act_2);
t_list	*set_env(char *envp[]);
int		builtin_env(t_list *env);
int		builtin_export(t_list *env, char *name);
t_list	*change_env(t_list *env, char *key, char *value);
int		executor(char **prompt, t_list *env);
char	**get_paths(t_list *env);
char	*find_command(char *command, char **paths);
#endif
