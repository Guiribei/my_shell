/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:25:43 by coder             #+#    #+#             */
/*   Updated: 2022/10/21 20:23:21 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*set_env(char *envp[])
{
	int		i;
	t_list	*env;
	
	i = 0;
	env = ft_lstenv_new(envp[i++]);
	while (envp[i] != NULL)
		ft_lstadd_back(&env, ft_lstenv_new(envp[i++]));
	return (env);
}

int	builtin_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(tmp->value, 1);
		tmp = tmp->next;
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
