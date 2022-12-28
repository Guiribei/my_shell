/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:01:13 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/28 20:13:10 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_input_file(t_cmd	*cmds, char *file)
{
	cmds->fd_in = open(file, O_RDONLY, 644);
	if (cmds->fd_in == -1)
		printf("minishell: open failed\n");
}

static void	open_output_file(t_cmd	*cmds, char *file)
{
	cmds->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmds->fd_out == -1)
		printf("minishell: open failed\n");
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

	count = 1;
	i = 0;
	while(tokens[i++].name)
		if(cmp(tokens[count].name, "|"))
			count++;
	return (count);
}

void	safe_init(t_cmd **cmds, int size)
{
	int		i;

	i = 0;
	while(i < size)
	{
		cmds[i]->name = NULL;
		cmds[i]->args = NULL;
		cmds[i]->fd_in = -1;
		cmds[i]->fd_out = -1;
		cmds[i]->pipe = ft_calloc(2, sizeof(int));
		i++;
	}
}

t_cmd	*init_cmd_table(t_token *tokens)
{
	t_cmd	*cmds;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	cmds = ft_calloc(count_args(tokens), sizeof (t_cmd)); //aloquei, tem q dar free dps
	safe_init(&cmds, count_args(tokens));
	while (tokens[i].name)
	{
		//esse primeiro if dá o open no cmds[j], o else if ali dá o open no cmds[j - 1], tirei o else q deixaria o fd_in na entrada padrão pq acho q o normal é já estar assim
		if (cmp(tokens[i].name, "<") && i == 0)
		{
			while (tokens[i + 2].name && (cmp(tokens[i + 2].name, "<")))
				i += 2;
			open_input_file(&cmds[j], tokens[i + 1].name);
			i++;
		}
		else if (cmp(tokens[i].name, "<"))
		{
			while (tokens[i + 2].name && (cmp(tokens[i + 2].name, "<")))
				i += 2;
			open_input_file(&cmds[j - 1], tokens[i + 1].name);
			i++;
		}
		else if ((cmp(tokens[i].name, ">") || cmp(tokens[i].name, ">>")) && i == 0)
		{
			while (tokens[i + 2].name && (cmp(tokens[i + 2].name, ">") || cmp(tokens[i + 2].name, ">>")))
				i += 2;
			if (cmp(tokens[i].name, ">"))
				open_output_file(&cmds[j], tokens[i + 1].name);
			else
				open_append_file(&cmds[j], tokens[i + 1].name);
			i++;
		}
		else if (cmp(tokens[i].name, ">") || cmp(tokens[i].name, ">>"))
		{
			while (tokens[i + 2].name && (cmp(tokens[i + 2].name, ">") || cmp(tokens[i + 2].name, ">>")))
				i += 2;
			if (cmp(tokens[i].name, ">"))
				open_output_file(&cmds[j - 1], tokens[i + 1].name);
			else
				open_append_file(&cmds[j - 1], tokens[i + 1].name);
			i++;
		}
		else if (cmp(tokens[i].name, "|"))
		{
			if (pipe(cmds[j].pipe) == -1) // pra funcionar aqui tem q ser j - 1 pra registrar no comando anterior.
				printf("minishell: pipe failed\n");
			j++;
		}
		else
		{
			if (!cmds[j].name)
				cmds[j].name = ft_strdup(tokens[i].name);
			else if (!cmds[j].args)
			{
				cmds[j].args = ft_strdup(tokens[i].name);
				cmds[j + 1].args = NULL; // isso daqui vai dar mt b.o. de memória
			}
			else
				cmds[j].args = join_three(cmds[j].args, " ", tokens[i].name);
		}
		i++;
	}
	return(cmds);
}
