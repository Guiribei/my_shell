/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:46:36 by tkomeno           #+#    #+#             */
/*   Updated: 2023/01/24 21:00:31 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_double_quotes(char *line, int *i, int *tokens)
{
	(*i)++;
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (line[*i] == '"')
		(*i)++;
	if ((!line[*i]) || is_token(line[*i]) || ft_isspace(line[*i]))
		(*tokens)++;
}

void	skip_single_quotes(char *line, int *i, int *tokens)
{
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] == '\'')
		(*i)++;
	if ((!line[*i]) || is_token(line[*i]) || ft_isspace(line[*i]))
		(*tokens)++;
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
