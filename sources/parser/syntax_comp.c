/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_comp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:09:32 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/24 19:14:24 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_middle_syntax(t_token *tokens, int *i)
{
	if (cmp(tokens[*i + 1].name, "|"))
		return (error_syntax("|"));
	else if (cmp(tokens[*i + 1].name, ">") || cmp(tokens[*i + 1].name, ">>")
		|| cmp(tokens[*i + 1].name, "<") || cmp(tokens[*i + 1].name, "<<"))
		return (error_syntax("newline"));
	return (0);
}

int	lesser_than_middle_syntax(t_token *tokens, int *i)
{
	if (cmp(tokens[*i + 1].name, "<"))
		return (error_syntax("|"));
	else if (cmp(tokens[*i + 1].name, ">") || cmp(tokens[*i + 1].name, ">>")
		|| cmp(tokens[*i + 1].name, "|") || cmp(tokens[*i + 1].name, "<<"))
		return (error_syntax(tokens[*i + 1].name));
	return (0);
}

int	greater_than_middle_syntax(t_token *tokens, int *i)
{
	if (cmp(tokens[*i + 1].name, ">"))
		return (error_syntax("|"));
	else if (cmp(tokens[*i + 1].name, "|") || cmp(tokens[*i + 1].name, ">>")
		|| cmp(tokens[*i + 1].name, "<") || cmp(tokens[*i + 1].name, "<<"))
		return (error_syntax(tokens[*i + 1].name));
	return (0);
}

int	append_syntax(t_token *tokens, int *i)
{
	if (cmp(tokens[*i + 1].name, ">>"))
		return (error_syntax("|"));
	else if (cmp(tokens[*i + 1].name, ">") || cmp(tokens[*i + 1].name, "|")
		|| cmp(tokens[*i + 1].name, "<") || cmp(tokens[*i + 1].name, "<<"))
		return (error_syntax(tokens[*i + 1].name));
	return (0);
}

int	heredoc_syntax(t_token *tokens, int *i)
{
	if (cmp(tokens[*i + 1].name, "<<"))
		return (error_syntax("|"));
	else if (cmp(tokens[*i + 1].name, ">") || cmp(tokens[*i + 1].name, ">>")
		|| cmp(tokens[*i + 1].name, "<") || cmp(tokens[*i + 1].name, "|"))
		return (error_syntax(tokens[*i + 1].name));
	return (0);
}
