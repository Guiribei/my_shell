/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomeno <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:05:39 by tkomeno           #+#    #+#             */
/*   Updated: 2022/12/23 17:37:51 by tkomeno          ###   ########.fr       */
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
