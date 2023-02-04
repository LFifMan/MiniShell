/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:03:27 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/03 16:49:25 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_root_new(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_memcmp((char *)env[i], "HOME=", 5) != 0)
		i++;
	return (ft_strdup(&env[i][5], FALSE));
}

void	ft_init_env(t_vars *vars, char **envp, int len_env)
{
	int		i;
	char	**new_envp;

	i = 0;
	new_envp = malloc(sizeof(char *) * (len_env + 1));
	if (!new_envp)
		exit (EXIT_FAILURE);
	while (i < len_env)
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == TRUE)
			new_envp[i] = ft_shlvl(envp[i]);
		else
			new_envp[i] = ft_strdup(envp[i], FALSE);
		i++;
	}
	new_envp[len_env] = 0;
	vars->envp = new_envp;
}

void	ft_init_vars(t_vars *vars, char **envp)
{
	int		len_env;
	char	**exp;

	len_env = 0;
	while (envp[len_env])
		len_env++;
	ft_init_env(vars, envp, len_env);
	exp = ft_dup_exp(vars, len_env);
	ft_sort_exp(len_env, exp);
	vars->export = ft_create_exp(len_env, exp);
	ft_free_array(exp, len_env);
	vars->root = get_root_new(envp);
}
