/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:40:34 by etachott          #+#    #+#             */
/*   Updated: 2022/12/14 15:43:59 by etachott         ###   ########.fr       */
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
}
