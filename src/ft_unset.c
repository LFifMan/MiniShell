/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:44:36 by max               #+#    #+#             */
/*   Updated: 2023/03/06 18:17:29 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_remove_env_var(t_var *var, char *str)
{
	int	i;
	int	j;
	int	len;

	len = (int)strlen(str);
	i = 0;
	while (var->env[i])
	{
		if (ft_strncmp(var->env[i], str, len) == TRUE && \
		(var->env[i][len] == '\0' || var->env[i][len] == '='))
		{
			free(var->env[i]);
			j = i;
			while (var->env[j])
			{
				var->env[j] = var->env[j + 1];
				j++;
			}
		}
		else
			i++;
	}
}

void	ft_remove_export_var(t_var *var, char *str)
{
	int		i;
	int		j;
	int		len;
	char	*unset;

	unset = ft_strdup("declare -x ", FALSE);
	unset = ft_join_exp(unset, str, FALSE);
	len = (int)strlen(unset);
	i = 0;
	while (var->exp[i])
	{
		if (ft_strncmp(var->exp[i], unset, len) == TRUE && \
		(var->exp[i][len] == '\0' || var->exp[i][len] == '='))
		{
			free(var->exp[i]);
			j = i;
			while (var->exp[j])
			{
				var->exp[j] = var->exp[j + 1];
				j++;
			}
		}
		else
			i++;
	}
}

int	ft_build_unset(t_tabs *tabs, t_var *var, int print)
{
	int	i;

	i = 1;
	while (tabs->cmds[i])
	{
		if (ft_check_var(tabs->cmds[i], var, FALSE) == 1)
		{
			ft_remove_env_var(var, tabs->cmds[i]);
			ft_remove_export_var(var, tabs->cmds[i]);
		}
		else
			if (print == TRUE)
				ft_write(tabs->cmds[i], 5, 1);
		i++;
	}
	return (TRUE);
}

void	ft_unset_export(t_tabs *tabs, t_var *var, char *cmd_one)
{
	int	i;

	i = 0;
	tabs = tabs->next;
	if (!cmd_one)
		return ;
	while (cmd_one[i])
	{
		cmd_one[i] = (char)ft_tolower(cmd_one[i]);
		i++;
	}
	if (tabs->next)
		return ;
	while (tabs)
	{
		if (ft_strcmp(cmd_one, "export") == TRUE)
			ft_build_export(tabs, var, FALSE);
		else if (ft_strcmp(cmd_one, "unset") == TRUE)
			ft_build_unset(tabs, var, FALSE);
		else if (ft_strcmp(cmd_one, "cd") == TRUE)
			ft_build_cd(tabs, var, FALSE);
		else if (ft_strcmp(cmd_one, "exit") == TRUE)
			ft_build_exit(tabs, var, FALSE);
		tabs = tabs->next;
	}
}
