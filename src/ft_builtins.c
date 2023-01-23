/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/01/23 00:01:22 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_build_echo(t_tabs *tabs, t_vars *vars)
{
	int	newline;
	int	i;
	int	len;

	newline = 0;
	if (ft_strcmp(tabs->cmds[1], "-n") == TRUE)
		newline = 1;
	i = newline + 1;
	while (tabs->cmds[i])
	{
		len = ft_strlen(tabs->cmds[i]);
		write(1, tabs->cmds[i], len);
		if (tabs->cmds[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline == 0)
		write(1, "\n", 1);
	(void)vars;
	return (TRUE);
}

int	ft_build_cd(t_tabs *tabs, t_vars *vars)
{
	(void)tabs;
	(void)vars;
	return (TRUE);
}

int	ft_build_pwd(t_tabs *tabs, t_vars *vars)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	(void)tabs;
	(void)vars;
	write(1, tmp, ft_strlen(tmp));
	write(1, "\n", 1);
	free(tmp);
	return (TRUE);
}

int	ft_build_env(t_tabs *tabs, t_vars *vars)
{
	int	i;
	int	len;

	(void)tabs;
	i = 0;
	while (vars->envp[i])
	{
		len = ft_strlen(vars->envp[i]);
		write(1, vars->envp[i], len);
		write(1, "\n", 1);
		i++;
	}
	return (TRUE);
}

int	ft_builtins(t_tabs *tabs, t_vars *vars, char *cmd_one)
{
	int	i;

	i = 0;
	while (cmd_one[i])
	{
		cmd_one[i] = ft_tolower(cmd_one[i]);
		i++;
	}
	if (ft_strcmp(cmd_one, "echo") == TRUE)
		return (ft_build_echo(tabs, vars));
	else if (ft_strcmp(cmd_one, "cd") == TRUE)
		return (ft_build_cd(tabs, vars));
	else if (ft_strcmp(cmd_one, "pwd") == TRUE)
		return (ft_build_pwd(tabs, vars));
	else if (ft_strcmp(cmd_one, "export") == TRUE)
		return (ft_build_export(tabs, vars));
	else if (ft_strcmp(cmd_one, "unset") == TRUE)
		return (ft_build_unset(tabs, vars));
	else if (ft_strcmp(cmd_one, "env") == TRUE)
		return (ft_build_env(tabs, vars));
	return (FALSE);
}
