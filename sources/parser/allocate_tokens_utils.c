/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_tokens_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:10:14 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/24 21:00:18 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	allocate_double(int *curr_token, int *curr_token_size, char *line,
		int *i)
{
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		(*i)++;
		(*curr_token_size)++;
	}
	if (line[*i] == '"')
		(*i)++;
	if ((!line[*i]) || is_token(line[*i]))
		(*curr_token)++;
}

void	allocate_single(int *curr_token, int *curr_token_size, char *line,
		int *i)
{
	(*i)++;
	while (line[*i] && line[*i] != '\'')
	{
		(*i)++;
		(*curr_token_size)++;
	}
	if (line[*i] == '\'')
		(*i)++;
	if ((!line[*i]) || is_token(line[*i]))
		(*curr_token)++;
}

void	allocate_pipe(int *curr_token, int *curr_token_size, int *i)
{
	(*curr_token)++;
	(*curr_token_size)++;
	(*i)++;
}

void	allocate_greater(int *curr_token, int *curr_token_size, char *line,
		int *i)
{
	(*curr_token)++;
	(*curr_token_size)++;
	if (line[*i + 1] && line[*i + 1] == '>')
	{
		(*i)++;
		(*curr_token_size)++;
	}
	(*i)++;
}

void	allocate_less(int *curr_token, int *curr_token_size, char *line, int *i)
{
	(*curr_token)++;
	(*curr_token_size)++;
	if (line[*i + 1] && line[*i + 1] == '<')
	{
		(*i)++;
		(*curr_token_size)++;
	}
	(*i)++;
}
