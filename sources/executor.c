/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:00:15 by guribeir          #+#    #+#             */
/*   Updated: 2023/02/05 13:03:12 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static void	child(t_cmd *cmds, char **envp, int i)
{
	select_inout(cmds, i);
	full_close(cmds);
	if (is_builtin_fork(cmds[i].cmds))
	{
		g_data.exit_status = builtin_run_fork(cmds[i].cmds);
		exit(g_data.exit_status);
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
	int		status;
	int		i;

	i = 0;
	full_close(cmds);
	status = 0;
	while (cmds[i].cmd)
	{
		waitpid(cmds[i].pid, &status, 0);
		if (WIFEXITED(status))
			g_data.exit_status = WEXITSTATUS(status);
		i++;
	}
	dup2(0, g_data.std_in_fd);
	dup2(1, g_data.std_out_fd);
	return (g_data.exit_status);
}

int	run_builtin_unfork(t_cmd *cmds, char **envp, int i)
{
	if (is_builtin_unfork(cmds[i].cmds))
	{
		g_data.exit_status = builtin_run_unfork(cmds[i].cmds, envp);
		return (1);
	}
	return (0);
}

void	get_pathing(t_cmd *cmds, char **envp, int i)
{
	char	**paths;

	paths = NULL;
	paths = get_paths(envp);
	cmds[i].path_cmd = find_command(cmds[i].cmds[0], paths, -1);
	strsclear(paths);
}

int	core(t_cmd *cmds, char **envp, int exitcode, int i)
{
	while (cmds[++i].cmd)
	{
		if (run_builtin_unfork(cmds, envp, i))
		{
			if (cmds[i + 1].cmd)
				continue ;
			else
				return (g_data.exit_status);
		}
		if (!cmds[i].is_heredoc)
		{
			get_pathing(cmds, envp, i);
			if (!cmds[i].path_cmd && !is_builtin_fork(cmds[i].cmds))
				return (127);
		}
		cmds[i].pid = fork();
		set_execute_signals(cmds[i].pid);
		if (cmds[i].pid == -1)
			return (perror_handler_int("fork", "pid error", 1, cmds));
		else if (cmds[i].pid == 0)
			child(cmds, envp, i);
	}
	exitcode = parent(cmds);
	return (exitcode);
}
