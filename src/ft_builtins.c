/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/01/22 22:49:49 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_build_echo(t_tabs *tabs, t_vars *vars)
{
	int	newline;
	int	i;
	int	len;

	newline = 0;
	if (ft_strcmp(tabs->cmds[1], "-n") == TRUE)
		newline = 1;
	i = newline + 1;
	while (tabs->cmds[i])
	{
		len = ft_strlen(tabs->cmds[i]);
		write(1, tabs->cmds[i], len);
		if (tabs->cmds[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline == 0)
		write(1, "\n", 1);
	(void)vars;
	return (TRUE);
}

int	ft_build_cd(t_tabs *tabs, t_vars *vars)
{
	(void)tabs;
	(void)vars;

	return (TRUE);
}

int	ft_build_pwd(t_tabs *tabs, t_vars *vars)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	(void)tabs;
	(void)vars;
	write(1, tmp, ft_strlen(tmp)); // change with getcwd
	write(1, "\n", 1);
	free(tmp);
	return (TRUE);
}

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
		src[place] = ft_strdup(str); // new_src
	}
	else
	{
		new_src = malloc(sizeof(char *) * (i + 2));
		while (i < len)
		{
			new_src[i] = src[i];
			i++;
		}
		new_src[len] = ft_strdup(str);
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













int	ft_build_env(t_tabs *tabs, t_vars *vars)
{
	int	i;
	int	len;

	(void)tabs;
	i = 0;
	while (vars->envp[i])
	{
		len = ft_strlen(vars->envp[i]);
		write(1, vars->envp[i], len);
		write(1, "\n", 1);
		i++;
	}
	return (TRUE);
}

int	ft_builtins(t_tabs *tabs, t_vars *vars, char *cmd_one)
{
	int	i;
	
	i = 0;
	while (cmd_one[i])
	{
		cmd_one[i] = ft_tolower(cmd_one[i]);
		i++;
	}
	if (ft_strcmp(cmd_one, "echo") == TRUE)
		return (ft_build_echo(tabs, vars));
	else if (ft_strcmp(cmd_one, "cd") == TRUE)
		return (ft_build_cd(tabs, vars));
	else if (ft_strcmp(cmd_one, "pwd") == TRUE)
		return (ft_build_pwd(tabs, vars));
	else if (ft_strcmp(cmd_one, "export") == TRUE)
		return (ft_build_export(tabs, vars));
	else if (ft_strcmp(cmd_one, "unset") == TRUE)
		return (ft_build_unset(tabs, vars));
	else if (ft_strcmp(cmd_one, "env") == TRUE)
		return (ft_build_env(tabs, vars));
	return (FALSE);
}
