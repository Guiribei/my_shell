/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_comp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott <etachott@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:09:32 by guribeir          #+#    #+#             */
/*   Updated: 2023/02/08 13:10:51 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_middle_syntax(t_token *tokens, int *i)
{
	if (tokens[*i + 1].is_sentinel)
		return (error_syntax("newline"));
	if (cmp(tokens[*i + 1].name, "|"))
		return (error_syntax("|"));
	else if (cmp(tokens[*i + 1].name, ">") || cmp(tokens[*i + 1].name, ">>")
		|| cmp(tokens[*i + 1].name, "<") || cmp(tokens[*i + 1].name, "<<"))
		return (error_syntax("newline"));
	return (0);
}

int	lesser_than_middle_syntax(t_token *tokens, int *i)
{
	if (tokens[*i + 1].is_sentinel)
		return (error_syntax("newline"));
	if (cmp(tokens[*i + 1].name, "<"))
		return (error_syntax("|"));
	else if (cmp(tokens[*i + 1].name, ">") || cmp(tokens[*i + 1].name, ">>")
		|| cmp(tokens[*i + 1].name, "|") || cmp(tokens[*i + 1].name, "<<"))
		return (error_syntax(tokens[*i + 1].name));
	return (0);
}

int	greater_than_middle_syntax(t_token *tokens, int *i)
{
	if (tokens[*i + 1].is_sentinel)
		return (error_syntax("newline"));
	if (cmp(tokens[*i + 1].name, ">"))
		return (error_syntax("|"));
	else if (cmp(tokens[*i + 1].name, "|") || cmp(tokens[*i + 1].name, ">>")
		|| cmp(tokens[*i + 1].name, "<") || cmp(tokens[*i + 1].name, "<<"))
		return (error_syntax(tokens[*i + 1].name));
	return (0);
}

int	append_syntax(t_token *tokens, int *i)
{
	if (tokens[*i + 1].is_sentinel)
		return (error_syntax("newline"));
	if (cmp(tokens[*i + 1].name, ">>"))
		return (error_syntax("|"));
	else if (cmp(tokens[*i + 1].name, ">") || cmp(tokens[*i + 1].name, "|")
		|| cmp(tokens[*i + 1].name, "<") || cmp(tokens[*i + 1].name, "<<"))
		return (error_syntax(tokens[*i + 1].name));
	return (0);
}

int	heredoc_syntax(t_token *tokens, int *i)
{
	if (tokens[*i + 1].is_sentinel)
		return (error_syntax("newline"));
	if (cmp(tokens[*i + 1].name, "<<"))
		return (error_syntax("|"));
	else if (cmp(tokens[*i + 1].name, ">") || cmp(tokens[*i + 1].name, ">>")
		|| cmp(tokens[*i + 1].name, "<") || cmp(tokens[*i + 1].name, "|"))
		return (error_syntax(tokens[*i + 1].name));
	return (0);
}
