/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:38:47 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/22 16:58:25 by max              ###   ########.fr       */
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

/*
note: 
- if you put fff in the prompt, the program quits for some reason...
- a command like --> echo -o oo "slt cv" "bien et oti?" we we eeee <-- will work perfectly, but if you try random input, a "pointer being freed was not allocated" often appears
*/
int	main(int ac, char **av, char **ev)
{
	t_vars	vars;
	t_shell	*shell;
	t_tabs	*tabs;
	char	*input;

	init_vars(&vars, ev);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (0);
	if (ac != 1 || av[1])
		exit (0); // TODO : add error
	while (1)
	{
		input = readline("salut lulu> ");
		if (ft_strcmp(input, "exit") == TRUE)
			break ;
		add_history(input);
		if (parsing_input(&shell, input) == FALSE)
			printf("error: quote not finished\n");
		
		shell = parsing_not_quotation(&shell);
		shell = ft_get_da_pipes(&shell);
		
		
		shell = ft_redirections(&shell);
		ft_dollars(&shell, &vars);
		//PRINT_SHELL(&shell);

		if (ft_check_op(shell) == FALSE)
			free_lst(shell);
		shell = ft_space_redop(&shell);

		tabs = ft_regroup(&shell, &vars);
		ft_parsing_redop(&tabs);
		ft_parsing_paths(vars, &tabs);
		PRINT_CMDS(&tabs);
		ft_pipex(tabs, &vars);
		free_lst(shell);

		free(input);
		free_lst_tabs(tabs);
	}
	//rl_clear_history();
	return (0);
}
