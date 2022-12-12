/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:35:53 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/12 20:07:31 by etachott         ###   ########.fr       */
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

char	**get_paths(t_list *env)
{
	char	*path;
	char	**paths;

	paths = NULL;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
			path = env->value;
		env = env->next;
	}
	paths = ft_split(path, ':');
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
		return (command);
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
