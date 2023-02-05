/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:15:25 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/26 21:01:38 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	fill_double(int *i, char *line, int *curr_token, t_token **tokens)
{
	(*i)++;
	while (line[*i] && line[*i] != '"'
		&& (g_data.index) < (*tokens)[*curr_token].size)
	{
		(*tokens)[*curr_token].name[g_data.index] = line[*i];
		(g_data.index)++;
		(*i)++;
	}
	if (line[*i] == '"')
		(*i)++;
	if ((!line[*i]) || is_token(line[*i]) || ft_isspace(line[*i]))
	{
		(g_data.index) = 0;
		(*curr_token)++;
	}
}

void	fill_single(int *i, char *line, int *curr_token, t_token **tokens)
{
	(*i)++;
	while (line[*i] && line[*i] != '\''
		&& (g_data.index) < (*tokens)[*curr_token].size)
	{
		if (line[*i] == '~')
			(*tokens)[*curr_token].name[g_data.index] = ' ';
		else
			(*tokens)[*curr_token].name[g_data.index] = line[*i];
		(g_data.index)++;
		(*i)++;
	}
	if (line[*i] == '\'')
		(*i)++;
	if ((!line[*i]) || is_token(line[*i]) || ft_isspace(line[*i]))
	{
		(g_data.index) = 0;
		(*curr_token)++;
	}
}

void	fill_pipe(t_token **tokens, int *curr_token, char *line, int *i)
{
	(*tokens)[*curr_token].name[0] = line[*i];
	(*curr_token)++;
	(*i)++;
}

void	fill_greater(t_token **tokens, int *curr_token, int *i, char *line)
{
	int	curr_token_size;

	curr_token_size = 0;
	(*tokens)[*curr_token].name[curr_token_size] = line[*i];
	if (line[*i + 1] && line[*i + 1] == '>')
	{
		(*i)++;
		curr_token_size++;
		(*tokens)[*curr_token].name[curr_token_size] = line[*i];
	}
	(*curr_token)++;
	(*i)++;
}

void	fill_less(t_token **tokens, int *curr_token, int *i, char *line)
{
	int	curr_token_size;

	curr_token_size = 0;
	(*tokens)[*curr_token].name[curr_token_size] = line[*i];
	if (line[*i + 1] && line[*i + 1] == '<')
	{
		(*i)++;
		curr_token_size++;
		(*tokens)[*curr_token].name[curr_token_size] = line[*i];
	}
	(*curr_token)++;
	(*i)++;
}
