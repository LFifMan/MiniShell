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

int	main(int ac, char **av, char **ev)
{
	t_vars	vars;

	(void)av;
	if (ac != 1)
	{
		write(2, "Too many arguments\n", 19);
		write(2, "Run only the minishell program by itself\n", 41);
		exit (1);
	}
	ft_signals(TRUE);
	init_vars(&vars, ev);
	control_tower(&vars);
	ft_free_vars(vars);
	ft_signals(FALSE);
	return (0);
}
