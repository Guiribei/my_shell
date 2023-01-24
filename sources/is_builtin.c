/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:34:51 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/24 16:24:58 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(char *cmd, char *error)
{
	write(1, "minishell: ", 11);
	ft_putstr_fd(cmd, 1);
	write(1, ": ", 2);
	ft_putstr_fd(error, 1);
	write(1, "\n", 1);
}

int	is_builtin_fork(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	return (0);
}

int	is_builtin_unfork(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

int	builtin_run_fork(char **prompt)
{
	int	exitcode;

	exitcode = 1;
	if (ft_strncmp(prompt[0], "pwd", 4) == 0)
		exitcode = pwd();
	else if (ft_strncmp(prompt[0], "echo", 5) == 0)
		echo(prompt);
	else if (ft_strncmp(prompt[0], "env", 4) == 0)
		exitcode = builtin_env();
	else
		return (1);
	return (exitcode);
}

int	builtin_run_unfork(char **prompt, char **envp)
{
	int	exitcode;

	exitcode = 1;
	if (ft_strncmp(prompt[0], "cd", 3) == 0)
		exitcode = cd(envp, prompt[1]);
	else if (ft_strncmp(prompt[0], "exit", 5) == 0)
		builtin_exit(prompt);
	else if (ft_strncmp(prompt[0], "export", 7) == 0)
		exitcode = builtin_export(prompt);
	else if (ft_strncmp(prompt[0], "unset", 6) == 0)
		exitcode = builtin_unset(prompt);
	else
		return (1);
	return (exitcode);
}
