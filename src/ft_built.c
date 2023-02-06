/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/01/31 18:16:14 by mstockli         ###   ########.fr       */
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
	else if (ft_strncmp(tabs->cmds[1], var->home, ft_strlen(var->home)) == TRUE)
	{
		ft_cd_absolute(tabs, var, print);
		free(curr);
	}
	else
		ft_cd_relative(tabs, var, print, curr);
	return (TRUE);
}

int	ft_builtins(t_tabs *tabs, t_var *var, char *cmd_one)
{
	int	i;

	i = 0;
	while (cmd_one[i])
	{
		cmd_one[i] = (char)ft_tolower(cmd_one[i]);
		i++;
	}
	if (ft_strcmp(cmd_one, "echo") == TRUE)
		return (ft_build_echo(tabs, var));
	else if (ft_strcmp(cmd_one, "cd") == TRUE)
		return (ft_build_cd(tabs, var, FALSE));
	else if (ft_strcmp(cmd_one, "pwd") == TRUE)
		return (ft_build_pwd(tabs, var));
	else if (ft_strcmp(cmd_one, "export") == TRUE)
		return (ft_build_export(tabs, var, FALSE));
	else if (ft_strcmp(cmd_one, "unset") == TRUE)
		return (ft_build_unset(tabs, var, FALSE));
	else if (ft_strcmp(cmd_one, "env") == TRUE)
		return (ft_build_env(tabs, var));
	return (FALSE);
}
