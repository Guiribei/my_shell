/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:41:17 by vkist-si          #+#    #+#             */
/*   Updated: 2023/01/23 23:10:49 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int heredoc(t_cmd *cmds, char *delimiter)
{
	char *line;

	line = readline("> ");
	while (line && !cmp(line, delimiter))
	{
		ft_putendl_fd(line, cmds->fd_in);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(cmds->fd_in);
	return (open(HEREDOC, O_RDONLY));
}
