/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:13:00 by coder             #+#    #+#             */
/*   Updated: 2023/01/17 17:19:48 by guribeir         ###   ########.fr       */
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
}

void	break_free(t_data *data)
{
	half_break_free(data);
	if (data->envp)
		strsclear(data->envp);
	rl_clear_history();
}



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
	while(tokens[index].name)
	{
		free(tokens[index].name);
		index++;
	}
	free(tokens);
}

//TO DEBUG: TOKENIZER FILLING PROCESS
// int main(int argc, char **argv, char **envp)
// {
// 	t_token *tokens;
// 	t_cmd	*cmds;
// 	char 	*line;
// 	int		exitcode;

// 	(void) argc; (void) argv;
// 	line = ft_strdup("< infile grep \"Brasil\" | wc -w >> outfile");
// 	tokens = tokenize(line);
// 	check_syntax(tokens);
// 	cmds = init_cmd_table(tokens);
// 	split_cmds(cmds);
// 	exitcode = core(cmds, envp);
// 	free_cmds(cmds);
// 	free_tokens(tokens);
// 	free(line);
// 	(void)tokens;
// }

int	main(int argc, char *argv[], char *envp[])
{
	struct sigaction	act;
	struct sigaction	act_2;
	t_token *tokens;
	t_cmd	*cmds;
	int		exitcode;

	if (argc == 0 || !argv[0])
		return (1);
	set_signals(&act, &act_2);
	init_global(&g_data);
	g_data.envp = set_env(envp);
	while (1)
	{
		g_data.cwd = getcwd(NULL, 0);
		g_data.prompt_name = join_three("minishell:~", g_data.cwd, "$ ");
		free(g_data.cwd);
		g_data.str = set_prompt(g_data.prompt_name);
		if (is_expansible(g_data.str))
			g_data.str = expand_str(g_data.str);
		if (!g_data.str)
		{
			break_free(&g_data);
			write(1, "\n", 1);
			exit(127);
		}
		tokens = tokenize(g_data.str);
		check_syntax(tokens);
		cmds = init_cmd_table(tokens);
		split_cmds(cmds);
		exitcode = core(cmds, envp);
		free_cmds(cmds);
		free_tokens(tokens);
		half_break_free(&g_data);
	}
}