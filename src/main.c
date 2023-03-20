/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:38:47 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/20 18:01:16 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **ev)
{
	t_var	var;

	(void)av;
	if (ac != 1)
	{
		write(2, "Too many arguments\n", 19);
		write(2, "Run the minishell program by itself\n", 36);
		exit (1);
	}
	ft_signals(TRUE);
	ft_init_var(&var, ev);
	ft_ctrl_twr(&var);
	ft_free_var(var);
	ft_signals(FALSE);
	return (42);
}
