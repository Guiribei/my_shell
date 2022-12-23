/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomeno <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:07:22 by tkomeno           #+#    #+#             */
/*   Updated: 2022/12/23 17:54:40 by tkomeno          ###   ########.fr       */
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
		(*tokens)[*curr_token].name[curr_token_size] = line[*i];
		curr_token_size++;
		(*i)++;
	}
	(*curr_token)++;
	if (line[*i] == '\'')
		(*i)++;
}

void	fill_pipe(t_token **tokens, int *curr_token, char *line, int i)
{
	(*tokens)[*curr_token].name[0] = line[i];
	(*curr_token)++;
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
}

void	fill_normal(char *line, int *i, t_token **tokens, int *curr_token)
{
	int	curr_token_size;

	curr_token_size = 0;
	while (line[*i] && !ft_isspace(line[*i])
		&& curr_token_size < (*tokens)[*curr_token].size)
	{
		(*tokens)[*curr_token].name[curr_token_size] = line[*i];
		(*i)++;
		curr_token_size++;
	}
	(*curr_token)++;
}

t_token	*fill_tokens_content(char *line, t_token *tokens)
{
	int	i;
	int	curr_token;

	curr_token = 0;
	i = -1;
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			continue ;
		else if (line[i] == '"')
			fill_double(&i, line, &curr_token, &tokens);
		else if (line[i] == '\'')
			fill_single(&i, line, &curr_token, &tokens);
		else if (line[i] == '|')
			fill_pipe(&tokens, &curr_token, line, i);
		else if (line[i] == '>')
			fill_greater(&tokens, &curr_token, &i, line);
		else if (line[i] == '<')
			fill_less(&tokens, &curr_token, &i, line);
		else
			fill_normal(line, &i, &tokens, &curr_token);
	}
	return (tokens);
}
