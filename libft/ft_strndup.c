/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott <etachott@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:34:32 by etachott          #+#    #+#             */
/*   Updated: 2022/12/21 12:31:47 by etachott         ###   ########.fr       */
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
//	ptr[n] = '\0';
	return (ft_memcpy(ptr, s, n));
}
