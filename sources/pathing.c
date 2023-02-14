/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:35:53 by guribeir          #+#    #+#             */
/*   Updated: 2023/02/13 20:44:26 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	append_slash_to_path(char **paths)
{
	int		i;
	char	*tmp;

	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = tmp;
	}
}

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

int	exit_error_no_path(char **paths, char *command)
{
	if (!paths)
	{
		if (!is_fork_builtin(command))
		{
			printf("minishell: %s: No such file or directory\n", command);
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

	if (exit_error_no_path(paths, command))
		return (NULL);
	path = NULL;
	if (access(command, F_OK | X_OK) == 0)
		return (ft_strdup(command));
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
	if (ft_strncmp(command, "./", 2) == 0)
		printf("minishell: %s: No such file or directory\n", command);
	else
		printf("minishell: %s: command not found\n", command);
	return (NULL);
}
