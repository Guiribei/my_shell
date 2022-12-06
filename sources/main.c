/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:13:00 by coder             #+#    #+#             */
/*   Updated: 2022/12/06 20:33:52 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char				**prompt;
	struct sigaction	act;
	struct sigaction	act_2;
	t_list				*env;
	char				*str;

	if (argc == 0 || !argv[0])
		return (1);
	set_signals(&act, &act_2);
	env = set_env(envp);
	while (1)
	{
		str = set_prompt("minishell$ ");
		if (str == NULL)
			break;
		prompt = ft_split(str, ' ');
		if (!prompt)
		{
			//ft_lstclear(&env, free);
			free(prompt);
			write(1, "\n", 1);
			exit(127);
		}
		executor(prompt, env);
		free(prompt);
	}
	free(prompt);
}
