/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:23:50 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/19 22:00:00 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is(const char *s, int c)
{
	size_t	s_len;
	char	*ptr;

	ptr = (char *)s;
	s_len = ft_strlen(ptr) + 1;
	while (s_len--)
	{
		if (*ptr == (unsigned char)c)
			return (TRUE);
		ptr++;
	}
	return (FALSE);
}

int	count_iterations(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].cmd)
		i++;
	return (i);
}

void	print_cmd(t_cmd *cmd)
{
	if (cmd)
		printf("CMD POINTER: %p\n", cmd);
	if (cmd->cmd)
		printf("COMMAND: %s\n", cmd->cmd);
	if (cmd->cmds[0])
		printf("COMMANDS[0]: %s\n", cmd->cmds[0]);
	if (cmd->fd_in)
		printf("FD_IN: %d\n", cmd->fd_in);
	if (cmd->fd_out)
		printf("FD_OUT: %d\n", cmd->fd_out);
	if (cmd->path_cmd)
		printf("PATH TO CMD: %s\n", cmd->path_cmd);
	if (cmd->pid)
		printf("PID: %d\n", cmd->pid);
	if (cmd->where_read)
		printf("WHERE READ: %d\n", cmd->where_read);
	if (cmd->where_write)
		printf("WHERE WRITE: %d\n", cmd->where_write);
	printf("PIPE[0]: %d, PIPE[1]: %d\n", cmd->pipe[0], cmd->pipe[1]);
}