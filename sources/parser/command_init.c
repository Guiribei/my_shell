/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:00:35 by guribeir          #+#    #+#             */
/*   Updated: 2023/02/13 16:36:35 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	init_heredoc(t_cmd *cmds, t_token *tokens, int *i, int *j)
{
	cmds[*j].fd_in = open(HEREDOC, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cmds[*j].fd_in = heredoc(&cmds[*j], tokens[*i + 1].name);
	cmds[*j].where_read = FILE_IN;
	(*i)++;
}

void	init_less_than(t_cmd *cmds, t_token *tokens, int *i, int *j)
{
	while (cmp(tokens[*i].name, "<"))
	{
		if (cmds[*j].flag_quit != 0)
			break ;
		open_input_file(&cmds[*j], tokens[*i + 1].name);
		cmds[*j].where_read = FILE_IN;
		if (tokens[*i + 2].name && (cmp(tokens[*i + 2].name, "<")))
			*i += 2;
		else
			(*i)++;
	}
}

void	init_greater_than(t_cmd *cmds, t_token *tokens, int *i, int *j)
{
	while ((cmp(tokens[*i].name, ">") || cmp(tokens[*i].name, ">>")))
	{
		if (cmp(tokens[*i].name, ">"))
		{
			if (cmds[*j].flag_quit != 0)
				break ;
			open_output_file(&cmds[*j], tokens[*i +1].name);
			cmds[*j].where_write = FILE_OUT;
		}
		else
		{
			if (cmds[*j].flag_quit != 0)
				break ;
			open_append_file(&cmds[*j], tokens[*i +1].name);
			cmds[*j].where_write = FILE_OUT;
		}
		if (tokens[*i + 2].name && (cmp(tokens[*i + 2].name, ">")
				|| cmp(tokens[*i + 2].name, ">>")))
			*i += 2;
		else
			(*i)++;
	}
}

void	init_normal(t_cmd *cmds, t_token *tokens, int *i, int *j)
{
	char	*temp;
	char	*aux;

	temp = NULL;
	aux = NULL;
	if (!cmds[*j].cmd)
		cmds[*j].cmd = ft_strdup(tokens[*i].name);
	else
	{
		aux = fill_non_space();
		temp = ft_strdup(cmds[*j].cmd);
		free(cmds[*j].cmd);
		cmds[*j].cmd = join_three(temp, aux, tokens[*i].name);
		free(aux);
		free(temp);
	}
}

void	init_pipe(t_cmd *cmds, int *j)
{
	if (pipe(cmds[*j].pipe) == -1)
		perror_handler("pipe", ": ", ++cmds[*j].flag_quit, cmds);
	if (cmds[*j].where_write != FILE_OUT)
		cmds[*j].where_write = PIPE_1;
	cmds[*j + 1].where_read = PIPE_0;
	(*j)++;
}
