/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkist-si <vkist-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:48:47 by tkomeno           #+#    #+#             */
/*   Updated: 2022/12/19 02:08:02 by vkist-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	ft_matrixfree(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

static int	fits_in_long_long(char *str)
{
	long long	out;
	int			c;
	
	if (ft_strlen(str) > 20)
		return (0);
	if (ft_strncmp(str, "-9223372036854775808", 21) == 0)
		return (1);
	out = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		c = *str - '0';
		 if (out > (LLONG_MAX - c) / 10)
			return (0);
		out = out * 10 + c;
		str++;
	}
	return (1);
}

void	check_exit(char **args)
{
	if (args[2])
	{
		ft_matrixfree(args);
		exit_with_error("exit", "too many arguments", EXIT_FAILURE);
	}
	else if (!fits_in_long_long(args[1]))
	{
		ft_matrixfree(args);
		exit_with_error("exit", "numeric argument required", 2);	
	}
	else
	{
		rl_clear_history();
	//	ft_matrixfree(args);
		break_free(&g_data);
		//close_all_fds();
		g_data.exit_status = ft_atoi_long(args[1]);
		exit(g_data.exit_status);
	}
}

void	builtin_exit(char **args)
{
	write (STDERR_FILENO, "exit\n", 5);
	if (args[0] && !args[1])
	{
		break_free(&g_data);
	//	close_all_fds();
	//	ft_matrixfree(args);
		exit(EXIT_SUCCESS);
	}
	else
		check_exit(args);
}
