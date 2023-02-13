/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 08:39:49 by vcastilh          #+#    #+#             */
/*   Updated: 2023/02/13 13:17:00 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	sub_len;

	i = 0;
	if (start > ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	sub_len = ft_strlen(&s[start]);
	if (len > sub_len)
		len = sub_len;
	sub = ft_calloc((len + 1), sizeof(char));
	if (! sub)
		return (NULL);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
