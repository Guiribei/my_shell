/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:57:34 by coder             #+#    #+#             */
/*   Updated: 2023/01/24 16:23:00 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals(struct sigaction *s_sigint, struct sigaction *s_sigquit)
{
	s_sigint->sa_handler = &sig_handler;
	s_sigint->sa_flags = 0;
	sigemptyset(&s_sigint->sa_mask);
	sigaction(SIGINT, s_sigint, NULL);
	s_sigquit->sa_handler = SIG_IGN;
	s_sigquit->sa_flags = 0;
	sigemptyset(&s_sigquit->sa_mask);
	sigaction(SIGQUIT, s_sigquit, NULL);
}

void	set_execute_signals(int child_pid)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (child_pid == 0)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	define_heredoc_signals(int child_pid)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_flags = 0;
	sigemptyset(&sa_sigint.sa_mask);
	if (child_pid == 0)
		sa_sigint.sa_handler = SIG_DFL;
	else
		sa_sigint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_flags = 0;
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}
