/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:29:35 by guribeir          #+#    #+#             */
/*   Updated: 2022/10/21 20:32:23 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*change_env(t_list *env, char *key, char *value)
{
	t_list	*tmp;
	int		len;

	len = ft_strlen(key);
	tmp = env;
	if (!key || !value)
		return (NULL);
	while(tmp)
	{
		if (ft_strncmp(key, tmp->key, len) == 0)
			{
				free(tmp->value);
				tmp->value = NULL;
				tmp->value = ft_strdup(value);
			}
		tmp = tmp->next;
	}
	return(env);
}
