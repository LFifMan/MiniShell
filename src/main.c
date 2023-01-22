/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:38:47 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/22 22:50:14 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
init_vars is our initiation function. for now we only init the shell env for the prompt name
*/
void	init_vars(t_vars *vars, char **envp)
{
	int		envp_length;
	int		i;
	char	**new_envp;
	
	envp_length = 0;
	i = 0;
	while (envp[envp_length])
	{
		envp_length++;
	}
	new_envp = malloc(sizeof(char *) * (envp_length + 1));
	while (i < envp_length)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[envp_length] = 0;
	vars->envp = new_envp;
}

char	*ft_prompt(char *input)
{
	input = readline("> ");
	if (ft_strcmp(input, "exit") == TRUE)
		return (NULL);
	add_history(input);
	return (input);
}

int	control_parsing(t_shell **shell, t_vars *vars, char *input)
{
	if (parsing_quotations(shell, input) == FALSE) //quotations
	{
		printf("error: quote not finished\n");
		return (FALSE);
	}
	(*shell) = parsing_spaces(shell);
	(*shell) = parsing_pipes(shell);
	
	(*shell) = parsing_redops(shell); //redops
	parsing_dollars(shell, vars); //variable substition
	if (ft_check_op(*shell) == FALSE)
		return (FALSE);
	(*shell) = ft_space_redops(shell);
	//PRINT_SHELL(&shell);
	free(input);
	return (TRUE);

}

int	control_commands(t_tabs **tabs, t_shell **shell, t_vars *vars)
{
	*tabs = ft_regroup(shell, vars);
	ft_redops(tabs);
	ft_paths(*vars, tabs);
	free_lst(*shell);

	//PRINT_CMDS(&tabs);

	return (TRUE);
}

int	check_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != SPACE)
			return (FALSE);
		i++;
	}
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
		input = readline("> ");
		if (ft_strcmp(input, "exit") == TRUE)
			break ;
		add_history(input);
		if (check_only_spaces(input) == TRUE)
			free(input);
		else
		{
			if (control_parsing(&shell, vars, input) == FALSE)
			{
				free_lst(shell);
				free(input);
			}
			if (control_commands(&tabs, &shell, vars) == FALSE)
			{
				free_lst(shell);
				free_lst_tabs(tabs);
			}

			ft_pipex(tabs, vars);
			ft_unset_export(tabs, vars, tabs->next->cmds[0]);
			free_lst(shell);
			free_lst_tabs(tabs);
		}
	}
	//rl_clear_history();
}

int	main(int ac, char **av, char **ev)
{
	t_vars	vars;

	if (ac != 1 || av[1])
		exit (0); // TODO : add error
	init_vars(&vars, ev);
	control_tower(&vars);
	//ft_free_struct(vars);
	return (0);
}
