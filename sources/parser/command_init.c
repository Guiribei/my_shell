/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:00:35 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/24 18:03:33 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	init_heredoc(t_cmd *cmds, t_token *tokens, int *i)
{
	cmds[*i].fd_in = open(HEREDOC, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cmds[*i].fd_in = heredoc(&cmds[*i], tokens[*i + 1].name);
	cmds[*i].where_read = FILE_IN;
	(*i)++;
}

void	init_less_than(t_cmd *cmds, t_token *tokens, int *i, int *j)
{
	while (tokens[*i + 2].name && (cmp(tokens[*i + 2].name, "<")))
		*i += 2;
	open_input_file(&cmds[*j], tokens[*i + 1].name, &g_data.flag_quit);
	cmds[*j].where_read = FILE_IN;
	(*i)++;
}

void	init_greater_than(t_cmd *cmds, t_token *tokens, int *i, int *j)
{
	while (tokens[*i + 2].name && (cmp(tokens[*i + 2].name, ">")
			|| cmp(tokens[*i + 2].name, ">>")))
		*i += 2;
	if (cmp(tokens[*i].name, ">"))
	{
		open_output_file(&cmds[*j], tokens[*i + 1].name, &g_data.flag_quit);
		cmds[*j].where_write = FILE_OUT;
	}
	else
	{
		open_append_file(&cmds[*j], tokens[*i + 1].name, &g_data.flag_quit);
		cmds[*j].where_write = FILE_OUT;
	}
	(*i)++;
}

void	init_normal(t_cmd *cmds, t_token *tokens, int *i, int *j)
{
	char	*temp;

	temp = NULL;
	if (!cmds[*j].cmd)
		cmds[*j].cmd = ft_strdup(tokens[*i].name);
	else
	{
		temp = ft_strdup(cmds[*j].cmd);
		free(cmds[*j].cmd);
		cmds[*j].cmd = join_three(temp, " ", tokens[*i].name);
		free(temp);
	}
}

void	init_pipe(t_cmd *cmds, int *j)
{
	if (pipe(cmds[*j].pipe) == -1)
		perror_handler("pipe", ": ", ++g_data.flag_quit, cmds);
	if (cmds[*j].where_write != FILE_OUT)
		cmds[*j].where_write = PIPE_1;
	cmds[*j + 1].where_read = PIPE_0;
	(*j)++;
}
