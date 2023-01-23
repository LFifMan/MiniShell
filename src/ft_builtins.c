/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/01/23 16:05:17 by mstockli         ###   ########.fr       */
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

char	*get_current_cd(char **env)
{
	int		i;
	int		j;
	int		k;
	int		slash;
	char	*current = NULL;
	i = 0;
	k = 0;
	while (env[i] && ft_memcmp((char *)env[i], "PATH=", 5) != 0)
		i++;
	//if envp[i] == 0 -->stop
	// also, if PWD was modified, like a / was removed
	if (env[i][6] == '/')
	{
		j = 7;
		while  (env[i][j])
		{
			if (env[i][j] == '/')
				slash = j;
			j++;
		}
		current = malloc(sizeof(char) * j - slash + 1); // pas sur?
		if (!current)
			return (NULL);
		j = slash;
		while  (env[i][j])
		{
			current[k] = env[i][j];
			j++;
		}
		current[k] = 0;		
	}
	return (current);
}

char	*get_root_cd(char **env)
{
	int		i;
	int		j;
	int		k;
	char	*root = NULL;

	i = 0;
	k = 0;
	while (env[i] && ft_memcmp((char *)env[i], "PATH=", 5) != 0) // TDOD PWD not path, change all j nb after
		i++;
	//if envp[i] == 0 -->stop
	// also, if PWD was modified, like a / was removed
	if (env[i][6] == '/')
	{
		j = 7;
		while  (env[i][j] && env[i][j] != '/')
		{
			j++;
		}
		root = malloc(sizeof(char) * j - 6 + 1); // pas sur?
		if (!root)
			return (NULL);
		j = 6;
		while  (env[i][j] && env[i][j] != '/')
		{
			root[k] = env[i][j];
			j++;
		}
		root[k] = 0;

		
	}
	return (root);
}
/*
int	check_directory_exists(const char* path)
{
	DIR* dir;
	
	dir = opendir(path);
	if (dir) 
	{
		closedir(dir);
		return (TRUE);
	}
	return (FALSE);
}
*/
int	ft_build_cd(t_tabs *tabs, t_vars *vars)
{
	/*
	modify PWD and OLDPWD
	*/
	char	*root = NULL;
	char	*current;
	//char	*dir_path;

	root = get_root_cd(vars->envp);
	current = get_current_cd(vars->envp);
 /*
	if (ft_strncmp(tabs->cmds[1], root, ft_strlen(root)) == TRUE)
	{
		if (check_directory_exists(tabs->cmds[1]))
		{
			
		}
	}
	else
	{
		current = ft_strjoin()
	}
	*/
	(void)tabs;
	return (TRUE);
}

int	ft_build_pwd(t_tabs *tabs, t_vars *vars)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	(void)tabs;
	(void)vars;
	write(1, tmp, ft_strlen(tmp));
	write(1, "\n", 1);
	free(tmp);
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
