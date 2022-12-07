/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recreate_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:36:34 by etachott          #+#    #+#             */
/*   Updated: 2022/12/07 19:06:43 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**recreate_envp(t_list *env_lst)
{
	char	**envp;
	char	*current_line;
	t_list	*trav;
	int		i;

	envp = ft_calloc(ft_lstsize(env_lst) + 1, sizeof(char *));
	i = 0;
	trav = env_lst;
	while (trav)
	{
		current_line = join_three(trav->key, "=", trav->value);
		envp[i] = current_line;
		trav = trav->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
