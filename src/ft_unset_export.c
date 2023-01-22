/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:44:36 by max               #+#    #+#             */
/*   Updated: 2023/01/22 22:25:17 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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