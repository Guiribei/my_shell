/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:35:53 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/26 02:05:11 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH", 4) == 0)
			path = ft_strdup(envp[index]);
		index++;
	}
	paths = ft_split(path + 5, ':');
	free(path);
	append_slash_to_path(paths);
	return (paths);
}

char	*find_command(char *command, char **paths, int i)
{
	char	*tmp;
	char	*path;

	path = NULL;
	if (access(command, F_OK | X_OK) == 0)
	{
		tmp = ft_strdup(command);
		return (tmp);
	}
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
