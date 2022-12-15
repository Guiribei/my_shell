/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:25:43 by coder             #+#    #+#             */
/*   Updated: 2022/12/15 16:53:53 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

char	**set_env(char *envp[])
{
	int		index;
	char	**new_envp;

	index = 0;
	new_envp = NULL;
	while (envp[index])
		index++;
	new_envp = ft_calloc(sizeof(char *), index + 1);
	new_envp[index] = NULL;
	index = 0;
	while (envp[index])
	{
		new_envp[index] = ft_strdup(envp[index]);
		index++;
	}
	return (new_envp);
}

int	builtin_env(void)
{
	int	index;

	index = 0;
	while (g_data.envp[index])
	{
		ft_putendl_fd(g_data.envp[index], 1);
		index++;
	}
	return (0);
}

int	builtin_export(char *name)
{
	char	**temp;
	int		size;
	int		index;

	if (!name)
		return (0);
	index = 0;
	size = ft_matrix_size(g_data.envp);
	temp = ft_calloc(sizeof(char *), size + 2);
	temp[size + 1] = NULL;
	while (g_data.envp[index])
	{
		temp[index] = ft_strdup(g_data.envp[index]);
		index++;
	}
	temp[index] = ft_strdup(name);
	strsclear(g_data.envp);
	g_data.envp = temp;
	return (0);
}
