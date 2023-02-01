/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:43:51 by max               #+#    #+#             */
/*   Updated: 2023/01/31 14:17:18 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var(char *str)
{
	int	i;

	i = 0;
	if (str[0] == EQUAL)
		return (FALSE);
	while (str[i] && str[i] != EQUAL && str[i] != SPACE)
	{
		if (ft_check_allowed_char(str[i], i + 1) == FALSE)
		{
			return (0);
		}
		i++;
	}
	if (str[i] == EQUAL)
	{
		return (2);
	}
	return (1);
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
		new_src = malloc(sizeof(char *) * (len + 2));
		if (!new_src)
			exit (EXIT_FAILURE);
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
		if (ft_strncmp(vars->envp[i], str, size + 1) == TRUE)
		{
			vars->envp = replace_var(vars->envp, str, i);
			return ;
		}
		i++;
	}
	vars->envp = replace_var(vars->envp, str, i);
}

void	ft_sort_new_export(t_vars *vars)
{
	int		i;
	int		envp_length;
	char	*tmp;

	i = 0;
	envp_length = 0;
	while (vars->export[envp_length])
		envp_length++;
	while (i < envp_length)
	{
		if (vars->export[i + 1] && ft_strcmp_ascii(vars->export[i], vars->export[i + 1]) < 0)
		{
			tmp = vars->export[i];
			vars->export[i] = vars->export[i + 1];
			vars->export[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void	ft_export_export(t_vars *vars, char *str, int index)
{
	int		i;
	int		size;
	char	*export;

	export = ft_strdup("declare -x ", FALSE);
	export = ft_join_export(export, str, index);
	i = 0;
	size = 0;

	while(export[size])
	{
		if (export[size] == EQUAL)
			break;
		size++;
	}
	while (vars->export[i])
	{
		if (ft_strncmp(vars->export[i], export, size) == TRUE)
		{
			vars->export = replace_var(vars->export, export, i);
			return ;
		}
		i++;
	}
	vars->export = replace_var(vars->export, export, i);
	ft_sort_new_export(vars);
}


int	ft_printf_export(t_tabs *tabs, t_vars *vars)
{
	int	i;
	int	len;

	(void)tabs;
	i = 0;
	while (vars->export[i])
	{
		len = ft_strlen(vars->export[i]);
		write(1, vars->export[i], len);
		write(1, "\n", 1);
		i++;
	}
	return (TRUE);
}

int	ft_build_export(t_tabs *tabs, t_vars *vars, int print)
{
	int	i;

	i = 1;
	if (!tabs->cmds[i] && print == TRUE)
	{
		ft_printf_export(tabs, vars);
	}
	while (tabs->cmds[i])
	{
		if (check_var(tabs->cmds[i]) == 2)
		{
			ft_export_export(vars, tabs->cmds[i], TRUE);
			ft_export_env(vars, tabs->cmds[i]);
		}
		else if (check_var(tabs->cmds[i]) == 1)
		{
			ft_export_export(vars, tabs->cmds[i], FALSE);
		}
		else
		{
			if (print == TRUE)
			{
				write (2, "bash: export: `", ft_strlen("bash: export: `"));
				write (2, tabs->cmds[i], ft_strlen(tabs->cmds[i]));
				write (2, "': not a valid identifier\n", ft_strlen("': not a valid identifier\n"));
			}
		}
		i++;
	}
	return (TRUE);
}
