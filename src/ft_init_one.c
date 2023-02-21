/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:03:27 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/21 19:03:04 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_root_new(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_memcmp((char *)env[i], "HOME=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	return (ft_strdup(&env[i][5], FALSE));
}

void	ft_init_env(t_var *var, char **env, int len_env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (len_env + 1));
	if (!new_env)
		exit (EXIT_FAILURE);
	while (env[j])
	{
		if (ft_strncmp(env[j], "SHLVL=", 6) == TRUE)
			new_env[i++] = ft_shlvl(env[j]);
		else if (ft_strncmp(env[j], "OLDPWD=", 7) == FALSE && \
		ft_strncmp(env[j], "PWD=", 4) == FALSE)
			new_env[i++] = ft_strdup(env[j], FALSE);
		j++;
	}
	new_env[i++] = ft_strjoin(ft_strdup("PWD=", FALSE), getcwd(NULL, 0), TRUE);
	new_env[i] = 0;
	var->env = new_env;
}

void	ft_init_var(t_var *var, char **env)
{
	int		len_env;
	int		pwds;
	char	**exp;

	len_env = 0;
	pwds = 2;
	while (env[len_env])
	{
		if (ft_strncmp(env[len_env], "OLDPWD=", 7) == TRUE || \
		ft_strncmp(env[len_env], "PWD=", 4) == TRUE)
			pwds--;
		len_env++;
	}
	len_env = len_env + pwds;
	ft_init_env(var, env, len_env - 1);
	exp = ft_dup_exp(var, len_env);
	ft_sort_exp(len_env, exp);
	var->exp = ft_create_exp(len_env, exp);
	ft_free_array(exp, len_env);
	var->home = get_root_new(env);
}
