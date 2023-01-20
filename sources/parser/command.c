/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkist-si <vkist-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:01:13 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/20 21:59:57 by vkist-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static void	open_input_file(t_cmd	*cmds, char *file)
{
	cmds->fd_in = open(file, O_RDONLY);
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

int	count_cmds(t_token *tokens)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while(tokens[i].name)
	{
		if(cmp(tokens[i].name, "|"))
			count++;
		i++;
	}
	return (count);
}

void	safe_init(t_cmd *cmds, int size)
{
	int		i;

	i = 0;
	while(i < size)
	{
		cmds[i].cmd = NULL;
		cmds[i].cmds = NULL;
		cmds[i].fd_in = 0;
		cmds[i].fd_out = 1;
		cmds[i].path_cmd = NULL;
		cmds[i].pid = -1;
		cmds[i].where_read = STD_IN;
		cmds[i].where_write = STD_OUT;
		memset(cmds[i].pipe, 0, 2);
		i++;
	}
}

t_cmd	*init_cmd_table(t_token *tokens)
{
	t_cmd	*cmds;
	char	*temp;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	cmds = ft_calloc(count_cmds(tokens) + 1, sizeof (t_cmd)); //aloquei (isso e mais mt coisa), tem q dar free dps
	safe_init(cmds, count_cmds(tokens) + 1);// aqui também tem calloc (dos ints fd_in e fd_out)
	while (tokens[i].name)
	{
		if (cmp(tokens[i].name, "<") && j == 0)
		{
			while (tokens[i + 2].name && (cmp(tokens[i + 2].name, "<")))
				i += 2;
			open_input_file(&cmds[j], tokens[i + 1].name);
			cmds[j].where_read = FILE_IN;
			i++;
		}
		else if (cmp(tokens[i].name, "<<"))
		{
			
			cmds[j].fd_in = open(HEREDOC, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			cmds[j].fd_in = heredoc(&cmds[j], tokens[i + 1].name);
			i++;
		}
		else if (cmp(tokens[i].name, ">") || cmp(tokens[i].name, ">>"))
		{
			while (tokens[i + 2].name && (cmp(tokens[i + 2].name, ">") || cmp(tokens[i + 2].name, ">>")))
				i += 2;
			if (cmp(tokens[i].name, ">"))
			{
				open_output_file(&cmds[j], tokens[i + 1].name);
				cmds[j].where_write = FILE_OUT;
			}
			else
			{
				open_append_file(&cmds[j], tokens[i + 1].name);
				cmds[j].where_write = FILE_OUT;
			}
			i++;
		}
		else if (cmp(tokens[i].name, "|"))
		{
			if (pipe(cmds[j].pipe) == -1)
				printf("minishell: pipe failed\n");//lacking a decent error message and loop breaking
			if (cmds[j].where_write != FILE_OUT)
				cmds[j].where_write = PIPE_1;
			cmds[j + 1].where_read = PIPE_0;
			j++;
		}
		else
		{
			if (!cmds[j].cmd)
		 		cmds[j].cmd = ft_strdup(tokens[i].name); //mais alocações de memória
			else
			{
				temp = ft_strdup(cmds[j].cmd);
				free(cmds[j].cmd);
				cmds[j].cmd = join_three(temp, " ", tokens[i].name);
				free(temp);
			}
		}
		// {
		// 	if (!cmds[j].cmd[0])
		// 		cmds[j].cmd[0] = ft_strdup(tokens[i].name); //mais alocações de memória
		// 	else if (!cmds[j].cmd[k])
		// 	{
		// 		cmds[j].cmd[k] = ft_strdup(tokens[i].name);//mais alocações 
		// 		cmds[j + 1].cmd[k] = NULL; // isso daqui vai dar mt b.o. de memória
		// 		k++;
		// 	}
		// 	else
		// 		cmds[j].cmd[k] = join_three(cmds[j].args, " ", tokens[i].name);
		i++;
	}
	//free_tokens(ainda n existe a função, tem q criar);
	return(cmds);
}
