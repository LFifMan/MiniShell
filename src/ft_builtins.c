/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/01/31 18:16:14 by mstockli         ###   ########.fr       */
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
		len = (int)ft_strlen(tabs->cmds[i]);
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

int	check_directory_exists(const char* path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (TRUE);
	}
	return (FALSE);
}

void	update_oldpwd(t_vars *vars, int i)
{
	int		j;
	char	*tmp_env;

	tmp_env = ft_strdup("OLDPWD=", FALSE);
	j = 0;
	while (vars->envp[j])
	{
		if (ft_strncmp(vars->envp[j], "OLDPWD=", 7) == TRUE)
			break ;
		j++;
	}
	free(vars->envp[j]);
	vars->envp[j] = ft_strjoin(tmp_env, &vars->envp[i][4], FALSE);
}

void	update_pwd(t_vars *vars, char *path)
{
	char	*tmp_env;
	int		i;

	tmp_env = malloc(sizeof(char) * 5);
	if (!tmp_env)
		exit (EXIT_FAILURE);
	i = 0;
	while (vars->envp[i])
	{
		if (ft_strncmp(vars->envp[i], "PWD=", 4) == TRUE)
			break ;
		i++;
	}
	update_oldpwd(vars, i);
	ft_strcpy(tmp_env, "PWD=");
	tmp_env = ft_strjoin(tmp_env, path, FALSE);
	free(vars->envp[i]);
	vars->envp[i] = tmp_env;
}

void	update_oldpwd_exp(t_vars *vars, int i)
{
	int		j;
	char	*tmp_exp;

	tmp_exp = ft_strdup("declare -x OLDPWD=", FALSE);
	j = 0;
	while (vars->export[j])
	{
		if (ft_strncmp(vars->export[j], "declare -x OLDPWD=", 18) == TRUE)
			break ;
		j++;
	}
	free(vars->export[j]);
	vars->export[j] = ft_strjoin(tmp_exp, &vars->export[i][15], FALSE);
}

void	update_pwd_exp(t_vars *vars, char *path)
{
	char	*tmp_exp;
	int		i;

	tmp_exp = malloc(sizeof(char) * 16);
	if (!tmp_exp)
		exit (EXIT_FAILURE);
	i = 0;
	while (vars->export[i])
	{
		if (ft_strncmp(vars->export[i], "declare -x PWD=", 15) == TRUE)
			break ;
		i++;
	}
	update_oldpwd_exp(vars, i);
	ft_strcpy(tmp_exp, "declare -x PWD=");
	tmp_exp = ft_strjoin(tmp_exp, path, FALSE);
	free(vars->export[i]);
	vars->export[i] = tmp_exp;
}

void	ft_cd_alone(char **env, int print, t_vars *vars)
{
	int		i;
	int		j;
	int		k;
	char	*root;

	i = 0;
	k = 0;
	root = NULL;
	while (env[i] && ft_memcmp((char *)env[i], "HOME=", 5) != 0)
		i++;
	if (!env[i] && print == TRUE)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		g_status = 1;
		return ;
	}
	if (env[i][5])
	{
		j = 5;
		while (env[i][j])
			j++;
		root = malloc(sizeof(char) * (j - 5 + 1)); // pas sur?
		if (!root)
			exit(EXIT_FAILURE);
		j = 5;
		while (env[i][j])
		{
			root[k] = env[i][j];
			j++;
			k++;
		}
		root[k] = 0;
	}
	if (chdir(root) == 0)
	{
		update_pwd_exp(vars, root);
		update_pwd(vars, root);
		g_status = 0;
	}
	else
		if (print == TRUE && root)
			ft_write(root, 0, 1);
}


int	ft_build_cd(t_tabs *tabs, t_vars *vars, int print)
{
	char	*current;
	char	*relative;

	current = getcwd(NULL, 0);
	if (!tabs->cmds[1])
	{
		ft_cd_alone(vars->envp, print, vars);
		free(current);
	}
	else if (ft_strncmp(tabs->cmds[1], vars->root, ft_strlen(vars->root)) == TRUE)
	{
		if (check_directory_exists(tabs->cmds[1]) == TRUE)
		{
			if (chdir(tabs->cmds[1]) == 0)
			{
				update_pwd_exp(vars, tabs->cmds[1]);
				update_pwd(vars, tabs->cmds[1]);
				g_status = 0;
			}
		}
		else
			if (print == TRUE)
				ft_write(tabs->cmds[1], 0, 1);
		free(current);
	}
	else
	{
		relative = ft_strjoin(ft_strjoin(current, "/", FALSE), tabs->cmds[1], FALSE);
		if (check_directory_exists(relative) == TRUE)
		{
			if (chdir(relative) == 0)
			{
				update_pwd_exp(vars, relative);
				update_pwd(vars, relative);
				g_status = 0;
			}
		}
		else
		{
			if (print == TRUE && errno == ENOENT)
				ft_write(tabs->cmds[1], 0, 1);
			else if (print == TRUE && errno == EACCES)
				ft_write(tabs->cmds[1], 1, 1);
		}
		free(relative);
	}
	return (TRUE);
}

int	ft_build_pwd(t_tabs *tabs, t_vars *vars)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	(void)tabs;
	(void)vars;
	write(1, temp, ft_strlen(temp));
	write(1, "\n", 1);
	free(temp);
	g_status = 0;
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
		len = (int)ft_strlen(vars->envp[i]);
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
		return (ft_build_cd(tabs, vars, FALSE));
	else if (ft_strcmp(cmd_one, "pwd") == TRUE)
		return (ft_build_pwd(tabs, vars));
	else if (ft_strcmp(cmd_one, "export") == TRUE)
		return (ft_build_export(tabs, vars, FALSE));
	else if (ft_strcmp(cmd_one, "unset") == TRUE)
		return (ft_build_unset(tabs, vars, FALSE));
	else if (ft_strcmp(cmd_one, "env") == TRUE)
		return (ft_build_env(tabs, vars));
	return (FALSE);
}
