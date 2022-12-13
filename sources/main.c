/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:13:00 by coder             #+#    #+#             */
/*   Updated: 2022/12/13 23:19:44 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	half_break_free(char **prompt, char *str, char **my_env, char *name)
{
	if (prompt)
		strsclear(prompt);
	if (str)
		strclear(&str);
	if (my_env)
		strsclear(my_env);
	if (name)
		strclear(&name);
}

static void	break_free(char **prompt, char *str, char **my_env, t_list **env, char *name)
{
	half_break_free(prompt, str, my_env, name);
	if (env)
		ft_envfree(env);
	rl_clear_history();
}

int	main(int argc, char *argv[], char *envp[])
{
	char				**prompt;
	struct sigaction	act;
	struct sigaction	act_2;
	t_list				*env;
	char				*str;
	char				**my_env;
	char				*name;
	char				*cwd;

	str = NULL;
	if (argc == 0 || !argv[0])
		return (1);
	set_signals(&act, &act_2);
	env = set_env(envp);
	while (1)
	{
		cwd = getcwd(NULL, 0);
		name = join_three("minishell:~", cwd, "$ ");
		free(cwd);
		str = set_prompt(name);
		my_env = recreate_envp(env);
		prompt = ft_split(str, ' ');
		if (!str)
		{
			break_free(prompt, str, my_env, &env, name);
			write(1, "\n", 1);
			exit(127);
		}
		executor(prompt, env, my_env);
		half_break_free(prompt, str, my_env, name);
	}
}
