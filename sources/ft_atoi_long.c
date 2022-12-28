/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkist-si <vkist-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:29:06 by ridalgo-          #+#    #+#             */
/*   Updated: 2022/12/28 15:39:56 by vkist-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoi_long(char *str)
{
	long long	nbr;
	int			sign;

	nbr = 0;
	sign = 1;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if ((*str == 45) || (*str == 43))
	{
		if (*str == 45)
			sign = -1;	
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		if (nbr > (LLONG_MAX - (*str - 48)) / 10)
			exit_with_error("exit", "numeric argument required", 2);
		nbr = (nbr * 10) + (*str - 48);
		str++;
	}
	return (nbr * sign);
}
