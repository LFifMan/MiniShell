/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:43:51 by max               #+#    #+#             */
/*   Updated: 2023/02/03 13:51:22 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_var(char *str, t_var *var, int index)
{
	int	i;
	int	j;

	i = 0;
	if (str[0] == EQUAL)
		return (FALSE);
	while (str[i] && str[i] != EQUAL && str[i] != SPACE)
	{
		if (ft_check_allowed_char(str[i], i + 1) == FALSE)
			return (0);
		i++;
	}
	if (str[i] == EQUAL)
		return (2);
	j = 0;
	while (var->env[j] && index == TRUE)
	{
		if (ft_strncmp(var->env[j], str, i) == TRUE)
			return (4);
		j++;
	}
	return (1);
}

void	ft_export_env(t_var *var, char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[size])
	{
		if (str[size] == EQUAL)
			break ;
		size++;
	}
	while (var->env[i])
	{
		if (ft_strncmp(var->env[i], str, size + 1) == TRUE)
		{
			var->env = replace_var(var->env, str, i);
			return ;
		}
		i++;
	}
	var->env = replace_var(var->env, str, i);
}

void	ft_export_export(t_var *var, char *str, int index)
{
	int		i;
	int		size;
	char	*export;

	export = ft_strdup("declare -x ", FALSE);
	export = ft_join_exp(export, str, index);
	i = 0;
	size = 0;
	while (export[size])
	{
		if (export[size] == EQUAL)
			break ;
		size++;
	}
	while (var->exp[i])
	{
		if (ft_strncmp(var->exp[i], export, size) == TRUE)
		{
			var->exp = replace_var(var->exp, export, i);
			return ;
		}
		i++;
	}
	var->exp = replace_var(var->exp, export, i);
	ft_sort_new_export(var);
}

int	ft_printf_export(t_tabs *tabs, t_var *var)
{
	int	i;
	int	len;

	(void)tabs;
	i = 0;
	while (var->exp[i])
	{
		len = (int)ft_strlen(var->exp[i]);
		write(1, var->exp[i], len);
		write(1, "\n", 1);
		i++;
	}
	return (TRUE);
}

int	ft_build_export(t_tabs *tabs, t_var *var, int print)
{
	int	i;

	i = 1;
	if (!tabs->cmds[i] && print == TRUE)
	{
		ft_printf_export(tabs, var);
	}
	while (tabs->cmds[i])
	{
		if (ft_check_var(tabs->cmds[i], var, TRUE) == 2)
		{
			ft_export_export(var, tabs->cmds[i], TRUE);
			ft_export_env(var, tabs->cmds[i]);
		}
		else if (ft_check_var(tabs->cmds[i], var, TRUE) == 1)
		{
			ft_export_export(var, tabs->cmds[i], FALSE);
		}
		else if (ft_check_var(tabs->cmds[i], var, TRUE) == 0)
			if (print == TRUE)
				ft_write(tabs->cmds[i], 4, 1);
		i++;
	}
	return (TRUE);
}
