/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:54:20 by etachott          #+#    #+#             */
/*   Updated: 2022/12/14 20:03:46 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	matrix_size(char **matrix)
{
	int	index;

	index = 0;
	while (matrix[index])
		index++;
	return (index);
}

void	ft_matrixcpy(char **dst, char **src)
{
	int	index;
	int	m_size;

	index = 0;
	m_size = matrix_size(src);
	if (dst || !src)
		return ;
	dst = ft_calloc(sizeof(char *), m_size + 1);
	dst[m_size] = NULL;
	while (src[index])
	{
		dst[index] = ft_strdup(src[index]);
		index++;
	}
}
