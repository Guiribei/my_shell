/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:14:58 by guribeir          #+#    #+#             */
/*   Updated: 2023/02/13 17:33:50 by guribeir         ###   ########.fr       */
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
