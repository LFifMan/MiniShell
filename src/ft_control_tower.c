/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_tower.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:27:44 by max               #+#    #+#             */
/*   Updated: 2023/02/03 16:18:56 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	build_exit(char *input)
{
	int	i;

	if (ft_strcmp(input, "exit") == TRUE)
	{
		return (TRUE);
	}
	if (ft_strncmp(input, "exit ", 5) == TRUE)
	{
		i = 5;
		while (input[i])
		{
			if (input[i] > '9' || input[i] < '0' )
				return (FALSE);
			i++;
		}
		exit(atoi(&input[5]) % 256); //TODO ft_atoi
	}
	else
		return (FALSE);
	return (TRUE);
}

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
	if (build_exit(input) == TRUE)
	{
		exit(0);
	}
	add_history(input);
	ft_signals(FALSE);
	return (input);
}

int	control_parsing(t_shell **shell, t_vars *vars, char *input, t_tabs *tabs)
{
	if (parsing_quotations(shell, input) == FALSE)
	{
		write (2, "minishell: error: quote not finished\n", 37);
		g_status = 1;
		free_lsts(*shell, tabs, input, 1);
		return (FALSE);
	}
	(*shell) = parsing_spaces(shell);
	(*shell) = parsing_pipes(shell);
	(*shell) = parsing_redops(shell);
	parsing_dollars(shell, vars);
	(*shell) = parsing_spaces(shell);
	if (ft_check_op(*shell) == FALSE)
	{
		free_lsts(*shell, tabs, input, 1);
		return (FALSE);
	}
	(*shell) = ft_space_redops(shell);
	return (TRUE);
}

int	control_commands(t_tabs **tabs, t_shell **shell, t_vars *vars)
{
	*tabs = ft_regroup(shell, vars);
	ft_redops(tabs);
	ft_paths(*vars, tabs);
	return (TRUE);
}

int	control_execution(t_tabs *tabs, t_vars *vars)
{
	ft_pipex(tabs, vars);
	ft_unset_export(tabs, vars, tabs->next->cmds[0]);
	return (TRUE);
}

void	control_tower(t_vars *vars)
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
			free_lsts(shell, tabs, input, 0);
		else
		{
			if (control_parsing(&shell, vars, input, tabs) == TRUE)
			{
				control_commands(&tabs, &shell, vars);
				control_execution(tabs, vars);
				free_lsts(shell, tabs, input, 2);
			}
		}
		ft_signals(TRUE);
		vars->tmp_g = g_status;
	}
}
