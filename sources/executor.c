/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:34:51 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/12 21:03:03 by etachott         ###   ########.fr       */
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
	if (!prompt[0])
		return (1);
	return (0);
}

int	executor(char **prompt, t_list *env, char **envp)
{
	int		pid;
	int		status;
	char	**paths;
	char	*cmd;

	if (prompt == NULL)
		return (0);
	if (is_builtin(prompt) == 0)
	{
		paths = get_paths(env);
		cmd = find_command(prompt[0], paths);
		strsclear(paths);
		if (!cmd)
		{
			error_handler(prompt[0], "command not found");
			return (127);
		}
		pid = fork();
		if (pid == 0 && envp != NULL)
		{
			execve(cmd, &prompt[0], envp);
			printf("Entrou no if\n");
		}
		else
		{
			waitpid(pid, &status, 0);
			printf("Entrou no else\n");
		}
		free(cmd);
	}
	return (0);
}
