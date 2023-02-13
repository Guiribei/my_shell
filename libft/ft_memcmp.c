/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 10:31:38 by vcastilh          #+#    #+#             */
/*   Updated: 2023/02/13 13:13:52 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (unsigned char *)b1;
	p2 = (unsigned char *)b2;
	if (len != 0)
	{	
		while (len--)
		{
			if (*p1 == *p2)
			{
				p1++;
				p2++;
			}
			else
				return (*p1 - *p2);
		}
	}
	return (0);
}
