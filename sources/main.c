/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:13:00 by coder             #+#    #+#             */
/*   Updated: 2023/01/27 21:09:48 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	free_cmds(t_cmd *cmds)
{
	int	index;

	index = 0;
	while (cmds[index].cmd)
		index++;
	while (index >= 0)
	{
		free(cmds[index].cmd);
		free(cmds[index].path_cmd);
		strsclear(cmds[index].cmds);
		index--;
	}
	free(cmds);
}

static void	get_str(void)
{
	g_data.envp = change_exit_status(g_data.envp, g_data.exit_status);
	g_data.cwd = getcwd(NULL, 0);
	g_data.prompt_name = join_three("\x1b[32mminishell:~\033[0m",
			g_data.cwd, "\x1b[32m$ \033[0m");
	free(g_data.cwd);
	g_data.str = set_prompt(g_data.prompt_name);
}

static void	parse_and_execute(void)
{
	g_data.cmds = init_cmd_table(g_data.tokens);
	if (g_data.cmds)
	{
		split_cmds(g_data.cmds);
		g_data.exit_status = core(g_data.cmds, g_data.envp, 0, -1);
		free_cmds(g_data.cmds);
	}
}

static void	syntax_right_execute(void)
{
	if (check_syntax(g_data.tokens, 0, 0) != -1)
		parse_and_execute();
	free_tokens(g_data.tokens);
}

int	main(int argc, char *argv[], char *envp[])
{
	struct sigaction	act;
	struct sigaction	act_2;

	if (argc == 0 || !argv[0])
		return (1);
	set_signals(&act, &act_2);
	init_global(&g_data);
	g_data.envp = set_env(envp);
	while (1)
	{
		get_str();
		if (!g_data.str)
		{
			break_free(&g_data);
			write(1, "\n", 1);
			exit(127);
		}
		expand_variables(&g_data.str);
		g_data.tokens = tokenize(g_data.str);
		if (g_data.tokens)
			syntax_right_execute();
		half_break_free(&g_data);
	}
}
