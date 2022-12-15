/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:34:51 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/15 14:59:41 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

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
		builtin_env(envp);
	else if (ft_strncmp(prompt[0], "exit", 4) == 0)
		builtin_exit(prompt);
	else
		return (1);
	return (0);
}

int	executor(char **prompt, char **envp)
{
	int		pid;
	int		status;
	char	**paths;
	char	*cmd;

	if (prompt[0] == NULL)
		return (0);
	if (is_builtin(prompt, envp) == 1)
	{
		paths = get_paths(envp);
		cmd = find_command(prompt[0], paths);
		strsclear(paths);
		if (!cmd)
		{
			error_handler(prompt[0], "command not found");
			return (127);
		}
		pid = fork();
		if (pid == 0 && envp != NULL)
			execve(cmd, &prompt[0], envp);
		else
			waitpid(pid, &status, 0);
		free(cmd);
	}
	return (0);
}
