/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:03:27 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/03 13:53:31 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**create_export(int envp_length, char **input)
{
	int		i;
	char	**export;

	i = 0;
	export = malloc(sizeof(char *) * (envp_length + 1));
	if (!export)
		exit (EXIT_FAILURE);
	while (i < envp_length)
	{
		export[i] = ft_strdup("declare -x ", FALSE);
		export[i] = ft_join_export(export[i], input[i], TRUE);
		i++;
	}
	export[i] = 0;
	return (export);
}

char	**dup_export(t_vars *vars, int envp_length)
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

void	sort_export(int envp_length, char **export)
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

void	init_env(t_vars *vars, char **envp, int envp_length)
{
	int		i;
	char	**new_envp;

	i = 0;
	new_envp = malloc(sizeof(char *) * (envp_length + 1));
	if (!new_envp)
		exit (EXIT_FAILURE);
	while (i < envp_length)
	{
		new_envp[i] = ft_strdup(envp[i], FALSE);
		i++;
	}
	new_envp[envp_length] = 0;
	vars->envp = new_envp;
}


char	*get_root_new(char **env)
{
	int		i;

	i = 0;
	while (env[i] && ft_memcmp((char *)env[i], "HOME=", 5) != 0)
		i++;
	return (ft_strdup(&env[i][5], FALSE));

}

void	init_vars(t_vars *vars, char **envp)
{
	int		envp_length;
	char	**export;

	envp_length = 0;
	while (envp[envp_length])
		envp_length++;
	init_env(vars, envp, envp_length);
	export = dup_export(vars, envp_length);
	sort_export(envp_length, export);
	vars->export = create_export(envp_length, export);
	free_array(export, envp_length);
	vars->root = get_root_new(envp);
}
