/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:05:55 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/24 16:06:24 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_input_file(t_cmd	*cmds, char *file, int *flag_quit)
{
	cmds->fd_in = open(file, O_RDONLY);
	if (cmds->fd_in == -1)
	{
		perror_handler(file, ": ", 1, cmds);
		(*flag_quit)++;
	}
}

void	open_output_file(t_cmd	*cmds, char *file, int *flag_quit)
{
	cmds->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmds->fd_out == -1)
	{
		perror_handler(file, ": ", 1, cmds);
		(*flag_quit)++;
	}
}

void	open_append_file(t_cmd	*cmds, char *file, int *flag_quit)
{
	cmds->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmds->fd_out == -1)
	{
		perror_handler(file, ": ", 1, cmds);
		(*flag_quit)++;
	}
}
