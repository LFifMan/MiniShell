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

void	ft_cd_absolute(t_tabs *tabs, t_vars *vars, int print)
{
	if (ft_find_dir(tabs->cmds[1]) == TRUE)
	{
		if (chdir(tabs->cmds[1]) == 0)
		{
			ft_pwd_exp(vars, tabs->cmds[1]);
			ft_pwd(vars, tabs->cmds[1]);
			g_status = 0;
		}
	}
	else
		if (print == TRUE)
			ft_write(tabs->cmds[1], 0, 1);
}

void	ft_cd_relative(t_tabs *tabs, t_vars *vars, int print, char *current)
{
	char	*str;

	str = ft_strjoin(ft_strjoin(current, "/", FALSE), tabs->cmds[1], FALSE);
	if (ft_find_dir(str) == TRUE)
	{
		if (chdir(str) == 0)
		{
			ft_pwd_exp(vars, str);
			ft_pwd(vars, str);
			g_status = 0;
		}
		free(str);
	}
	else
	{
		if (print == TRUE && errno == ENOENT)
			ft_write(tabs->cmds[1], 0, 1);
		else if (print == TRUE && errno == EACCES)
			ft_write(tabs->cmds[1], 1, 1);
		free(str);
	}
}

int	ft_build_cd(t_tabs *tabs, t_vars *vars, int print)
{
	char	*curr;

	curr = getcwd(NULL, 0);
	if (!tabs->cmds[1])
	{
		ft_cd_alone(vars->envp, print, vars);
		free(curr);
	}
	else if (ft_strncmp(tabs->cmds[1], vars->root, ft_strlen(vars->root)) == TRUE)
	{
		ft_cd_absolute(tabs, vars, print);
		free(curr);
	}
	else
		ft_cd_relative(tabs, vars, print, curr);
	return (TRUE);
}


