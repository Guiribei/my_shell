/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:00:15 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/17 17:23:42 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void change_inout(t_cmd *cmd)
{
	if(dup2(cmd->fd_in, 0) == -1)
		printf("dup failed\n");
	if(dup2(cmd->fd_out, 1) == -1)
		printf("dup failed\n");
}

static void	child(t_cmd *cmd, char **envp)
{
	count_cmds();
	change_inout(cmd);
	//full_close(cmd);
	if (cmd->cmds == NULL || cmd->path_cmd == NULL)
		printf("Command not found, child\n");
	if (execve(cmd->path_cmd, cmd->cmds, envp) == -1)
		printf("faild execve");
}

static int	parent(t_cmd *cmds)
{
	pid_t	pid;
	int		status;
	int		exitcode;
	int		i;

	//full_close();
	exitcode = 1;
	i = 0;
	while (cmds[i].cmd)
	{
		pid = waitpid(cmds[i].pid, &status, 0);
		if (WIFEXITED(status))
			exitcode = WEXITSTATUS(status);
		i++;
	}
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
		paths = get_paths(envp);
		cmds[i].path_cmd = find_command(cmds[i].cmds[0], paths);
		strsclear(paths);
		if (!cmds[i].path_cmd)
		{
			printf("%s: Command not found\n", cmds[i].cmds[0]);
			return (127);
		}
		printf("FD_IN: %d\t FD_OUT: %d\t\n", cmds[i].fd_in, cmds[i].fd_out);
		cmds[i].pid = fork();
		if (cmds[i].pid == -1)
		{
			printf("minishell: fork: pid not found\n");
			return (1);
		}
		else if (cmds[i].pid == 0)
			child(&cmds[i], envp);
		i++;
	}
	exitcode = parent(cmds);
	return (exitcode);
}