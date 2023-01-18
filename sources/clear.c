/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:37:30 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/07 19:08:06 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	strclear(char **str)
{
	if (!str)
		return ;
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

int	count_rows(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

void	strsclear(char **ptrs)
{
	int	i;
	int	elements;

	if (!ptrs)
		return ;
	if (ptrs != NULL)
	{
		elements = count_rows(ptrs);
		i = 0;
		while (i < elements)
		{
			if (ptrs[i] != NULL)
				free(ptrs[i]);
			i++;
		}
		free(ptrs);
		ptrs = NULL;
	}
}

void	full_close(t_cmd *cmds)
{
	int	i;

	i = 0;
	while(cmds[i].cmd)
	{
		if (cmds[i].fd_in != 0)
			close(cmds[i].fd_in);
		if (cmds[i].fd_out != 1)
			close(cmds[i].fd_out);
		if (cmds[i].pipe[0] != 0)
			close(cmds[i].pipe[0]);
		if (cmds[i].pipe[1] != 0)
			close(cmds[i].pipe[1]);
		i++;
	}
	dup2(0, g_data.std_in_fd);
	dup2(1, g_data.std_out_fd);
}
