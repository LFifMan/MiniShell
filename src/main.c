/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:38:47 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/26 12:59:35 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_vars(t_vars *vars, char **envp)
{
	int		envp_length;
	int		i;
	char	**new_envp;

	envp_length = 0;
	i = 0;
	while (envp[envp_length])
		envp_length++;
	new_envp = malloc(sizeof(char *) * (envp_length + 1));
	while (i < envp_length)
	{
		new_envp[i] = ft_strdup(envp[i], FALSE);
		i++;
	}
	new_envp[envp_length] = 0;
	vars->envp = new_envp;
}

void	restore_terminal_settings(struct termios original_settings)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_settings);
}

int	main(int ac, char **av, char **ev)
{
	t_vars	vars;
	int		i;
	struct termios original_settings;

	(void)av;
	(void)ac;
	tcgetattr(STDIN_FILENO, &original_settings);
	ft_signals(original_settings);
	init_vars(&vars, ev);
	control_tower(&vars);
	i = 0;
	while (vars.envp[i])
	{
		free(vars.envp[i]);
		i++;
	}
	free(vars.envp);
	restore_terminal_settings(original_settings);
	return (0);
}
