/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:35:53 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/15 15:22:13 by etachott         ###   ########.fr       */
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

char	*find_command(char *command, char **paths)
{
	int		i;
	char	*tmp;
	char	*path;

	path = NULL;
	if (access(command, F_OK | X_OK) == 0)
	{
		tmp = ft_strdup(command);
		return (tmp);
	}
	i = -1;
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
	return (NULL);
}
