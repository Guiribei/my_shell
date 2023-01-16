/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:06:54 by tkomeno           #+#    #+#             */
/*   Updated: 2023/01/16 18:17:27 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*allocate_tokens(char *line)
{
	t_token	*tokens;

	tokens = ft_calloc(sizeof(t_token), (count_tokens(line) + 1));
	if (!tokens)
		return (NULL);
	return (tokens);
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
		if (!line[i])
			break ;
	}
	//tokens[count_tokens]
	return (tokens);
}
