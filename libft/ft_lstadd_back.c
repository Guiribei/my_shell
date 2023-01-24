/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 19:31:50 by coder             #+#    #+#             */
/*   Updated: 2023/01/24 16:28:12 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*last_node;

	if (lst && new_node)
	{
		if (*lst)
		{
			last_node = ft_lstlast(*lst);
			last_node->next = new_node;
		}
		else
			*lst = new_node;
	}
}
