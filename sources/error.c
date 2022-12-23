/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:30:53 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/23 22:30:55 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static void	print_error_msg(char *cmd, char *msg)
{
	write (STDERR_FILENO, "minishell: ", 11);
 	write (STDERR_FILENO, cmd, ft_strlen(cmd));
  	write (STDERR_FILENO, ": ", 2);
	write (STDERR_FILENO, msg, ft_strlen(msg));
  	write (STDERR_FILENO, "\n", 1);
}

void	exit_with_error(char *cmd, char *msg, int error)
{
	print_error_msg(cmd, msg);
	//close_all_fds();
	rl_clear_history();
	break_free(&g_data);
	exit(error);
}