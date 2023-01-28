/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:20:44 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/24 17:03:27 by guribeir         ###   ########.fr       */
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

void	put_str_increment(char **str, int *i)
{
	int	limit;

	limit = counter(str);
	ft_putstr_fd(str[*i], 1);
	if ((*i) < limit - 1)
		ft_putchar_fd(' ', 1);
	(*i)++;
}

void	echo(char **str)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!str[1])
	{
		ft_putendl_fd("", 1);
		return ;
	}
	if (ft_strncmp(str[i], "-n", 3) == 0)
	{
		i++;
		flag = -1;
	}
	while (str[i])
		put_str_increment(str, &i);
	if (flag == 0)
		ft_putchar_fd('\n', 1);
}
