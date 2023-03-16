/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/03/10 14:37:18 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_update_env(t_var *var, char *path)
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
	ft_old_env(var, i);
	if (!var->env[i])
		return ;
	ft_strcpy(tmp_env, "PWD=");
	tmp_env = ft_strjoin(tmp_env, getcwd(NULL, 0), FALSE);
	free(var->env[i]);
	var->env[i] = tmp_env;
}

int	ft_check_old_env(t_var *var)
{
	int	i;

	i = 0;
	while (var->env[i])
	{
		if (ft_strncmp(var->env[i], "OLDPWD=", 7) == TRUE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	deset_env(t_var *var)
{
	int		i;
	int		j;
	char	**dest;

	i = 0;
	j = 0;
	if (ft_check_old_env(var) == FALSE)
		return ;
	while (var->env[i])
		i++;
	dest = malloc(sizeof(char *) * (i));
	i = 0;
	while (var->env[i])
	{
		dest[j] = ft_strdup(var->env[i], TRUE);
		i++;
		j++;
		if (var->env[i] && ft_strncmp(var->env[i], "OLDPWD=", 7) == TRUE)
			free(var->env[i++]);
	}
	free(var->env);
	dest[j] = 0;
	var->env = dest;
}

void	reset_env(t_var *var, char *src)
{
	int		i;
	char	**dest;

	i = 0;
	while (var->env[i])
	{
		i++;
	}
	dest = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (var->env[i])
	{
		dest[i] = ft_strdup(var->env[i], TRUE);
		i++;
	}
	free(var->env);
	dest[i++] = ft_strjoin(ft_strdup("OLDPWD=", FALSE), \
	ft_strdup(ft_trim_quotations(&src[18]), TRUE), TRUE);
	dest[i] = 0;
	var->env = dest;
}

void	ft_old_env(t_var *var, int i)
{
	int		j;
	int		k;
	char	*tmp_env;

	tmp_env = ft_strdup("OLDPWD=", FALSE);
	j = -1;
	while (var->env[++j])
		if (ft_strncmp(var->env[j], "OLDPWD=", 7) == TRUE)
			break ;
	k = ft_check_old(var);
	if (!var->exp[k])
		return (deset_env(var));
	if (!var->env[j])
		return (reset_env(var, var->exp[k]));
	free(var->env[j]);
	if (!var->env[i])
	{
		free(tmp_env);
		var->env[j] = ft_strdup("OLDPWD=", FALSE);
	}
	else
		var->env[j] = ft_strjoin(tmp_env, &var->env[i][4], FALSE);
}
