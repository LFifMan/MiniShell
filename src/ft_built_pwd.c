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

void	ft_pwd_exp(t_var *var, char *path)
{
	char	*tmp_exp;
	int		i;

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
	printf("ici4\n");
	ft_old_pwd_exp(var, i);
	if (!var->exp[i])
		return ;
	printf("ici5\n");
	ft_strcpy(tmp_exp, "declare -x PWD=");
	printf("ici6\n");
	tmp_exp = ft_strjoin(tmp_exp, path, FALSE);
	free(var->exp[i]);
	var->exp[i] = tmp_exp;
}

void	ft_pwd(t_var *var, char *path)
{
	char	*tmp_env;
	int		i;

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
	ft_strcpy(tmp_env, "PWD=");
	tmp_env = ft_strjoin(tmp_env, path, FALSE);
	free(var->env[i]);
	var->env[i] = tmp_env;
}

void	ft_old_pwd(t_var *var, int i)
{
	int		j;
	char	*tmp_env;

	tmp_env = ft_strdup("OLDPWD=", FALSE);
	j = 0;
	while (var->env[j])
	{
		if (ft_strncmp(var->env[j], "OLDPWD=", 7) == TRUE)
			break ;
		j++;
	}
	free(var->env[j]);
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
		if (ft_strncmp(var->exp[j], "declare -x OLDPWD=", 18) == TRUE)
			break ;
		j++;
	}
	free(var->exp[j]);
	if (!var->exp[i])
	{
		free(tmp_exp);
	}
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
