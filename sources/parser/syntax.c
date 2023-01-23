/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:07:59 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/23 12:06:58 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	cmp(char *s1, char *s2)
{
	if (ft_strcmp(s1, s2) == 0)
		return (TRUE);
	return (FALSE);
}

void	error_syntax(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("\'", 2);
	//free nos esquema td;
	exit(2);
}

void	check_syntax(t_token *tokens)
{
	int	i;
	int	count;

	count = 0;
	while(tokens[count].name)
		count++;
	i = 0;
	while( i < count - 1)
	{
		if (cmp(tokens[0].name, "|"))
			error_syntax("|");
		else if (cmp(tokens[i].name, "|"))
		{
			if (cmp(tokens[i + 1].name, "|"))
				error_syntax("|");
			else if (cmp(tokens[i + 1].name, ">") || cmp(tokens[i + 1].name, ">>") || cmp(tokens[i + 1].name, "<"))
				error_syntax("newline");
		}
		else if (cmp(tokens[i].name, "<"))
		{
			if (cmp(tokens[i + 1].name, "<"))
				error_syntax("|");
			else if (cmp(tokens[i + 1].name, ">") || cmp(tokens[i + 1].name, ">>") || cmp(tokens[i + 1].name, "|") || cmp(tokens[i + 1].name, "<<"))
				error_syntax(tokens[i + 1].name);
		}
		else if (cmp(tokens[i].name, ">"))
		{
			if (cmp(tokens[i + 1].name, ">"))
				error_syntax("|");
			else if (cmp(tokens[i + 1].name, "|") || cmp(tokens[i + 1].name, ">>") || cmp(tokens[i + 1].name, "<") || cmp(tokens[i + 1].name, "<<"))
				error_syntax(tokens[i + 1].name);
		}
		else if (cmp(tokens[i].name, ">>"))
		{
			if (cmp(tokens[i + 1].name, ">>"))
				error_syntax("|");
			else if (cmp(tokens[i + 1].name, ">") || cmp(tokens[i + 1].name, "|") || cmp(tokens[i + 1].name, "<") || cmp(tokens[i + 1].name, "<<"))
				error_syntax(tokens[i + 1].name);
		}
		else if (cmp(tokens[i].name, "<<"))
		{
			if (cmp(tokens[i + 1].name, "<<"))
				error_syntax("|");
			else if (cmp(tokens[i + 1].name, ">") || cmp(tokens[i + 1].name, ">>") || cmp(tokens[i + 1].name, "<") || cmp(tokens[i + 1].name, "|"))
				error_syntax(tokens[i + 1].name);
		}
		i++; 
	}
}

