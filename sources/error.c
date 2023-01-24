/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:30:53 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/24 16:19:13 by guribeir         ###   ########.fr       */
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
	rl_clear_history();
	break_free(&g_data);
	exit(error);
}

void	perror_handler(char *str1, char *str2, int status, t_cmd *cmds)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	perror("");
	if (cmds)
		full_close(cmds);
	g_data.exit_status = status;
}
