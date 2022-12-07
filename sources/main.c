/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:13:00 by coder             #+#    #+#             */
/*   Updated: 2022/12/07 19:47:28 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	half_break_free(char**prompt, char *str, char **my_env)
{
	if (prompt)
		strsclear(prompt);
	if (str)
		strclear(&str);
	if (my_env)
		strsclear(my_env);
}

void	break_free(char **prompt, char *str, char **my_env, t_list **env)
{
	printf("saiu\n");
	half_break_free(prompt, str, my_env);
	if (env)
		ft_envfree(env);
}

int	main(int argc, char *argv[], char *envp[])
{
	char				**prompt;
	struct sigaction	act;
	struct sigaction	act_2;
	t_list				*env;
	char				*str;
	char				**my_env;

	(void)envp;
	if (argc == 0 || !argv[0])
		return (1);
	set_signals(&act, &act_2);
	env = set_env(envp);
	while (1)
	{
		str = set_prompt("minishell$ ");
		my_env = recreate_envp(env);
		prompt = ft_split(str, ' ');
		if (!str)
		{
			printf("STRING = %s\n", str);
			break_free(prompt, str, my_env, &env);
			write(1, "\n", 1);
			exit(127);
		}
		prompt = ft_split(str, ' ');
		half_break_free(prompt, str, my_env);
	}
}
