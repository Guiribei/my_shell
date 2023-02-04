/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:06:54 by tkomeno           #+#    #+#             */
/*   Updated: 2023/02/03 03:18:17 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

t_token	*allocate_tokens(char *line)
{
	t_token	*tokens;
	int		tokens_count;

	tokens_count = count_tokens(line);
	if (tokens_count == 0)
		return (NULL);
	tokens = ft_calloc(sizeof(t_token), (tokens_count + 1));
	if (!tokens)
		return (NULL);
	return (tokens);
}

void	allocate_normal(char *line, int *i, int *curr_token,
		int *curr_token_size)
{
	while (line[*i] == ' ')
		(*i)++;
	while (line[*i] && !ft_isspace(line[*i]) && !is_token(line[*i]))
	{
		while (line[*i] == '\"' || line[*i] == '\'')
			(*i)++;
		if (line[*i] && !ft_isspace(line[*i]) && !is_token(line[*i]))
		{
			(*i)++;
			(*curr_token_size)++;
		}
		while (line[*i] == '\"' || line[*i] == '\'')
			(*i)++;
	}
	(*curr_token)++;
}

int	actual_allocation(t_token **tokens, int curr_token, int *curr_token_size)
{
	(*tokens)[curr_token].size = *curr_token_size;
	(*tokens)[curr_token].name = ft_calloc(sizeof(char),
			(*curr_token_size + 1));
	if (!(*tokens)[curr_token].name)
		return (-1);
	(*curr_token_size) = 0;
	return (0);
}

t_token	*allocate_tokens_content(char *line, t_token *tokens, int curr_token,
		int curr_token_size)
{
	while (line[g_data.j])
	{
		if (ft_isspace(line[g_data.j]) && g_data.j++)
			continue ;
		else if (line[g_data.j] == '"')
			allocate_double(&curr_token, &curr_token_size, line, &g_data.j);
		else if (line[g_data.j] == '\'')
			allocate_single(&curr_token, &curr_token_size, line, &g_data.j);
		else if (line[g_data.j] == '|')
			allocate_pipe(&curr_token, &curr_token_size, &g_data.j);
		else if (line[g_data.j] == '>')
			allocate_greater(&curr_token, &curr_token_size, line, &g_data.j);
		else if (line[g_data.j] == '<')
			allocate_less(&curr_token, &curr_token_size, line, &g_data.j);
		else
			allocate_normal(line, &g_data.j, &curr_token, &curr_token_size);
		if (line[g_data.j] == '"' || line[g_data.j] == '\'')
			continue ;
		if (actual_allocation(&tokens, curr_token, &curr_token_size) == -1)
			return (NULL);
		if (!line[g_data.j])
			break ;
	}
	return (tokens);
}
