/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:30:53 by guribeir          #+#    #+#             */
/*   Updated: 2023/02/14 01:13:00 by etachott         ###   ########.fr       */
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

int	perror_handler_int(char *str1, char *str2, int status, t_cmd *cmds)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	perror("");
	if (cmds)
		full_close(cmds);
	g_data.exit_status = status;
	return (status);
}

void	full_close(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].cmd)
	{
		if (cmds[i].fd_in != 0 )//&& cmds[i].fd_in != -1)
			close(cmds[i].fd_in);
		if (cmds[i].fd_out != 1)// && cmds[i].fd_in != -1)
			close(cmds[i].fd_out );
		if (cmds[i].pipe[0] != 0)// && cmds[i].fd_in != -1)
			close(cmds[i].pipe[0]);
		if (cmds[i].pipe[1] != 0)// && cmds[i].fd_in != -1)
			close(cmds[i].pipe[1]);
		i++;
	}
}
