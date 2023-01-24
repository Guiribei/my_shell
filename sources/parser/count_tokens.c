/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:09:58 by tkomeno           #+#    #+#             */
/*   Updated: 2023/01/24 16:08:44 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_as_token(char *line, int *i, int *tokens)
{
	(*tokens)++;
	while (line[*i] && !ft_isspace(line[*i]) && !is_token(line[*i]))
		(*i)++;
}

int	count_tokens(char *line)
{
	int	i;
	int	tokens;

	i = 0;
	tokens = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '|')
			skip_pipe(&i, &tokens);
		else if (line[i] == '>')
			skip_gt(&i, &tokens, line);
		else if (line[i] == '<')
			skip_lt(&i, &tokens, line);
		else
			count_as_token(line, &i, &tokens);
	}
	return (tokens);
}
