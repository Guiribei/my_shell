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

void	full_close(t_cmd *cmd)
{
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	if (cmd->pipe[0] != 0)
		close(cmd->pipe[0]);
	if (cmd->pipe[1] != 0)
		close(cmd->pipe[1]);
}
