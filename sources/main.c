/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:13:00 by coder             #+#    #+#             */
/*   Updated: 2022/12/14 21:52:32 by tkomeno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	half_break_free(t_data	*data)
{
	if (data->prompt)
		strsclear(data->prompt);
	if (data->str)
		strclear(&data->str);
	if (data->prompt_name)
		strclear(&data->prompt_name);
	if (data->envp)
		strsclear(data->envp);
}

void	break_free(t_data *data)
{
	half_break_free(data);
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
	(void)envp;
	while (1)
	{
		g_data.cwd = getcwd(NULL, 0);
		g_data.prompt_name = join_three("minishell:~", g_data.cwd, "$ ");
		free(g_data.cwd);
		g_data.str = set_prompt(g_data.prompt_name);
		g_data.envp = set_env(envp);
		// g_data.prompt = ft_split(g_data.str, ' ');
		g_data.prompt = ft_split(g_data.str, ' ');
		if (!g_data.str)
		{
			break_free(&g_data);
			write(1, "\n", 1);
			exit(127);
		}
		executor(g_data.prompt, g_data.envp);
		half_break_free(&g_data);
	}
}
