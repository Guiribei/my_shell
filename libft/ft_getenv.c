/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 08:15:25 by vcastilh          #+#    #+#             */
/*   Updated: 2023/02/13 13:13:17 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char *name, char **envp)
{
	int	i;
	int	j;

	if ((name == NULL) | (envp == NULL))
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!ft_strncmp(name, envp[i], ft_strlen(name)))
		{
			j = i + ft_strlen(name) + 1;
			return (&(envp[i][j]));
		}
		else
			i++;
	}
	return (NULL);
}
