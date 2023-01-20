/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:00:15 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/20 18:32:28 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data g_data;

void	select_inout(t_cmd *cmds, int i)
{
	if (cmds[i].where_read == FILE_IN)
	{
		if(dup2(cmds[i].fd_in, 0) == -1)
			printf("dup failed\n");
	}
	if (cmds[i].where_read == PIPE_0)
	{
		if(dup2(cmds[i - 1].pipe[0], 0) == -1)
			printf("dup failed\n");
	}
	if (cmds[i].where_write == PIPE_1)
	{
		if(dup2(cmds[i].pipe[1], 1) == -1)
			printf("dup failed\n");
	}
	if (cmds[i].where_write == FILE_OUT)
	{
		if(dup2(cmds[i].fd_out, 1) == -1)
			printf("dup failed\n");
	}
}

static void	child(t_cmd *cmds, char **envp, int i)
{
	select_inout(cmds, i);
	full_close(cmds);
	if (cmds[i].cmds == NULL || cmds[i].path_cmd == NULL)
		printf("Command not found, child\n");
	if (execve(cmds[i].path_cmd, cmds[i].cmds, envp) == -1)
		printf("faild execve");
}

static int	parent(t_cmd *cmds)
{
	pid_t	pid;
	int		status;
	int		exitcode;
	int		i;

	i = 0;
	full_close(cmds);
	exitcode = 1;
	status = 0;
	while (cmds[i].cmd)
	{
		pid = waitpid(cmds[i].pid, &status, 0);
		if (WIFEXITED(status))
			exitcode = WEXITSTATUS(status);
		i++;
	}
	dup2(0, g_data.std_in_fd);
	dup2(1, g_data.std_out_fd);
	return (exitcode);
}

int	core(t_cmd *cmds, char **envp)
{
	int		exitcode;
	int		i;
	char	**paths;
	
	i = 0;
	while (cmds[i].cmd)
	{
		if (is_builtin(cmds[i].cmds))
		{
			builtin_run(cmds[i].cmds, envp);
			i++;
			continue ;
		}
		paths = get_paths(envp);
		cmds[i].path_cmd = find_command(cmds[i].cmds[0], paths);
		strsclear(paths);
		if (!cmds[i].path_cmd)
		{
			printf("%s: Command not found\n", cmds[i].cmds[0]);
			return (127);
		}
		cmds[i].pid = fork();
		if (cmds[i].pid == -1)
		{
			printf("minishell: fork: pid not found\n");
			return (1);
		}
		else if (cmds[i].pid == 0)
			child(cmds, envp, i);
		i++;
	}
	exitcode = parent(cmds);
	return (exitcode);
}