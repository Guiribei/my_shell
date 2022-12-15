/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:09:58 by tkomeno           #+#    #+#             */
/*   Updated: 2022/12/15 20:09:00 by tkomeno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(char *line)
{
	int	i;
	int	tokens;

	i = 0;
	tokens = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			skip_space(&i);
		else if (line[i] == '"')
			skip_double_quotes(line, &i, &tokens);
		else if (line[i] == '\'')
			skip_single_quotes(line, &i, &tokens);
		else if (line[i] == '|')
			skip_pipe(&i, &tokens);
		else
			count_as_token(line, &i, &tokens);
	}
	return (tokens);
}

t_token	*allocate_tokens(char *line)
{
	t_token	*tokens;

	tokens = ft_calloc(sizeof(t_token), (count_tokens(line) + 1));
	if (!tokens)
		return (NULL);
	return (tokens);
}

t_token	*allocate_tokens_content(char *line, t_token *tokens)
{
	int	i;
	int	curr_token;
	int	curr_token_size;

	curr_token = 0;
	i = -1;
	while (line[++i])
	{
		curr_token_size = 0;
		if (ft_isspace(line[i]))
			skip_space(&i);
		else if (line[i] == '"')
		{
			curr_token++;
			i++;
			while (line[i] && line[i] != '"')
			{
				i++;
				curr_token_size++;
			}
			if (line[i] == '"')
				i++;
		}
		else if (line[i] == '\'')
		{
			curr_token++;
			i++;
			while (line[i] && line[i] != '\'')
			{
				i++;
				curr_token_size++;
			}
			if (line[i] == '\'')
				i++;
		}
		else if (line[i] == '|')
		{
			i++;
			curr_token++;
			curr_token_size++;
		}
		else
		{
			while (line[i] && !ft_isspace(line[i]))
			{
				curr_token++;
				i++;
				curr_token_size++;
			}
		}
		tokens[curr_token].size = curr_token_size;
		tokens[curr_token].name = ft_calloc(sizeof(char), (curr_token_size
					+ 1));
		if (!tokens[curr_token].name)
			//TODO: free all allocated tokens
			return (NULL);
	}
	return (tokens);
}

t_token	*fill_tokens_content(char *line, t_token *tokens)
{
	int	i;
	int	curr_token_size;
	int	curr_token;

	curr_token = 0;
	i = -1;
	while (line[++i])
	{
		curr_token_size = 0;
		if (ft_isspace(line[i]))
			skip_space(&i);
		else if (line[i] == '"')
		{
			curr_token++;
			i++;
			while (line[i] && line[i] != '"'
				&& curr_token_size < tokens[curr_token].size)
			{
				curr_token_size++;
				tokens[curr_token].name[curr_token_size] = line[i];
				i++;
			}
			if (line[i] == '"')
				i++;
		}
		else if (line[i] == '\'')
		{
			curr_token++;
			i++;
			while (line[i] && line[i] != '\''
				&& curr_token_size < tokens[curr_token].size)
			{
				curr_token_size++;
				tokens[curr_token].name[curr_token_size] = line[i];
				i++;
			}
			if (line[i] == '\'')
				i++;
		}
		else if (line[i] == '|')
		{
			curr_token_size++;
			tokens[curr_token].name[curr_token_size] = line[i];
			curr_token++;
			i++;
		}
		else
		{
			while (line[i] && !ft_isspace(line[i])
				&& curr_token_size < tokens[curr_token].size)
			{
				curr_token++;
				tokens[curr_token].name[curr_token_size] = line[i];
				i++;
			}
		}
	}
	return (tokens);
}

t_token *tokenize(char *line)
{
	t_token	*tokens;

	tokens = allocate_tokens(line);
	if (!tokens)
		return (NULL);
	tokens = allocate_tokens_content(line, tokens);
	if (!tokens)
		return (NULL);
	tokens = fill_tokens_content(line, tokens);
	if (!tokens)
		return (NULL);
	return (tokens);
}
