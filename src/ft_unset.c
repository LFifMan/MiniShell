/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:44:36 by max               #+#    #+#             */
/*   Updated: 2023/01/22 23:47:30 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	ft_remove_var(t_vars *vars, char *str)
{
	int	i;
	int	j;
	int	len;
	
	len = strlen(str);
	i = 0;
	while (vars->envp[i])
	{
		if (ft_strncmp(vars->envp[i], str, len) == TRUE && (vars->envp[i][len] == '\0' || vars->envp[i][len] == '='))
		{
			free(vars->envp[i]);
			j = i;
			while (vars->envp[j])
			{
				vars->envp[j] = vars->envp[j+1];
				j++;
			}
		}
		else
			i++;
	}
	return ;
}

int	ft_build_unset(t_tabs *tabs, t_vars *vars)
{
	int	i;

	i = 1;
	while (tabs->cmds[i])
	{
		if (check_var(tabs->cmds[i]) == TRUE)
		{
			ft_remove_var(vars, tabs->cmds[i]);
		}
		i++;
	}
	return (TRUE);
}

void	ft_unset_export(t_tabs *tabs, t_vars *vars, char *cmd_one)
{
	int	i;

	i = 0;
	tabs = tabs->next;
	while (cmd_one[i])
	{
		cmd_one[i] = ft_tolower(cmd_one[i]);
		i++;
	}

	if (tabs->next)
		return ;
	while (tabs)
	{
		if (ft_strcmp(cmd_one, "export") == TRUE)
			ft_build_export(tabs, vars);
		else if (ft_strcmp(cmd_one, "unset") == TRUE)
			ft_build_unset(tabs, vars);
		tabs = tabs->next;
	}
}