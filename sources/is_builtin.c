/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:34:51 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/19 18:22:25 by guribeir         ###   ########.fr       */
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

int	is_builtin(char **prompt, char **envp)
{
	if (ft_strncmp(prompt[0], "cd", 2) == 0)
		cd(envp, prompt[1]);
	else if (ft_strncmp(prompt[0], "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(prompt[0], "echo", 4) == 0)
		echo(prompt);
	else if (ft_strncmp(prompt[0], "env", 4) == 0)
		builtin_env();
	else if (ft_strncmp(prompt[0], "exit", 4) == 0)
		builtin_exit(prompt);
	else if (ft_strncmp(prompt[0], "export", 6) == 0)
		builtin_export(prompt[1]);
	else if (ft_strncmp(prompt[0], "unset", 5) == 0)
		builtin_unset(prompt[1]);
	else
		return (1);
	return (0);
}
