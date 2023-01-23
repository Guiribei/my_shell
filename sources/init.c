/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:40:34 by etachott          #+#    #+#             */
/*   Updated: 2023/01/23 13:31:05 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_global(t_data *d)
{
	// d->prompt = NULL;
	// d->envp = NULL;
	// d->prompt_name = NULL;
	// d->cwd = NULL;
	// d->str = NULL;
	// d->cmd = NULL;
	// d->tokens = NULL;
	// d->cmds = NULL;
	ft_bzero(d, 1);
	d->exit_status = -1;
	d->std_out_fd = dup(1);
	d->std_in_fd = dup(0);
}

// void	init_sigaction(t_sigaction *action, void (*handler)(int), int signal)
// {
// 	action.sa_flags = 0;
// 	action.sa_handler = handler;
// 	sigaction(SIGUSR1, &sigact, NULL);
// }