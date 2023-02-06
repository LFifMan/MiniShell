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

void	ft_cd_absolute(t_tabs *tabs, t_var *var, int print)
{
	if (ft_find_dir(tabs->cmds[1]) == TRUE)
	{
		if (chdir(tabs->cmds[1]) == 0)
		{
			ft_pwd_exp(var, tabs->cmds[1]);
			ft_pwd(var, tabs->cmds[1]);
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
			ft_pwd_exp(var, str);
			ft_pwd(var, str);
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
