/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:46:45 by etachott          #+#    #+#             */
/*   Updated: 2022/12/07 17:48:48 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_three(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(s1, s2);
	tmp2 = ft_strjoin(tmp, s3);
	free(tmp);
	return (tmp2);
}
