/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_utils_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/02/07 14:24:49 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_option_n(char *str)
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

int	ft_find_dir(const char *path)
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

char	*ft_create_root(char *env, int j)
{
	int		i;
	char	*root;

	i = 0;
	while (env[j])
		j++;
	root = malloc(sizeof(char) * (j - 5 + 1));
	if (!root)
		exit(EXIT_FAILURE);
	j = 5;
	while (env[j])
	{
		root[i++] = env[j++];
	}
	root[i] = 0;
	return (root);
}

void	ft_update_pwd(t_var *var, char *root)
{
	ft_update_exp(var, root);
	ft_update_env(var, root);
	g_status = 0;
}

void	ft_cd_alone(char **env, int print, t_var *var)
{
	int		i;
	char	*root;

	root = NULL;
	i = ft_find_home(env);
	if (!env[i] && print == TRUE)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		g_status = 1;
		return ;
	}
	if (env[i][5])
		root = ft_create_root(env[i], 5);
	if (chdir(root) == 0)
	{
		ft_update_pwd(var, root);
	}
	else if (print == TRUE && root)
		ft_write(root, 0, 1);
}
