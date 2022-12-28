/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:01:13 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/28 13:27:51 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_input_file(t_cmd	*cmds, char *file)
{
	cmds->fd_in = open(file, O_RDONLY, 644);
	if (cmds->fd_in == -1)
		printf("minishell: open failed");
}

static void	open_output_file(t_cmd	*cmds, char *file)
{
	cmds->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmds->fd_out == -1)
		printf("minishell: open failed");
}

static void	open_append_file(t_cmd	*cmds, char *file)
{
	cmds->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmds->fd_out == -1)
		printf("minishell: open failed\n");
}

int	count_args(t_token *tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while(tokens[i++].name)
		if(!cmp(tokens[count].name, "|") && !cmp(tokens[count].name, "<") 
			&& !cmp(tokens[count].name, ">") && !cmp(tokens[count].name, "<<")
				&& !cmp(tokens[count].name, ">>"))
			count++;
	return (count);
}

t_cmd	*init_cmd_table(t_token *tokens)
{
	t_cmd	*cmds;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	cmds = ft_calloc(count_args(tokens), sizeof (t_cmd)); //aloquei, tem q dar free dps
	while (tokens[i].name)
	{
		//esse primeiro if dá o open no cmds[i], o else if ali dá o open no cmds[ i - 1], tirei o else q deixaria o fd_in na entrada padrão pq acho q o normal é já estar assim
		if (cmp(tokens[i].name, "<") && i == 0)
		{
			while (tokens[i + 2].name && (cmp(tokens[i + 2].name, "<")))
				i += 2;
			open_input_file(&cmds[i], tokens[i + 1].name);
		}
		else if (cmp(tokens[i].name, "<"))
		{
			while (tokens[i + 2].name && (cmp(tokens[i + 2].name, "<")))
				i += 2;
			open_input_file(&cmds[i - 1], tokens[i + 1].name);
		}
		else if ((cmp(tokens[i].name, ">") || cmp(tokens[i].name, ">>")) && i == 0)
		{
			while (tokens[i + 2].name && (cmp(tokens[i + 2].name, ">") || cmp(tokens[i + 2].name, ">>")))
				i += 2;
			if (cmp(tokens[i].name, ">"))
				open_output_file(&cmds[i], tokens[i + 1].name);
			else
				open_append_file(&cmds[i], tokens[i + 1].name);
		}
		else if (cmp(tokens[i].name, ">") || cmp(tokens[i].name, ">>"))
		{
			while (tokens[i + 2].name && (cmp(tokens[i + 2].name, ">") || cmp(tokens[i + 2].name, ">>")))
				i += 2;
			if (cmp(tokens[i].name, ">"))
				open_output_file(&cmds[i - 1], tokens[i + 1].name);
			else
				open_append_file(&cmds[i - 1], tokens[i + 1].name);
		}
		printf("infile fd: %d\n outfile fd: %d\n", cmds[i].fd_in, cmds[i].fd_out);
		i++;
	}
	return(cmds);
}
