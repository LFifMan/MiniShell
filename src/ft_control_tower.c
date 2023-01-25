/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_tower.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:27:44 by max               #+#    #+#             */
/*   Updated: 2023/01/25 14:04:02 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_prompt(char **input)
{
	*input = readline("> ");
	if (input == 0 || ft_strcmp(*input, "exit") == TRUE)
	{
		free(input);
		return (0);
	}
	add_history(*input);
	return (*input);
}

int	control_parsing(t_shell **shell, t_vars *vars, char *input)
{
	if (parsing_quotations(shell, input) == FALSE)
	{
		printf("error: quote not finished\n");
		free_shell(*shell);
		return (FALSE);
	}
	(*shell) = parsing_spaces(shell);
	(*shell) = parsing_pipes(shell);
	(*shell) = parsing_redops(shell);
	parsing_dollars(shell, vars);
	(*shell) = parsing_spaces(shell);
	if (ft_check_op(*shell) == FALSE)
	{
		free_shell(*shell);
		return (FALSE);
	}
	(*shell) = ft_space_redops(shell);
	free(input);

	return (TRUE);
}

int	control_commands(t_tabs **tabs, t_shell **shell, t_vars *vars)
{
	printf("\n\n IN CONTROL COMMANDS BEFORE REGROUP \n");
	PRINT_SHELL(shell);

	*tabs = ft_regroup(shell, vars);
	printf("\n\n END OF CONTROL COMMANDS RIGHT AFTER REGROUP  TMTC\n");
	PRINT_SHELL(shell);
	PRINT_CMDS(tabs);
	ft_redops(tabs);
	ft_paths(*vars, tabs);
	//PRINT_SHELL(shell);
	//free_shell(*shell);

	return (TRUE);
}

void	control_tower(t_vars *vars)
{
	t_shell	*shell;
	t_tabs	*tabs;
	char	*input;

	input = 0;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return ;
	while (1)
	{
		if (!ft_prompt(&input))
			break ;
		if (check_only_spaces(input) == TRUE)
			free(input);
		else
		{
			if (control_parsing(&shell, vars, input) == FALSE)
			{
				free_shell(shell);
				free(input);
			}
			else if (control_commands(&tabs, &shell, vars) == FALSE)
			{
				free_shell(shell);
				free_tabs(tabs);
				free(tabs);
			}
			else
			{
				//printf("\n\nELSE COMMANDS \n");
				// PRINT_SHELL(&shell);
				// PRINT_CMDS(&tabs);
				ft_pipex(tabs, vars);
				ft_unset_export(tabs, vars, tabs->next->cmds[0]);
				// printf("\n\nELSE COMMANDS AFTER PIPE\n");
				// PRINT_SHELL(&shell);
				// PRINT_CMDS(&tabs);
				free_shell(shell);
				free_tabs(tabs);
				free(tabs);
				//	printf("leaks regroup 1 %p next %p\n", tabs, tabs->next);
			}
		}
	}
	//rl_clear_history();
}
