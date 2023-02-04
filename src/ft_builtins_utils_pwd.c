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

void	ft_pwd_exp(t_vars *vars, char *path)
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
	ft_old_pwd_exp(vars, i);
	ft_strcpy(tmp_exp, "declare -x PWD=");
	tmp_exp = ft_strjoin(tmp_exp, path, FALSE);
	free(vars->export[i]);
	vars->export[i] = tmp_exp;
}

void	ft_pwd(t_vars *vars, char *path)
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
	ft_old_pwd(vars, i);
	ft_strcpy(tmp_env, "PWD=");
	tmp_env = ft_strjoin(tmp_env, path, FALSE);
	free(vars->envp[i]);
	vars->envp[i] = tmp_env;
}

void	ft_old_pwd(t_vars *vars, int i)
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

void	ft_old_pwd_exp(t_vars *vars, int i)
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

int	ft_find_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_memcmp((char *)env[i], "HOME=", 5) != 0)
		i++;
	return (i);
}

