/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:34:32 by etachott          #+#    #+#             */
/*   Updated: 2023/01/24 16:28:32 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*ptr;

	if (!n)
		return (NULL);
	ptr = ft_calloc((n + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	return (ft_memcpy(ptr, s, n));
}
