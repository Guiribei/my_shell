/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott <etachott@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:07:59 by guribeir          #+#    #+#             */
/*   Updated: 2023/02/08 12:56:51 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	cmp(char *s1, char *s2)
{
	if (ft_strcmp(s1, s2) == 0)
		return (TRUE);
	return (FALSE);
}

int	error_syntax(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("\'", 2);
	return (-1);
}

int	compare_signs(t_token *tokens, int *i)
{
	if (cmp(tokens[*i].name, "<"))
	{
		if (lesser_than_middle_syntax(tokens, i) == -1)
			return (-1);
	}
	else if (cmp(tokens[*i].name, ">"))
	{
		if (greater_than_middle_syntax(tokens, i) == -1)
			return (-1);
	}
	else if (cmp(tokens[*i].name, ">>"))
	{
		if (append_syntax(tokens, i) == -1)
			return (-1);
	}
	else if (cmp(tokens[*i].name, "<<"))
	{
		if (heredoc_syntax(tokens, i) == -1)
			return (-1);
	}
	return (0);
}

int	check_syntax(t_token *tokens, int i, int count)
{
	while (tokens[count].name)
		count++;
	while (i < count)
	{
		if (cmp(tokens[0].name, "|"))
			return (error_syntax("|"));
		else if (cmp(tokens[i].name, "|"))
		{
			if (pipe_middle_syntax(tokens, &i) == -1)
				return (-1);
		}
		if (compare_signs(tokens, &i) == -1)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}
