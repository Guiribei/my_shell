/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_tokens_content.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomeno <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:06:54 by tkomeno           #+#    #+#             */
/*   Updated: 2022/12/23 17:37:29 by tkomeno          ###   ########.fr       */
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

void	allocate_normal(char *line, int *i, int *curr_token,
		int *curr_token_size)
{
	while (line[*i] && !ft_isspace(line[*i]))
	{
		(*i)++;
		(*curr_token_size)++;
	}
	(*curr_token)++;
}

int	actual_allocation(t_token **tokens, int curr_token, int curr_token_size)
{
	(*tokens)[curr_token].size = curr_token_size;
	(*tokens)[curr_token].name = ft_calloc(sizeof(char), (curr_token_size + 1));
	if (!(*tokens)[curr_token].name)
		return (-1);
	return (0);
}

t_token	*allocate_tokens_content(char *line, t_token *tokens, int curr_token,
		int curr_token_size)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		curr_token_size = 0;
		if (ft_isspace(line[i]))
			continue ;
		else if (line[i] == '"')
			allocate_double(&curr_token, &curr_token_size, line, &i);
		else if (line[i] == '\'')
			allocate_single(&curr_token, &curr_token_size, line, &i);
		else if (line[i] == '|')
			allocate_pipe(&curr_token, &curr_token_size);
		else if (line[i] == '>')
			allocate_greater(&curr_token, &curr_token_size, line, &i);
		else if (line[i] == '<')
			allocate_less(&curr_token, &curr_token_size, line, &i);
		else
			allocate_normal(line, &i, &curr_token, &curr_token_size);
		if (actual_allocation(&tokens, curr_token, curr_token_size) == -1)
			return (NULL);
	}
	return (tokens);
}
