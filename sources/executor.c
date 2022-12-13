/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:34:51 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/13 21:44:20 by guribeir         ###   ########.fr       */
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

int	is_builtin(char **prompt, t_list *env)
{
	if (ft_strncmp(prompt[0], "cd", 2) == 0)
		builtin_cd(env, prompt[1]);
	else if (ft_strncmp(prompt[0], "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(prompt[0], "echo", 4) == 0)
		echo(prompt);
	else if (ft_strncmp(prompt[0], "env", 4) == 0)
		builtin_env(env);
	else
		return(1);
	return (0);
}

int	executor(char **prompt, t_list *env, char **envp)
{
	int		pid;
	int		status;
	char	**paths;
	char	*cmd;

	if (prompt[0] == NULL)
		return (0);
	if (is_builtin(prompt, env) == 1)
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
			execve(cmd, &prompt[0], envp);
		else
			waitpid(pid, &status, 0);
		free(cmd);
	}
	return (0);
}
