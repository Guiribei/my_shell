/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:34:51 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/06 20:04:40 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	if (ft_strncmp(prompt[0], "cd", 3) == 0)
		return (1);
	return (0);
}

int	executor(char **prompt, t_list *env)
{
	int		pid;
	int		status;
	char	**paths;
	char	*cmd;
	if (prompt == NULL)
		return(0);
	if (is_builtin(prompt) == 0)
	{
		paths = get_paths(env);
		cmd = find_command(prompt[0], paths);
		if (!cmd)
		{
			error_handler(prompt[0], "command not found");
			return (127);
		}
		pid = fork();
		if (pid == 0 && env != NULL)
		{
			execve(cmd, &prompt[0], NULL);
		}
		else
		{
			waitpid(pid, &status, 0);	
		}
	}
	return(0);
}