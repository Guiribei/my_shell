/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:01:13 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/27 02:09:41 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_input_file(t_cmd	*cmds, char *file)
{
	cmds->fd_in = open(file, O_RDONLY, 644);
	if (cmds->fd_in == -1)
		printf("minishell: open failed");
}

//static void	open_output_file(t_cmd	*cmds, char *file)
//{
	//cmds.fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//if (cmds->fd_in == -1)
		//perror_handler(pipex->argv[pipex->argc - 1], ": ", 1, minishell);
//}

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
		//esse primeiro if dá o open no cmds[i], o else if ali dá o open no cmds[ i - 1], o else deixa o fd_in na entrada padrão
		if (cmp(tokens[i].name, "<") && i == 0)
		{
			while (cmp(tokens[i + 2].name, "<"))
				i += 2;
			open_input_file(&cmds[i], tokens[i + 1].name);
		}
		else if (cmp(tokens[i].name, "<"))
		{
			while (cmp(tokens[i + 2].name, "<"))
				i += 2;
			open_input_file(&cmds[i - 1], tokens[i + 1].name);
		}
		else
			cmds[0].fd_in = 0;
		i++;
	}
	return(cmds);
}
