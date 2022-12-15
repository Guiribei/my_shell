/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomeno <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:46:36 by tkomeno           #+#    #+#             */
/*   Updated: 2022/12/14 21:47:33 by tkomeno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_space(int *i)
{
	(*i)++;
}

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

void	count_as_token(char *line, int *i, int *tokens)
{
	(*tokens)++;
	while (line[*i] && !ft_isspace(line[*i]))
		(*i)++;
}
