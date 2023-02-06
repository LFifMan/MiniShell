/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_ctrl_twr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:27:44 by max               #+#    #+#             */
/*   Updated: 2023/02/03 16:18:56 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_prompt(void)
{
	char	*input;

	g_status = 0;
	input = readline("> ");
	if (input == 0)
	{
		printf("\033[1A\033[3Cexit\n");
		exit(0);
	}
	if (ft_build_exit(input) == TRUE)
	{
		exit(0);
	}
	add_history(input);
	ft_signals(FALSE);
	return (input);
}

int	ft_execution(t_tabs *tabs, t_var *var)
{
	ft_pipex(tabs, var);
	ft_unset_export(tabs, var, tabs->next->cmds[0]);
	return (TRUE);
}
