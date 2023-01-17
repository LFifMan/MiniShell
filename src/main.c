/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:38:47 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/17 14:38:47 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	ft_strcmp(char *input, char *str)
{
	int	i;

	i = 0;
	while (str[i] && input[i])
	{
		if (str[i] != input[i])
			return (FALSE);
		i++;
	}
	if (str[i] != 0 || input[i] != 0)
		return (FALSE);
	return (TRUE);
}

char	ft_check_quote(char *input)
{
	int		i;

	i = 0;
	while (input[i] && input[i] != DOUBLEQUOTE && input[i] != SINGLEQUOTE)
		i++;
	if (!input[i])
		return (FALSE);
	return (input[i]);
}

int	ft_strlen(char *input, int pos)
{
	char	type;
	int		i;

	if (input[pos] == DOUBLEQUOTE || input[pos] == SINGLEQUOTE)
		type = input[pos];
	else
		type = SPACE;
	i = pos;
	while (input[pos] && input[pos] != type)
		pos++;
	if (input[pos])
		pos++;
	return (pos - i);
}

char	**ft_parsing(char *input)
{
	int		i;
	char	**tab;
	int		t;
	int		j;
	int		len;

	i = 0;
	t = 0;
	j = 0;
	while (input[i])
	{
		len = ft_strlen(input, i);
		tab[]
		while (input[i] != DOUBLEQUOTE && input[i] != SINGLEQUOTE && input[i])
			tab[t][j] = input[i++];
	}
}

void	init_vars(t_vars *vars, char **ev)
{
	vars->env_shell = ft_parsing_sh(ev);
}

int	main(int ac, char **av, char **ev)
{
	char	*input;
	t_vars	vars;

	init_vars(&vars, ev);
	(void)ac;
	(void)av;
	while (1)
	{
		input = readline(vars.env_shell);
		if (ft_strcmp(input, "exit") == TRUE)
			break ;
		add_history(input);
		printf("You entered: %s\n", input);
		free(input);
	}
	//rl_clear_history();
	return (0);
}


