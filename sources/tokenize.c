/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomeno <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:06:29 by tkomeno           #+#    #+#             */
/*   Updated: 2022/12/23 17:38:08 by tkomeno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(char *line)
{
	t_token	*tokens;

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
