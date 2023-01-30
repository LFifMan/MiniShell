/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_tower.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:27:44 by max               #+#    #+#             */
/*   Updated: 2023/01/30 19:15:46 by mstockli         ###   ########.fr       */
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
		//atoi(&input[5])
		exit(atoi(&input[5])); //TODO ft_atoi
	}
	else
		return (FALSE);
	return (TRUE);
}

char	*ft_prompt(void)
{
	char	*input;

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
	return (input);
}

int	control_parsing(t_shell **shell, t_vars *vars, char *input)
{
	if (parsing_quotations(shell, input) == FALSE)
	{
		write (2, "minishell: error: quote not finished\n", ft_strlen("minishell: error: quote not finished\n"));
		return (FALSE);
	}
	(*shell) = parsing_spaces(shell);
	(*shell) = parsing_pipes(shell);
	(*shell) = parsing_redops(shell);
	parsing_dollars(shell, vars);
	(*shell) = parsing_spaces(shell);
	if (ft_check_op(*shell) == FALSE)
	{
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
		return ;
	shell->next = NULL;
	while (1)
	{
		input = ft_prompt();
		halt_signals();
		ft_signals(FALSE);
		if (check_only_spaces(input) == TRUE)
			free_lsts(shell, tabs, input, 0);
		else
		{
			if (control_parsing(&shell, vars, input) == FALSE)
				free_lsts(shell, tabs, input, 1);
			else if (control_commands(&tabs, &shell, vars) == FALSE)
				free_lsts(shell, tabs, input, 2);
			else if (control_execution(tabs, vars) == TRUE)
				free_lsts(shell, tabs, input, 2);
		}
		ft_signals(TRUE);
		enable_signals();
	}
	rl_clear_history();
}
