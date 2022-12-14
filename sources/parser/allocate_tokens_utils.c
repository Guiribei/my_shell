/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_tokens_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:10:14 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/23 22:10:25 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	allocate_double(int *curr_token, int *curr_token_size, char *line,
		int *i)
{
	(*curr_token)++;
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		(*i)++;
		(*curr_token_size)++;
	}
	if (line[*i] == '"')
		(*i)++;
}

void	allocate_single(int *curr_token, int *curr_token_size, char *line,
		int *i)
{
	(*curr_token)++;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
	{
		(*i)++;
		(*curr_token_size)++;
	}
	if (line[*i] == '\'')
		(*i)++;
}

void	allocate_pipe(int *curr_token, int *curr_token_size)
{
	(*curr_token)++;
	(*curr_token_size)++;
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
}
