/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 00:01:15 by max               #+#    #+#             */
/*   Updated: 2023/01/27 20:24:53 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
}

void	silent_signal(int sig)
{
	if (sig == SIGQUIT)
	{
	}
	if (sig == SIGINT)
	{
	}
}

void	enable_signals(void)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;

	sig_int.sa_handler = &sigint_handler;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = SIG_IGN;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	halt_signals(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_int.sa_handler = &silent_signal;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = &silent_signal;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_quit, NULL);
}



void	ft_signals(int index)
{
	static struct termios saved_termios;
	static struct termios modified_termios;

	if (index == TRUE)
	{
		tcgetattr(STDIN_FILENO, &saved_termios);
		tcgetattr(STDIN_FILENO, &modified_termios);
		modified_termios.c_lflag &= ~ ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &modified_termios);
	}
	else
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
	}
}
