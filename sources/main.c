/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:13:00 by coder             #+#    #+#             */
/*   Updated: 2023/01/24 18:32:02 by guribeir         ###   ########.fr       */
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

void	free_tokens(t_token *tokens)
{
	int	index;

	index = 0;
	while (tokens[index].name)
	{
		free(tokens[index].name);
		index++;
	}
	free(tokens);
}

void	half_break_free(t_data	*data)
{
	if (data->prompt)
		strsclear(data->prompt);
	if (data->str)
		strclear(&data->str);
	if (data->prompt_name)
		strclear(&data->prompt_name);
}

void	break_free(t_data *data)
{
	if (data)
		half_break_free(data);
	if (data->envp)
		strsclear(data->envp);
	rl_clear_history();
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
		g_data.envp = change_exit_status(g_data.envp, g_data.exit_status);
		g_data.cwd = getcwd(NULL, 0);
		g_data.prompt_name = join_three("\x1b[32mminishell:~\033[0m",
				g_data.cwd, "\x1b[32m$ \033[0m");
		free(g_data.cwd);
		g_data.str = set_prompt(g_data.prompt_name);
		if (!g_data.str)
		{
			break_free(&g_data);
			write(1, "\n", 1);
			exit(127);
		}
		if (is_expansible(g_data.str))
			g_data.str = expand_str(g_data.str);
		g_data.tokens = tokenize(g_data.str);
		if (check_syntax(g_data.tokens, 0, 0) != -1)
		{
			g_data.cmds = init_cmd_table(g_data.tokens);
			if (g_data.cmds)
			{
				split_cmds(g_data.cmds);
				g_data.exit_status = core(g_data.cmds, g_data.envp);
				free_cmds(g_data.cmds);
			}
		}
		free_tokens(g_data.tokens);
		half_break_free(&g_data);
	}
}
