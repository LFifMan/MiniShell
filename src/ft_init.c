/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:03:27 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/30 19:10:16 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


char	*ft_strjoin_quotes(char *s1, char *s2, int index)
{
	char	*dest;
	size_t	i;
	size_t	j;
	int		db;

	db = 0;
	if (index == TRUE)
		dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 3));
	else
		dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (0);
	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_zero("\0");
	if (s1)
	{
		while (s1[j])
		{
			dest[j] = s1[j];
			j++;
		}
	}
	if (s2)
	{
		while (s2[i])
		{
			if (s2[i] == EQUAL)
			{
				db = 1;
				dest[j++] = s2[i++];
				dest[j++] = DOUBLEQUOTE;
			}
			else
				dest[j++] = s2[i++];
		}
	}
	if (index == TRUE)
		dest[j++] = DOUBLEQUOTE;
	dest[j] = '\0';
	free(s1);
	return (dest);
}

int	ft_strcmp_ascii(char *input, char *str)
{
	int	i;

	i = 0;
	if (!input)
		return (FALSE);
	while (str[i] != EQUAL && input[i] != EQUAL)
	{
		if (str[i] != input[i])
			return (str[i] - input[i]);
		i++;
	}
	if (str[i] == EQUAL)
		return (-1);
	return (1);
}

char	**create_export(int envp_length, char **input)
{
	int	i;
	char	**export;

	i = 0;
	export = malloc(sizeof(char *) * (envp_length + 1));
	while (i < envp_length)
	{
		export[i] = ft_strdup("declare -x ", FALSE);
		export[i] = ft_strjoin_quotes(export[i], input[i], TRUE);
		
		i++;
	}
	export[i] = 0;
	return (export);
}

void	free_array(char **export, int envp_length)
{
	int	i;

	i = 0;
	while (i < envp_length)
	{
		free(export[i]);
		i++;
	}
	free(export[i]);
	free(export);
}
char	**dup_export(t_vars *vars, char **export, int envp_length)
{
	int	i;

	i = 0;
	while (i < envp_length)
	{
		export[i] = ft_strdup(vars->envp[i], FALSE);
		i++;
	}
	export[i] = 0;	
	return (export);
}

void	sort_export(t_vars *vars, int envp_length)
{
	int		i;
	char	**export;
	char	*tmp;

	export = malloc(sizeof(char *) * (envp_length + 1));
	if (!export)
		return ;
	export = dup_export(vars, export, envp_length);
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
	vars->export = create_export(envp_length, export);
	free_array(export, envp_length);
}

void	init_vars(t_vars *vars, char **envp)
{
	int		envp_length;
	int		i;
	char	**new_envp;

	envp_length = 0;
	i = 0;
	while (envp[envp_length])
		envp_length++;
	new_envp = malloc(sizeof(char *) * (envp_length + 1));
	while (i < envp_length)
	{
		new_envp[i] = ft_strdup(envp[i], FALSE);
		i++;
	}
	new_envp[envp_length] = 0;
	vars->envp = new_envp;
	sort_export(vars, envp_length);
}
