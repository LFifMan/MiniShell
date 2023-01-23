/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:43:51 by max               #+#    #+#             */
/*   Updated: 2023/01/23 22:58:25 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var(char *str)
{
	int	i;

	i = 0;
	if (str[0] == EQUAL)
		return (FALSE);
	while (str[i] && str[i] != EQUAL)
	{
		if (ft_check_allowed_char(str[i], i + 1) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char **replace_var(char **src, char *str, int place) 
{
	int i;
	int len;
	char **new_src;
	
	i = 0;
	len = 0;
	while (src[len] != 0)
	{
		len++;
	}
	if (place < len)
	{
		free(src[place]);
		src[place] = ft_strdup(str, FALSE);
	}
	else
	{
		new_src = malloc(sizeof(char *) * (i + 2));
		while (i < len)
		{
			new_src[i] = src[i];
			i++;
		}
		new_src[len] = ft_strdup(str, FALSE);
		new_src[len + 1] = 0;
		free(src);
		src = new_src;
	}
	/*
	int t = 0;
	while (src[t])
	{
		printf("%s\n", src[t]);
		t++;
	}
	*/
	return (src);
}

void	ft_export_env(t_vars *vars, char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while(str[size])
	{
		if (str[size] == EQUAL)
			break;
		size++;
	}
	while (vars->envp[i])
	{
		if (ft_strncmp(vars->envp[i], str, size) == TRUE)
		{
			vars->envp = replace_var(vars->envp, str, i);
			return ;
		}
		i++;
	}
	vars->envp = replace_var(vars->envp, str, size);
}

int	ft_build_export(t_tabs *tabs, t_vars *vars)
{
	int	i;

	i = 1;
	while (tabs->cmds[i])
	{
		if (check_var(tabs->cmds[i]) == TRUE)
		{
			ft_export_env(vars, tabs->cmds[i]);
		}
		i++;
	}

	return (TRUE);
}
