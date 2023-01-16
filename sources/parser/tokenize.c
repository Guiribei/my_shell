/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:06:29 by tkomeno           #+#    #+#             */
/*   Updated: 2023/01/16 18:45:25 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(char *line)
{
	t_token	*tokens;
	int		flag;

	flag = 0;
	tokens = allocate_tokens(line);
	if (!tokens)
		return (NULL);
	tokens = allocate_tokens_content(line, tokens, -1, 0);
	if (!tokens)
		return (NULL);
	tokens = fill_tokens_content(line, tokens);
	if (!tokens)
		return (NULL);
	return (tokens);
}
