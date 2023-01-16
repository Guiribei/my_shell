/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:34:34 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/16 19:00:04 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	before_split(char *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\'')
		{
			j = i + 1;
			while (cmd[j] != '\'')
			{
				if (cmd[j] == ' ')
					cmd[j] = (char)(2);
				j++;
			}
			return (1);
		}
	}
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\"')
		{
			j = i + 1;
			while (cmd[j] != '\"')
			{
				if (cmd[j] == ' ')
					cmd[j] = (char)(2);
				j++;
			}
			return (1);
		}
	}
	return (0);
}

static void	put_space(t_cmd *cmds)
{
	int		i;
	int		j;
	char	*aux;

	i = -1;
	while (cmds[++i].cmd)
	{
		j = -1;
		while (cmds[++i].cmd[++j])
		{
			if (cmds[i].cmd[j] == (char)(2))
			{
				while (cmds[i].cmd[j] == (char)(2))
				{
					cmds[i].cmd[j] = ' ';
					j++;
				}
				aux = ft_strdup(cmds[i].cmd);
				free(cmds[i].cmd);
				cmds[i].cmd = ft_strtrim(aux, "\'\"");
				free(aux);
				return ;
			}
		}
	}
}

void	split_cmds(t_cmd *cmds)
{
	int		i;
	int		flag;
	
	if (!cmds)
		return ;
	i = 0;
	flag = 0;
	while(cmds[i].cmd)
	{
		flag = before_split(cmds[i].cmd);
		cmds[i].cmds = ft_split(cmds[i].cmd, ' ');
		if (flag)
			put_space(cmds);
		if (!cmds[i].cmds)
			printf("Error malloc\n");
		i++;
	}
}