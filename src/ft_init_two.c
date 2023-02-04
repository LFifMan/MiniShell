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

char	**ft_create_exp(int envp_length, char **input)
{
	int		i;
	char	**exp;

	i = 0;
	exp = malloc(sizeof(char *) * (envp_length + 1));
	if (!exp)
		exit (EXIT_FAILURE);
	while (i < envp_length)
	{
		exp[i] = ft_strdup("declare -x ", FALSE);
		exp[i] = ft_join_exp(exp[i], input[i], TRUE);
		i++;
	}
	exp[i] = 0;
	return (exp);
}

char	**ft_dup_exp(t_vars *vars, int envp_length)
{
	int		i;
	char	**export;

	export = malloc(sizeof(char *) * (envp_length + 1));
	if (!export)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < envp_length)
	{
		export[i] = ft_strdup(vars->envp[i], FALSE);
		i++;
	}
	export[i] = 0;
	return (export);
}

void	ft_sort_exp(int envp_length, char **export)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < envp_length)
	{
		if (export[i + 1] && ft_strcmp_ascii(export[i], export[i + 1]) < 0)
		{
			tmp = export[i];
			export[i] = export[i + 1];
			export[i + 1] = tmp;
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
	char	*ret;

	i = 6;
	while (env[i])
	{
		if (env[i] < '0' || env[i] > '9')
			return (ft_strdup("SHLVL=1", FALSE));
		i++;
	}
	lvl = ft_atoi(&env[6]);
	ret = ft_itoa(lvl + 1);
	return (ft_strjoin(ft_strdup("SHLVL=", FALSE), ret, TRUE));
}
