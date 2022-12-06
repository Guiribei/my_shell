/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:37:30 by guribeir          #+#    #+#             */
/*   Updated: 2022/10/05 17:37:45 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strclear(char **str)
{
	if (!str)
		return ;
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

void	strsclear(char **ptrs)
{
	int	i;

	if (ptrs != NULL)
	{
		i = 0;
		while (ptrs[i])
		{
			if (ptrs[i] != NULL)
				free(ptrs[i]);
			i++;
		}
		free(ptrs);
		ptrs = NULL;
	}
}
