/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:06:29 by tkomeno           #+#    #+#             */
/*   Updated: 2022/12/28 20:39:10 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*before_split(char *line, int *flag)
{
	int		i;
	int		j;
	char	*newline;

	i = -1;
	newline = ft_strdup(line);
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			j = i + 1;
			while (line[j] != '\'')
			{
				if (line[j] == ' ')
				{
					newline[j] = '~';
					*flag = 1;
				}
				j++;
			}
		}
	}
	return (newline);
}

// void	put_space(t_data *pipex)
// {
// 	int		i;
// 	int		j;
// 	char	*aux;

// 	i = -1;
// 	while (pipex->cmds[++i])
// 	{
// 		j = -1;
// 		while (pipex->cmds[i][++j])
// 		{
// 			if (pipex->cmds[i][j] == '~')
// 			{
// 				while (pipex->cmds[i][j] == '~')
// 				{
// 					pipex->cmds[i][j] = ' ';
// 					j++;
// 				}
// 				aux = ft_strdup(pipex->cmds[i]);
// 				free(pipex->cmds[i]);
// 				pipex->cmds[i] = ft_strtrim(aux, "\'");
// 				free(aux);
// 				return ;
// 			}
// 		}
// 	}
// }

t_token	*tokenize(char *line)
{
	t_token	*tokens;
	int		flag;

	flag = 0;
	line = before_split(line, &flag);
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
