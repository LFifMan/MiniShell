/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/02/22 19:28:00 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] > '9' || str[i] < '0'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_build_exit(t_tabs *tabs, t_var *var, int print)
{
	if (tabs->cmds[1])
	{
		if (check_num(tabs->cmds[1]) == FALSE)
		{
			if (print == TRUE)
				ft_write_exit(tabs->cmds[1], 1, 255);
			exit (255);
		}
		else if (tabs->cmds[2])
		{
			if (print == TRUE)
				ft_write_exit(tabs->cmds[1], 2, 1);
			g_status = 1;
		}
		else
			exit (ft_atoi(tabs->cmds[1]));
	}
	else
		exit(var->tmp_g);
	return (TRUE);
}

void	ft_cd_absolute(t_tabs *tabs, t_var *var, int print)
{
	if (ft_find_dir(tabs->cmds[1]) == TRUE)
	{
		if (chdir(tabs->cmds[1]) == 0)
		{
			ft_update_exp(var, tabs->cmds[1]);
			ft_update_env(var, tabs->cmds[1]);
			g_status = 0;
		}
	}
	else
	{
		if (print == TRUE)
			ft_write(tabs->cmds[1], 0, 1);
	}
}

void	ft_cd_relative(t_tabs *tabs, t_var *var, int print, char *current)
{
	char	*str;

	str = ft_strjoin(ft_strjoin(current, "/", FALSE), tabs->cmds[1], FALSE);
	if (ft_find_dir(str) == TRUE)
	{
		if (chdir(str) == 0)
		{
			ft_update_exp(var, str);
			ft_update_env(var, str);
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

int	ft_find_home(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_memcmp((char *)env[i], "HOME=", 5) != 0)
		i++;
	return (i);
}
