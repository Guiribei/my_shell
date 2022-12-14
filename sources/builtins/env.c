/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:25:43 by coder             #+#    #+#             */
/*   Updated: 2022/12/14 18:43:46 by etachott         ###   ########.fr       */
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
	printf("INDEX = %d\n", index);
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

t_list	*st_env(char *envp[])
{
	int		i;
	t_list	*env;

	i = 0;
	env = ft_lstenv_new(envp[i++]);
	while (envp[i] != NULL)
		ft_lstadd_back(&env, ft_lstenv_new(envp[i++]));
	return (env);
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