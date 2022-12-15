/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:54:20 by etachott          #+#    #+#             */
/*   Updated: 2022/12/14 20:20:14 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_matrix_size(char **matrix)
{
	int	index;

	index = 0;
	while (matrix[index])
		index++;
	return (index);
}

char	**ft_matrixcpy(char **src)
{
	int		index;
	int		m_size;
	char	**dst;

	index = 0;
	m_size = ft_matrix_size(src);
	if (!src)
		return (NULL);
	dst = ft_calloc(sizeof(char *), m_size + 1);
	dst[m_size] = NULL;
	while (src[index])
	{
		dst[index] = ft_strdup(src[index]);
		index++;
	}
	return (dst);
}
