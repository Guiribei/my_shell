/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:25:43 by coder             #+#    #+#             */
/*   Updated: 2022/12/15 15:19:35 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	builtin_env(char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		ft_putendl_fd(envp[index], 1);
		index++;
	}
	return (0);
}

int	builtin_export(t_list *env, char *name)
{
	t_list	*tmp;

	tmp = env;
	tmp = ft_lstlast(tmp);
	ft_lstadd_back(&tmp, ft_lstenv_new(name));
	return (0);
}