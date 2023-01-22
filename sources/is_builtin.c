 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:34:51 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/19 18:38:59 by etachott         ###   ########.fr       */
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

int	is_builtin(char **prompt)
{
	if (ft_strncmp(prompt[0], "cd", 2) == 0)
		return (1);
	if (ft_strncmp(prompt[0], "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(prompt[0], "echo", 4) == 0)
		return (1);
	if (ft_strncmp(prompt[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(prompt[0], "exit", 4) == 0)
		return (1);
	if (ft_strncmp(prompt[0], "export", 6) == 0)
		return (1);
	if (ft_strncmp(prompt[0], "unset", 5) == 0)
		return (1);
	return (0);
}

int	builtin_run(char **prompt, char **envp)
{
	int	exitcode;

	exitcode = 1;
	if (ft_strncmp(prompt[0], "cd", 2) == 0)
		exitcode = cd(envp, prompt[1]);
	else if (ft_strncmp(prompt[0], "pwd", 3) == 0)
		exitcode = pwd();
	else if (ft_strncmp(prompt[0], "echo", 4) == 0)
		echo(prompt);
	else if (ft_strncmp(prompt[0], "env", 4) == 0)
		exitcode = builtin_env();
	else if (ft_strncmp(prompt[0], "exit", 4) == 0)
		builtin_exit(prompt);
	else if (ft_strncmp(prompt[0], "export", 6) == 0)
		exitcode = builtin_export(prompt[1]);
	else if (ft_strncmp(prompt[0], "unset", 5) == 0)
		exitcode = builtin_unset(prompt[1]);
	else
		return (1);
	return (exitcode);
}
