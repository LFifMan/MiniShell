/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:03:27 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/06 20:04:15 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_create_exp(int len_env, char **exp)
{
	int		i;
	char	**new_exp;

	i = 0;
	new_exp = malloc(sizeof(char *) * (len_env + 1));
	if (!new_exp)
		exit (EXIT_FAILURE);
	while (i < len_env)
	{
		new_exp[i] = ft_strdup("declare -x ", FALSE);
		if (ft_strncmp(exp[i], "OLDPWD", 6) == TRUE)
			new_exp[i] = ft_join_exp(new_exp[i], exp[i], FALSE);
		else
			new_exp[i] = ft_join_exp(new_exp[i], exp[i], TRUE);
		i++;
	}
	new_exp[i] = 0;
	return (new_exp);
}

char	**ft_dup_exp(t_var *var, int len_env)
{
	int		i;
	char	**new_exp;

	new_exp = malloc(sizeof(char *) * (len_env + 1));
	if (!new_exp)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < len_env - 1)
	{
		new_exp[i] = ft_strdup(var->env[i], FALSE);
		i++;
	}
	new_exp[i] = ft_strdup("OLDPWD", FALSE);
	i++;
	new_exp[i] = 0;
	return (new_exp);
}

void	ft_sort_exp(int len_env, char **exp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < len_env)
	{
		if (exp[i + 1] && ft_cmp_ascii(exp[i], exp[i + 1]) < 0)
		{
			tmp = exp[i];
			exp[i] = exp[i + 1];
			exp[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

char	*ft_shlvl(char *env)
{
	int		i;
	int		lvl;
	char	*new_lvl;

	i = 6;
	while (env[i])
	{
		if (env[i] < '0' || env[i] > '9')
			return (ft_strdup("SHLVL=1", FALSE));
		i++;
	}
	lvl = ft_atoi(&env[6]);
	new_lvl = ft_itoa(lvl + 1);
	return (ft_strjoin(ft_strdup("SHLVL=", FALSE), new_lvl, TRUE));
}
