/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:13:00 by coder             #+#    #+#             */
/*   Updated: 2022/12/28 23:38:55 by guribeir         ###   ########.fr       */
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

// int	main(int argc, char *argv[], char *envp[])
// {
// 	struct sigaction	act;
// 	struct sigaction	act_2;

// 	if (argc == 0 || !argv[0])
// 		return (1);
// 	set_signals(&act, &act_2);
// 	init_global(&g_data);
// 	g_data.envp = set_env(envp);
// 	while (1)
// 	{
// 		g_data.cwd = getcwd(NULL, 0);
// 		g_data.prompt_name = join_three("minishell:~", g_data.cwd, "$ ");
// 		free(g_data.cwd);
// 		g_data.str = set_prompt(g_data.prompt_name);
// 		if (is_expansible(g_data.str))
// 			g_data.str = expand_str(g_data.str);
// 		// g_data.prompt = ft_split(g_data.str, ' ');
// 		g_data.prompt = ft_split(g_data.str, ' ');
// 		if (!g_data.str)
// 		{
// 			break_free(&g_data);
// 			write(1, "\n", 1);
// 			exit(127);
// 		}
// 		executor(g_data.prompt, g_data.envp);
// 		half_break_free(&g_data);
// 	}
// }


//TO DEBUG: TOKENIZER FILLING PROCESS
int main(void)
{
	int i;
	t_token *tokens;
	t_cmd	*cmds;

	i = 0;
	char *line;
	line = ft_strdup("< infile echo \"Hello World\" | wc -w >> outfile");
	tokens = tokenize(line);
	check_syntax(tokens);
	cmds = init_cmd_table(tokens);
	while (cmds[i].name)
	{
		printf("O token atual ??: \n%s %s\ninfile: %d\noutfile: %d\n\n", cmds[i].name, cmds[i].args, cmds[i].fd_in, cmds[i].fd_out);
		i++;
	}
	(void)tokens;
}
