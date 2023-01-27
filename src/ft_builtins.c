/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/01/27 20:44:33 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_option_n(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (FALSE);
			i++;
		}
	}
	else
		return (FALSE);
	return (TRUE);
}
int	ft_build_echo(t_tabs *tabs, t_vars *vars)
{
	int	newline;
	int	i;
	int	len;

	i = 1;
	newline = 0;
	while (check_option_n(tabs->cmds[i]) == TRUE)
	{
		newline++;
		i++;
	}
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
	char	*current = NULL;
	i = 0;
	k = 0;
	while (env[i] && ft_memcmp((char *)env[i], "PWD=", 4) != 0)
		i++;
	//if envp[i] == 0 -->stop
	// also, if PWD was modified, like a / was removed
	if (env[i][4] == '/')
	{
		j = 5;
		while  (env[i][j])
		{
			j++;
		}
		current = malloc(sizeof(char) * j + 1);
		if (!current)
			return (NULL); // TODO: protect mallocs
		j = 4;
		while  (env[i][j])
		{
			current[k] = env[i][j];
			j++;
			k++;
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
	while (env[i] && ft_memcmp((char *)env[i], "PWD=", 4) != 0) // TODO: PWD not path, change all j nb after
		i++;
	//if envp[i] == 0 -->stop
	// also, if PWD was modified, like a / was removed
	
	if (env[i][4] == '/')
	{
		j = 5;
		while  (env[i][j] && env[i][j] != '/')
		{
			j++;
		}

		root = malloc(sizeof(char) * (j - 5 + 2)); // pas sur?
		if (!root)
			return (NULL);
		j = 5;
		root[k] = '/';
		k++;
		while  (env[i][j] && env[i][j] != '/')
		{
			root[k] = env[i][j];
			j++;
			k++;
		}
		root[k] = 0;	
	}
	return (root);
}

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

void update_pwd(t_vars *vars, char *path)
{
	char	*tmp;
	int		i;

	tmp = malloc(sizeof(char) * 5);
	if (!tmp) // TODO: malloc errors
		return ;
	i = 0;
	while (vars->envp[i])
	{
		if (ft_strncmp(vars->envp[i], "PWD=", 4) == TRUE)
			break ;
		i++;
	}
	ft_strcpy(tmp, "PWD=");
	tmp = ft_strjoin(tmp, path, FALSE);
	free(vars->envp[i]);
	vars->envp[i] = tmp;
}

int	ft_build_cd(t_tabs *tabs, t_vars *vars)
{
	/*
	TODO: modify OLDPWD
	*/
	char	*root = NULL;
	char	*current = NULL;
	char	*relative = NULL;

	root = get_root_cd(vars->envp);
	current = get_current_cd(vars->envp);
	if (!tabs->cmds[1] || (ft_strncmp(tabs->cmds[1], root, ft_strlen(root)) == TRUE && tabs->cmds[1][ft_strlen(root)] == '\0'))
	{
		if (chdir(root) == 0)
		{
			update_pwd(vars, root);
			free(current);
		}
	}
	else if (ft_strncmp(tabs->cmds[1], root, ft_strlen(root)) == TRUE)
	{
		if (tabs->cmds[1][ft_strlen(root)] == '/' && check_directory_exists(tabs->cmds[1]) == TRUE)
		{
			if (chdir(tabs->cmds[1]) == 0) 
			{
				update_pwd(vars, tabs->cmds[1]);
			}
		}
		else
		{
			//TODO: error like in bash, stay in same repo 
			//but careful cause it should not print the message twice!
		}
		free(current);
	}
	else
	{
		relative = ft_strjoin(ft_strjoin(current, "/", FALSE), tabs->cmds[1], FALSE);
		if (check_directory_exists(relative) == TRUE)
		{
			if (chdir(relative) == 0) 
			{
				update_pwd(vars, relative);

			}
			else
				printf("fuck\n"); // TODO: error like in bash, stay in same repo
			//but careful cause it should not print the message twice! (because of pipex and unset_export)
		}
		free(relative);
	}
	//free(current);
	free(root);
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
