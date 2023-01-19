/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:23:50 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/20 00:39:02 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is(const char *s, int c)
{
	size_t	s_len;
	char	*ptr;

	ptr = (char *)s;
	s_len = ft_strlen(ptr) + 1;
	while (s_len--)
	{
		if (*ptr == (unsigned char)c)
			return (TRUE);
		ptr++;
	}
	return (FALSE);
}

int	count_iterations(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].cmd)
		i++;
	return (i);
}
