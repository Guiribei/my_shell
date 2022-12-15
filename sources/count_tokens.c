/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:09:58 by tkomeno           #+#    #+#             */
/*   Updated: 2022/12/15 14:51:30 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_tokens(char *line)
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

t_token *allocate_tokens(char *line)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = malloc(sizeof(t_token) * (count_tokens(line) + 1));
	if (!tokens)
		return (NULL);
	while (i < count_tokens(line))
	{
		tokens[i].name = NULL;
		i++;
	}
	tokens[i].name = NULL;
	return (tokens);
}

//TODO: fill the allocated array with the token content
/*void fill_tokens(char *line, t_token *tokens)
{
}*/
