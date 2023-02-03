/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:44:36 by max               #+#    #+#             */
/*   Updated: 2023/01/31 18:02:45 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_remove_env_var(t_vars *vars, char *str)
{
	int	i;
	int	j;
	int	len;

	len = (int)strlen(str);
	i = 0;
	while (vars->envp[i])
	{
		if (ft_strncmp(vars->envp[i], str, len) == TRUE && \
		(vars->envp[i][len] == '\0' || vars->envp[i][len] == '='))
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
}

void	ft_remove_export_var(t_vars *vars, char *str)
{
	int		i;
	int		j;
	int		len;
	char	*unset;

	unset = ft_strdup("declare -x ", FALSE);
	unset = ft_join_export(unset, str, FALSE);
	len = (int)strlen(unset);
	i = 0;
	while (vars->export[i])
	{
		if (ft_strncmp(vars->export[i], unset, len) == TRUE && \
		(vars->export[i][len] == '\0' || vars->export[i][len] == '='))
		{
			free(vars->export[i]);
			j = i;
			while (vars->export[j])
			{
				vars->export[j] = vars->export[j+1];
				j++;
			}
		}
		else
			i++;
	}
}

int	ft_build_unset(t_tabs *tabs, t_vars *vars, int print)
{
	int	i;

	i = 1;
	while (tabs->cmds[i])
	{
		if (check_var(tabs->cmds[i]) == 1)
		{
			ft_remove_env_var(vars, tabs->cmds[i]);
			ft_remove_export_var(vars, tabs->cmds[i]);
		}
		else
			if (print == TRUE)
				ft_write(tabs->cmds[i], 5, 1);
		i++;
	}
	return (TRUE);
}

void	ft_unset_export(t_tabs *tabs, t_vars *vars, char *cmd_one)
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
			ft_build_export(tabs, vars, TRUE);
		else if (ft_strcmp(cmd_one, "unset") == TRUE)
			ft_build_unset(tabs, vars, TRUE);
		else if (ft_strcmp(cmd_one, "cd") == TRUE)
		{
			ft_build_cd(tabs, vars, TRUE);
		}
		tabs = tabs->next;
	}
}
