/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:20:44 by guribeir          #+#    #+#             */
/*   Updated: 2022/10/05 16:37:06 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (ft_strncmp(str[i], "-n", 2) == 0)
	{
		i++;
		flag = -1;
	}
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
}
