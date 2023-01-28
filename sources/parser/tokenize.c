/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:06:29 by tkomeno           #+#    #+#             */
/*   Updated: 2023/01/27 01:23:00 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

t_token	*tokenize(char *line)
{
	t_token	*tokens;

	tokens = allocate_tokens(line);
	if (!tokens)
		return (NULL);
	g_data.j = 0;
	tokens = allocate_tokens_content(line, tokens, -1, 0);
	if (!tokens)
		return (NULL);
	tokens = fill_tokens_content(line, tokens, 0, 0);
	if (!tokens)
		return (NULL);
	return (tokens);
}
