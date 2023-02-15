/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott <etachott@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:13:00 by coder             #+#    #+#             */
/*   Updated: 2023/02/15 16:12:02 by etachott         ###   ########.fr       */
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
		if (g_data.error_flag == 1)
			g_data.exit_status = 1;
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
	struct sigaction	s_sigint;
	struct sigaction	s_sigquit;

	if (argc == 0 || !argv[0])
		return (1);
	init_global(&g_data);
	g_data.envp = set_env(envp);
	g_data.fenvp = set_env(envp);
	while (1)
	{
		set_signals(&s_sigint, &s_sigquit);
		get_str();
		if (!g_data.str)
		{
			break_free(&g_data);
			write(1, "\n", 1);
			exit(g_data.exit_status);
		}
		expand_variables(&g_data.str);
		g_data.tokens = tokenize(g_data.str);
		if (g_data.tokens)
			syntax_right_execute();
		half_break_free(&g_data);
	}
}
