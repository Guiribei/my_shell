/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:57:34 by coder             #+#    #+#             */
/*   Updated: 2022/12/06 19:15:42 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	suspend_sigquit(void)
// {
// 	struct sigaction	act;
	
// 	ft_memset(&act, 0, sizeof(act));
// 	act.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &act, NULL);
// }

void	sig_handler(int	sig)
{
	(void)sig;
	write(1,"\n",1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();

}

void	set_signals(struct sigaction *act, struct sigaction *act_2)
{
	act->sa_handler = &sig_handler;
	act_2->sa_handler = SIG_IGN;
	sigaction(SIGINT, act, NULL);
	sigaction(SIGQUIT, act_2, NULL);
	sigaction(SIGTSTP, act_2, NULL);
}
