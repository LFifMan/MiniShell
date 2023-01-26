/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 00:01:15 by max               #+#    #+#             */
/*   Updated: 2023/01/26 13:21:44 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	disable_sigint_display(struct termios original_settings)
{
	struct termios	t;

	t = original_settings;
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
}

void	ft_signals(struct termios original_settings)
{
	disable_sigint_display(original_settings);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
