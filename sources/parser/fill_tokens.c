/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:07:22 by tkomeno           #+#    #+#             */
/*   Updated: 2023/01/24 14:53:51 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_normal(char *line, int *i, t_token **tokens, int *curr_token)
{
	int	curr_token_size;

	curr_token_size = 0;
	while (line[*i] && !ft_isspace(line[*i]) && !is_token(line[*i])
		&& curr_token_size < (*tokens)[*curr_token].size)
	{
		while (line[*i] == '\"' || line[*i] == '\'')
			(*i)++;
		if (line[*i] && !ft_isspace(line[*i]) && !is_token(line[*i])
		&& curr_token_size < (*tokens)[*curr_token].size)
		{
			(*tokens)[*curr_token].name[curr_token_size] = line[*i];
			(*i)++;
			curr_token_size++;
		}
	}
	(*curr_token)++;
	if (ft_isspace(line[*i]) || line[*i] == '\'' || line[*i] == '\"')
		(*i)++;
}

t_token	*fill_tokens_content(char *line, t_token *tokens)
{
	int	i;
	int	curr_token;

	curr_token = 0;
	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			i++;
			continue ;
		}
		//else if (line[i] == '"')
		//	fill_double(&i, line, &curr_token, &tokens);
		//else if (line[i] == '\'')
		//	fill_single(&i, line, &curr_token, &tokens);
		else if (line[i] == '|')
			fill_pipe(&tokens, &curr_token, line, &i);
		else if (line[i] == '>')
			fill_greater(&tokens, &curr_token, &i, line);
		else if (line[i] == '<')
			fill_less(&tokens, &curr_token, &i, line);
		else
			fill_normal(line, &i, &tokens, &curr_token);
		if (!line[i])
			break ;
	}
	return (tokens);
}
