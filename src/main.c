/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:38:47 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/24 15:39:19 by mstockli         ###   ########.fr       */
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
	printf ("env %p\n", new_envp);

	while (i < envp_length)
	{
		new_envp[i] = ft_strdup(envp[i], FALSE);
		i++;
	}
	new_envp[envp_length] = 0;
	vars->envp = new_envp;
}

//void	sigint_handler(int sig)
//{
//	(void)sig;
//	rl_on_new_line();
//	printf("\n");
//	rl_replace_line("", 0);
//	rl_redisplay();
//}
//
//void	disable_sigint_display(void)
//{
//	struct termios	t;
//
//	tcgetattr(STDIN_FILENO, &original_settings);
//	t = original_settings;
//	t.c_lflag &= ~ECHOCTL;
////	t.c_cc[VQUIT] = 4;
//	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
//}

void	restore_terminal_settings(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_settings);
}

int	main(int ac, char **av, char **ev)
{
	t_vars	vars;
	int		i;
	(void)av;
	(void)ac;
	
	/*
	if (ac != 1 || av[1])
	{
		printf("Minishell does not take arguments\n");
		exit (0);
	}
	*/
	ft_signals();
//	disable_sigint_display();
//	signal(SIGINT, sigint_handler);
//	signal(SIGQUIT, sigquit_handler);
	init_vars(&vars, ev);
	control_tower(&vars);
	i = 0;
	while (vars.envp[i])
	{
		free(vars.envp[i]);
		i++;
	}
	free(vars.envp);
	restore_terminal_settings();
	return (0);
}
