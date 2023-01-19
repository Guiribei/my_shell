/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:40:34 by etachott          #+#    #+#             */
/*   Updated: 2023/01/19 19:02:36 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_global(t_data *d)
{
	d->exit_status = -1;
	d->prompt = NULL;
	d->envp = NULL;
	d->prompt_name = NULL;
	d->cwd = NULL;
	d->str = NULL;
	d->cmd = NULL;
	d->std_in_fd = dup(0);
	d->std_out_fd = dup(1);
}

// void	init_sigaction(t_sigaction *action, void (*handler)(int), int signal)
// {
// 	action.sa_flags = 0;
// 	action.sa_handler = handler;
// 	sigaction(SIGUSR1, &sigact, NULL);
// }