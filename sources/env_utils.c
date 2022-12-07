/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:29:35 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/07 19:44:35 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envfree(t_list **env)
{
	t_list	*prev_node;
	int		index = 0;

	prev_node = *env;
	if (!*env || !env)
		return ;
	while (*env && prev_node)
	{
		*env = (*env)->next;
		free(prev_node->key);
		free(prev_node->value);
		free(prev_node);
		prev_node = *env;
		index++;
	}
	*env = NULL;
}

t_list	*change_env(t_list *env, char *key, char *value)
{
	t_list	*tmp;
	int		len;

	len = ft_strlen(key);
	tmp = env;
	if (!key || !value)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, len) == 0)
		{
			free(tmp->value);
			tmp->value = NULL;
			tmp->value = ft_strdup(value);
		}
		tmp = tmp->next;
	}
	return (env);
}
