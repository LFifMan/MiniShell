/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:38:47 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/31 14:25:32 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restore_terminal_settings(struct termios original_settings)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_settings);
}

int	main(int ac, char **av, char **ev)
{
	t_vars	vars;
	int		i;

	(void)av;
	(void)ac;
	ft_signals(TRUE);
	enable_signals();
	init_vars(&vars, ev);
	control_tower(&vars);
	i = 0;
	while (vars.envp[i])
	{
		free(vars.envp[i]);
		i++;
	}
	free(vars.envp);
	ft_signals(FALSE);
	halt_signals();
	return (0);
}
