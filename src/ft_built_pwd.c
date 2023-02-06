/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/02/06 20:55:47 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd_exp(t_var *var, char *path)
{
	char	*tmp_exp;
	int		i;

	(void)path;
	tmp_exp = malloc(sizeof(char) * 16);
	if (!tmp_exp)
		exit (EXIT_FAILURE);
	i = 0;
	while (var->exp[i])
	{
		if (ft_strncmp(var->exp[i], "declare -x PWD=", 15) == TRUE)
			break ;
		i++;
	}
	ft_old_pwd_exp(var, i);
	if (!var->exp[i])
		return ;
	ft_strcpy(tmp_exp, "declare -x PWD=");
	tmp_exp = ft_strjoin(tmp_exp, getcwd(NULL, 0), FALSE);
	free(var->exp[i]);
	var->exp[i] = tmp_exp;
}

void	ft_pwd(t_var *var, char *path)
{
	char	*tmp_env;
	int		i;

	(void)path;
	tmp_env = malloc(sizeof(char) * 5);
	if (!tmp_env)
		exit (EXIT_FAILURE);
	i = 0;
	while (var->env[i])
	{
		if (ft_strncmp(var->env[i], "PWD=", 4) == TRUE)
			break ;
		i++;
	}
	ft_old_pwd(var, i);
	if (!var->env[i])
		return ;
	ft_strcpy(tmp_env, "PWD=");
	tmp_env = ft_strjoin(tmp_env, getcwd(NULL, 0), FALSE);
	free(var->env[i]);
	var->env[i] = tmp_env;
}

char	**reset_env(t_var *var, char *src)
{
	int	i;
	char	**dest;

	i = 0;
	while (var->env[i])
	{
		i++;
	}
	dest = malloc(sizeof(char *) * i + 2);
	i = 0;
	while (var->env[i])
	{
		dest[i] = ft_strdup(var->env[i], TRUE);
		i++;
	}
	free(var->env);
	dest[i++] = ft_strdup(&src[11], FALSE);
	dest[i] = 0;
	return (dest);
}

void	ft_old_pwd(t_var *var, int i)
{
	int		j;
	int		k;
	char	*tmp_env;

	tmp_env = ft_strdup("OLDPWD=", FALSE);
	j = 0;
	while (var->env[j])
	{
		if (ft_strncmp(var->env[j], "OLDPWD=", 7) == TRUE)
			break ;
		j++;
	}
	k = 0;
	while (var->exp[k])
	{
		if (ft_strncmp(var->exp[k], "declare -x OLDPWD", 17) == TRUE) // check for other OLDPWD, like OLDPWD1
		{
			if (var->exp[k][17] == EQUAL)
			{
				break ;
			}
		}
		k++;
	}
	if (!var->exp[k])
		return ;
	if (!var->env[j])
	{
		var->env = reset_env(var, var->exp[k]);
		return ; // create a new element
	}
	free(var->env[j]);
	if (!var->env[i])
	{
		free(tmp_env);
		var->env[j] = ft_strdup("OLDPWD=", FALSE);
	}
	else
		var->env[j] = ft_strjoin(tmp_env, &var->env[i][4], FALSE);
}

void	ft_old_pwd_exp(t_var *var, int i)
{
	int		j;
	char	*tmp_exp;

	tmp_exp = ft_strdup("declare -x OLDPWD=", FALSE);
	j = 0;
	while (var->exp[j])
	{
		if (ft_strncmp(var->exp[j], "declare -x OLDPWD", 17) == TRUE)
		{
			if (var->exp[j][17] == 0 || var->exp[j][17] == EQUAL)
			{
				break ;
			}
		}
		j++;
	}
	if (!var->exp[j])
		return ;
	free(var->exp[j]);
	if (!var->exp[i])
	{
		free(tmp_exp);
		var->exp[j] = ft_strdup("declare -x OLDPWD=""", FALSE);
	}
	else
		var->exp[j] = ft_strjoin(tmp_exp, &var->exp[i][15], FALSE);
}

int	ft_find_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_memcmp((char *)env[i], "HOME=", 5) != 0)
		i++;
	return (i);
}
