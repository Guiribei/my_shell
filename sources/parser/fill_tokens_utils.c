/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:15:25 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/20 17:46:24 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_double(int *i, char *line, int *curr_token, t_token **tokens)
{
	int	curr_token_size;

	curr_token_size = 0;
	(*i)++;
	while (line[*i] && line[*i] != '"'
		&& curr_token_size < (*tokens)[*curr_token].size)
	{
		(*tokens)[*curr_token].name[curr_token_size] = line[*i];
		curr_token_size++;
		(*i)++;
	}
	(*curr_token)++;
	if (line[*i] == '"')
		(*i)++;
}

void	fill_single(int *i, char *line, int *curr_token, t_token **tokens)
{
	int	curr_token_size;

	curr_token_size = 0;
	(*i)++;
	while (line[*i] && line[*i] != '\''
		&& curr_token_size < (*tokens)[*curr_token].size)
	{
		if (line[*i] == '~')
			(*tokens)[*curr_token].name[curr_token_size] = ' ';
		else
			(*tokens)[*curr_token].name[curr_token_size] = line[*i];
		curr_token_size++;
		(*i)++;
	}
	(*curr_token)++;
	if (line[*i] == '\'')
		(*i)++;
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
