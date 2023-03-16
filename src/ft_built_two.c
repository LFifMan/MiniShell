/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/02/22 19:13:09 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_str_lower(char *str)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc (sizeof(char) * (ft_strlen(str) + 1));
	while (str && str[i])
	{
		dest[i] = (char)ft_tolower(str[i]);
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int	ft_builtins(t_tabs *tabs, t_var *var, char *cmd_one)
{
	int	i;

	i = 0;
	while (cmd_one[i])
	{
		cmd_one[i] = (char)ft_tolower(cmd_one[i]);
		i++;
	}
	if (ft_strcmp(cmd_one, "echo") == TRUE)
		return (ft_build_echo(tabs, var));
	else if (ft_strcmp(cmd_one, "cd") == TRUE)
		return (ft_build_cd(tabs, var, TRUE));
	else if (ft_strcmp(cmd_one, "pwd") == TRUE)
		return (ft_build_pwd(tabs, var));
	else if (ft_strcmp(cmd_one, "export") == TRUE)
		return (ft_build_export(tabs, var, TRUE));
	else if (ft_strcmp(cmd_one, "unset") == TRUE)
		return (ft_build_unset(tabs, var, TRUE));
	else if (ft_strcmp(cmd_one, "env") == TRUE)
		return (ft_build_env(tabs, var));
	else if (ft_strcmp(cmd_one, "exit") == TRUE)
		return (ft_build_exit(tabs, var, TRUE));
	return (FALSE);
}
