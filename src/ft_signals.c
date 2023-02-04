/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 00:01:15 by max               #+#    #+#             */
/*   Updated: 2023/01/31 17:31:23 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
	g_status = 1;
}

void	ft_block_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
	}
	if (sig == SIGQUIT)
	{
		g_status = 131;
	}
}

void	ft_enable_signal(void)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;

	sig_int.sa_handler = &ft_sigint_handler;
//	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = SIG_IGN;
//	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	ft_halt_signal(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_int.sa_handler = &ft_block_signal;
//	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = &ft_block_signal;
//	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	ft_signals(int index)
{
	static struct termios	saved_termios;
	static struct termios	modified_termios;

	if (index == TRUE)
	{
		ft_enable_signal();
		tcgetattr(STDIN_FILENO, &saved_termios);
		tcgetattr(STDIN_FILENO, &modified_termios);
		modified_termios.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &modified_termios);
	}
	else
	{
		ft_halt_signal();
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
	}
}
