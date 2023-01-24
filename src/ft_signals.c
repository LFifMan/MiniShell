/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 00:01:15 by max               #+#    #+#             */
/*   Updated: 2023/01/23 00:01:24 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//void	sigquit_handler(int sig)
//{
//	(void)sig;
//	exit (0);
//}

void	sigint_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void	disable_sigint_display(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &original_settings);
	t = original_settings;
	t.c_lflag &= ~ECHOCTL;
//	t.c_cc[VQUIT] = 4;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
}

void	ft_signals(void)
{
	disable_sigint_display();
	signal(SIGINT, sigint_handler);
}
