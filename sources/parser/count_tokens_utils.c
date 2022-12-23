/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:46:36 by tkomeno           #+#    #+#             */
/*   Updated: 2022/12/23 22:13:25 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_double_quotes(char *line, int *i, int *tokens)
{
	(*tokens)++;
	(*i)++;
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (line[*i] == '"')
		(*i)++;
}

void	skip_single_quotes(char *line, int *i, int *tokens)
{
	(*tokens)++;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] == '\'')
		(*i)++;
}

void	skip_pipe(int *i, int *tokens)
{
	(*i)++;
	(*tokens)++;
}

void	skip_gt(int *i, int *tokens, char *line)
{
	(*i)++;
	if (line[*i] == '>')
		(*i)++;
	(*tokens)++;
}

void	skip_lt(int *i, int *tokens, char *line)
{
	(*i)++;
	if (line[*i] == '<')
		(*i)++;
	(*tokens)++;
}
