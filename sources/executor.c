/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:00:15 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/26 19:57:03 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	select_inout(t_cmd *cmds, int i)
{
	if (cmds[i].where_read == FILE_IN)
	{
		if (dup2(cmds[i].fd_in, 0) == -1)
			perror_handler("dup: ", "", 1, cmds);
	}
	if (cmds[i].where_read == PIPE_0)
	{
		if (dup2(cmds[i - 1].pipe[0], 0) == -1)
			perror_handler("dup: ", "", 1, cmds);
	}
	if (cmds[i].where_write == PIPE_1)
	{
		if (dup2(cmds[i].pipe[1], 1) == -1)
			perror_handler("dup: ", "", 1, cmds);
	}
	if (cmds[i].where_write == FILE_OUT)
	{
		if (dup2(cmds[i].fd_out, 1) == -1)
			perror_handler("dup: ", "", 1, cmds);
	}
}

static void	child(t_cmd *cmds, char **envp, int i)
{
	int	ret;

	ret = 0;
	select_inout(cmds, i);
	full_close(cmds);
	if (is_builtin_fork(cmds[i].cmds)) //!(cmp(cmds[i].cmd, " ")) &&
	{
		builtin_run_fork(cmds[i].cmds);
		execve("/usr/bin/true", cmds[i].cmds, envp);
	}
	if (cmds[i].cmds == NULL || cmds[i].path_cmd == NULL)
	{
		perror_handler("", cmds[i].cmds[0], 1, cmds);
		return ;
	}
	if (execve(cmds[i].path_cmd, cmds[i].cmds, envp) == -1)
	{
		perror("minishell: execve");
		return ;
	}	
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
		if (is_builtin_unfork(cmds[i].cmds)) //!(cmp(cmds[i].cmd, " ")) &&
		{
			builtin_run_unfork(cmds[i].cmds, envp);
			i++;
			continue ;
		}
		if (!cmds[i].is_heredoc)
		{
			paths = get_paths(envp);
			cmds[i].path_cmd = find_command(cmds[i].cmds[0], paths, -1);
			strsclear(paths);
			if (!cmds[i].path_cmd && !is_builtin_fork(cmds[i].cmds))
				return (127);
		}
		cmds[i].pid = fork();
		if (cmds[i].pid == -1)
		{
			perror_handler("fork", "pid error", 1, cmds);
			return (1);
		}
		else if (cmds[i].pid == 0)
			child(cmds, envp, i);
		i++;
	}
	exitcode = parent(cmds);
	return (exitcode);
}
