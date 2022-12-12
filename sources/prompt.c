/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:35:19 by coder             #+#    #+#             */
/*   Updated: 2022/12/12 15:51:06 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_prompt(const char *name)
{
	char	*line;

	line = readline(name);
	if (line == NULL)
		return (NULL);
	if (line && *line)
		add_history(line);
	return (line);
}
