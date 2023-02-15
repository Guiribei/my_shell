/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott <etachott@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:35:53 by guribeir          #+#    #+#             */
/*   Updated: 2023/02/15 16:05:07 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

char	**get_paths(char **envp)
{
	char	*path;
	char	**paths;
	int		index;

	index = 0;
	path = NULL;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH", 4) == 0)
			path = ft_strdup(envp[index]);
		index++;
	}
	if (!path)
		return (NULL);
	paths = ft_split(path + 5, ':');
	free(path);
	append_slash_to_path(paths);
	return (paths);
}

int	is_fork_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	return (0);
}

static void	error_handler_pathing(char *str1, char *str2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str2, 2);
}

int	exit_error_no_path(char **paths, char *command)
{
	if (!paths)
	{
		if (!is_fork_builtin(command))
		{
			error_handler_pathing(command, "No such file or directory");
			g_data.exit_status = 1;
		}
		return (1);
	}
	return (0);
}

char	*find_command(char *command, char **paths, int i)
{
	char	*path;
	char	*tmp;

	if (access(command, F_OK | X_OK) == 0)
		return (ft_strdup(command));
	if (exit_error_no_path(paths, command))
		return (NULL);
	path = NULL;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], command);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			path = tmp;
			return (path);
		}
		free(tmp);
	}
	if (ft_strncmp(command, "./", 2) == 0 || ft_strncmp(command, "/", 1) == 0)
		error_handler_pathing(command, "No such file or directory");
	else
		error_handler_pathing(command, "command not found");
	return (NULL);
}
