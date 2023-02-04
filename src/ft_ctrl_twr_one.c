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

int	ft_ctrl_prs(t_shell **shell, t_vars *vars, char *input, t_tabs *tabs)
{
	if (parsing_quotations(shell, input) == FALSE)
	{
		write (2, "minishell: error: quote not finished\n", 37);
		g_status = 1;
		ft_free_lst(*shell, tabs, input, 1);
		return (FALSE);
	}
	(*shell) = parsing_spaces(shell);
	(*shell) = parsing_pipes(shell);
	(*shell) = parsing_redops(shell);
	parsing_dollars(shell, vars);
	(*shell) = parsing_spaces(shell);
	if (ft_check_op(*shell) == FALSE)
	{
		ft_free_lst(*shell, tabs, input, 1);
		return (FALSE);
	}
	(*shell) = ft_space_redops(shell);
	return (TRUE);
}

int	ft_ctrl_cmd(t_tabs **tabs, t_shell **shell, t_vars *vars)
{
	*tabs = ft_regroup(shell, vars);
	ft_redops(tabs);
	ft_paths(*vars, tabs);
	return (TRUE);
}

void	ft_ctrl_twr(t_vars *vars)
{
	t_shell	*shell;
	t_tabs	*tabs;
	char	*input;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit (EXIT_FAILURE);
	shell->next = NULL;
	while (1)
	{
		input = ft_prompt();
		if (check_only_spaces(input) == TRUE)
			ft_free_lst(shell, tabs, input, 0);
		else
		{
			if (ft_ctrl_prs(&shell, vars, input, tabs) == TRUE)
			{
				ft_ctrl_cmd(&tabs, &shell, vars);
				ft_execution(tabs, vars);
				ft_free_lst(shell, tabs, input, 2);
			}
		}
		ft_signals(TRUE);
		vars->tmp_g = g_status;
	}
}

