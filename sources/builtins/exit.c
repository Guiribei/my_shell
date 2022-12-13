/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomeno <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:48:47 by tkomeno           #+#    #+#             */
/*   Updated: 2022/12/13 20:00:43 by tkomeno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_exit(char **args, t_list **env)
{
	(void)args;
	rl_clear_history();
	ft_envfree(env);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	//TODO: close all file descriptors
	exit(0);
}
