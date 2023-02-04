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

int	ft_build_echo(t_tabs *tabs, t_vars *vars)
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
	(void)vars;
	return (TRUE);
}

//int	ft_build_cd(t_tabs *tabs, t_vars *vars, int print)
//{
//	char	*current;
//	char	*relative;
//
//	current = getcwd(NULL, 0);
//	if (!tabs->cmds[1])
//	{
//		ft_cd_alone(vars->envp, print, vars);
//		free(current);
//	}
//	else if (ft_strncmp(tabs->cmds[1], vars->root, ft_strlen(vars->root)) == TRUE)
//	{
//		if (ft_find_dir(tabs->cmds[1]) == TRUE)
//		{
//			if (chdir(tabs->cmds[1]) == 0)
//			{
//				ft_pwd_exp(vars, tabs->cmds[1]);
//				ft_pwd(vars, tabs->cmds[1]);
//				g_status = 0;
//			}
//		}
//		else
//			if (print == TRUE)
//				ft_write(tabs->cmds[1], 0, 1);
//		free(current);
//	}
//	else
//	{
//		relative = ft_strjoin(ft_strjoin(current, "/", FALSE), tabs->cmds[1], FALSE);
//		if (ft_find_dir(relative) == TRUE)
//		{
//			if (chdir(relative) == 0)
//			{
//				ft_pwd_exp(vars, relative);
//				ft_pwd(vars, relative);
//				g_status = 0;
//			}
//		}
//		else
//		{
//			if (print == TRUE && errno == ENOENT)
//				ft_write(tabs->cmds[1], 0, 1);
//			else if (print == TRUE && errno == EACCES)
//				ft_write(tabs->cmds[1], 1, 1);
//		}
//		free(relative);
//	}
//	return (TRUE);
//}

int	ft_build_pwd(t_tabs *tabs, t_vars *vars)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	(void)tabs;
	(void)vars;
	write(1, temp, ft_strlen(temp));
	write(1, "\n", 1);
	free(temp);
	g_status = 0;
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
		len = (int)ft_strlen(vars->envp[i]);
		write(1, vars->envp[i], len);
		write(1, "\n", 1);
		i++;
	}
	return (TRUE);
}

int	ft_build_exit(char *input)
{
	int	i;

	if (ft_strcmp(input, "exit") == TRUE)
	{
		return (TRUE);
	}
	if (ft_strncmp(input, "exit ", 5) == TRUE)
	{
		i = 5;
		while (input[i])
		{
			if (input[i] > '9' || input[i] < '0' )
				return (FALSE);
			i++;
		}
		exit(ft_atoi(&input[5]) % 256);
	}
	else
		return (FALSE);
}

int	ft_builtins(t_tabs *tabs, t_vars *vars, char *cmd_one)
{
	int	i;

	i = 0;
	while (cmd_one[i])
	{
		cmd_one[i] = (char)ft_tolower(cmd_one[i]);
		i++;
	}
	if (ft_strcmp(cmd_one, "echo") == TRUE)
		return (ft_build_echo(tabs, vars));
	else if (ft_strcmp(cmd_one, "cd") == TRUE)
		return (ft_build_cd(tabs, vars, FALSE));
	else if (ft_strcmp(cmd_one, "pwd") == TRUE)
		return (ft_build_pwd(tabs, vars));
	else if (ft_strcmp(cmd_one, "export") == TRUE)
		return (ft_build_export(tabs, vars, FALSE));
	else if (ft_strcmp(cmd_one, "unset") == TRUE)
		return (ft_build_unset(tabs, vars, FALSE));
	else if (ft_strcmp(cmd_one, "env") == TRUE)
		return (ft_build_env(tabs, vars));
	return (FALSE);
}
