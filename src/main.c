/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:38:47 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/18 15:41:15 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
init_vars is our initiation function. for now we only init the shell env for the prompt name
*/
void	init_vars(t_vars *vars, char **ev)
{
	vars->env_shell = ft_parsing_sh(ev);
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
	char	*input;

	if (ac != 1 || av[1])
		exit (0); // add error 
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (0);
	ft_lstsize(&shell);
	init_vars(&vars, ev);
	while (1)
	{
		input = readline(vars.env_shell);
		if (ft_strcmp(input, "exit") == TRUE)
			break ;
		add_history(input);
		if (parsing_input(&shell, input) == 1) // split input in chunks of quotes / unquotes
			printf(" error: quote not finished\n");
		shell = parsing_not_quotation(&shell); // split all chunks of unquotes, creates a new lst
		printed(&shell); // to check the data of the lst. 
		printf(" size %d \n", ft_lstsize(&shell)); // to check the size of the lst

		printf("You entered: %s\n", input);
		free(input);
		free_lst(shell);
		printed(&shell);

	}
	//rl_clear_history();
	return (0);
}


