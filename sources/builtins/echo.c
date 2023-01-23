/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:20:44 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/21 13:44:58 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	counter(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	echo(char **str)
{
	int	i;
	int	flag;
	int	limit;

	i = 1;
	flag = 0;
	limit = 0;
	if (!str[1])
	{
		ft_putendl_fd("", 1);
		return ;
	}
	if (ft_strncmp(str[i], "-n", 2) == 0)
	{
		i++;
		flag = -1;
	}
	limit = counter(str);
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (i < limit - 1)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
}
