/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:38:47 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/20 03:45:33 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
init_vars is our initiation function. for now we only init the shell env for the prompt name
*/
void	init_vars(t_vars *vars, char **ev)
{
	vars->env_shell = ft_parsing_sh(ev);
	vars->env_pwd = ft_parsing_pwd(ev);
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
	t_tabs  *tabs;
	char	*input;

	vars.envp = ev;
	if (ac != 1 || av[1])
		exit (0); // TODO : add error
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (0);
	ft_lstsize(&shell);
	while (1)
	{
		init_vars(&vars, ev);
		input = readline("> ");
		if (ft_strcmp(input, "exit") == TRUE)
			break ;
		add_history(input);
		if (parsing_input(&shell, input) == FALSE)
			printf(" error: quote not finished\n");
		shell = parsing_not_quotation(&shell);
		shell = ft_get_da_pipes(&shell);
		ft_dollars(&shell, &vars);
		tabs = ft_regroup(&shell, &vars);

		ft_parsing_paths(vars, &tabs);

		ft_print_lst(&shell);
		ft_print_tabs_cmds(&tabs);
		ft_print_tabs_paths(&tabs);
		
		ft_pipex(tabs, vars);


		printf("You entered: %s\n", input);
		free(input);
		free_lst(shell);
		free_lst_tabs(tabs);
	}
	//rl_clear_history();
	return (0);
}


