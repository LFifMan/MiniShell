/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/02/22 19:13:09 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_build_echo(t_tabs *tabs, t_var *var)
{
	int	newline;
	int	i;
	int	len;

	i = 1;
	newline = 0;
	while (ft_option_n(tabs->cmds[i]) == TRUE)
	{
		newline++;
		i++;
	}
	i = newline + 1;
	while (tabs->cmds[i])
	{
		len = (int)ft_strlen(tabs->cmds[i]);
		write(1, tabs->cmds[i], len);
		if (tabs->cmds[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline == 0)
		write(1, "\n", 1);
	(void)var;
	return (TRUE);
}

int	ft_build_pwd(t_tabs *tabs, t_var *var)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	(void)tabs;
	(void)var;
	write(1, temp, ft_strlen(temp));
	write(1, "\n", 1);
	free(temp);
	g_status = 0;
	return (TRUE);
}

int	ft_build_env(t_tabs *tabs, t_var *var)
{
	int	i;
	int	len;

	(void)tabs;
	i = 0;
	while (var->env[i])
	{
		len = (int)ft_strlen(var->env[i]);
		write(1, var->env[i], len);
		write(1, "\n", 1);
		i++;
	}
	return (TRUE);
}

int	ft_build_cd(t_tabs *tabs, t_var *var, int print)
{
	char	*curr;

	curr = getcwd(NULL, 0);
	if (!tabs->cmds[1])
	{
		ft_cd_alone(var->env, print, var);
		free(curr);
	}
	else if ((ft_strcmp(tabs->cmds[1], "-") == TRUE || \
	ft_strcmp(tabs->cmds[1], "~") == TRUE) && print == TRUE)
		ft_write(tabs->cmds[1], 7, 1);
	else if (ft_strncmp(tabs->cmds[1], "/", 1) == TRUE)
	{
		ft_cd_absolute(tabs, var, print);
		free(curr);
	}
	else
		ft_cd_relative(tabs, var, print, curr);
	return (TRUE);
}
