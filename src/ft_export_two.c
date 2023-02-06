/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:43:51 by max               #+#    #+#             */
/*   Updated: 2023/02/03 13:51:22 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_new_src(char **src, char *str, int len)
{
	char	**new_src;
	int		i;

	i = 0;
	new_src = malloc(sizeof(char *) * (len + 2));
	if (!new_src)
		exit (EXIT_FAILURE);
	while (i < len)
	{
		new_src[i] = src[i];
		i++;
	}
	new_src[len] = ft_strdup(str, FALSE);
	new_src[len + 1] = 0;
	free(src);
	return (new_src);
}

char	**replace_var(char **src, char *str, int place)
{
	int		len;

	len = 0;
	while (src[len] != 0)
		len++;
	if (place < len)
	{
		free(src[place]);
		src[place] = ft_strdup(str, FALSE);
	}
	else
	{
		src = ft_new_src(src, str, len);
	}
	return (src);
}

void	ft_sort_new_export(t_var *var)
{
	int		i;
	int		envp_length;
	char	*tmp;

	i = 0;
	envp_length = 0;
	while (var->exp[envp_length])
		envp_length++;
	while (i < envp_length)
	{
		if (var->exp[i + 1] && ft_cmp_ascii(var->exp[i], var->exp[i + 1]) < 0)
		{
			tmp = var->exp[i];
			var->exp[i] = var->exp[i + 1];
			var->exp[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}
