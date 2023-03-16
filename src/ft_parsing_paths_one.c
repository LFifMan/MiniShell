/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_paths_one.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:56:33 by max               #+#    #+#             */
/*   Updated: 2023/03/16 13:46:05 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_paths(t_var var, t_tabs **tabs)
{
	t_tabs	*tmp;

	tmp = (*tabs);
	tmp = tmp->next;
	while (tmp)
	{
		if (!tmp->cmds)
		{
			tmp->paths = ft_parsing_binaries(var.env, "");
		}
		else
			tmp->paths = ft_parsing_binaries(var.env, tmp->cmds[0]);
		tmp = tmp->next;
	}
}

char	**ft_create_paths(void)
{
	char	**dst;

	dst = malloc(sizeof(char *));
	if (!dst)
		exit (EXIT_FAILURE);
	dst[0] = 0;
	return (dst);
}

char	**ft_parsing_binaries(char *const *envp, char *argv)
{
	char	**binaries_paths;
	int		i;

	i = 0;
	while (envp[i] && ft_memcmp((char *)envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		binaries_paths = ft_create_paths();
	else
		binaries_paths = ft_split_bin((char *)envp[i], ':', argv, 0);
	if (!binaries_paths)
		return (NULL);
	return (binaries_paths);
}

char	*ft_mallocfill_bin(char **str, char c, char *argv, int beg)
{
	int		i;
	int		start;
	char	*dst;

	start = 0;
	if (beg == 0)
		start = 5;
	i = 0;
	while (*(*str + i) && *(*str + i) != c)
		i++;
	dst = malloc(sizeof(char) * i + 2 + ft_strlen(argv) - start);
	if (!dst)
		exit (EXIT_FAILURE);
	i = 0;
	while (*(*str + start + i) && *(*str + start + i) != c)
	{
		dst[i] = *(*str + start + i);
		i++;
	}
	dst[i++] = '/';
	dst[i] = 0;
	dst = ft_strjoin(dst, argv, FALSE);
	*str += i + start;
	return (dst);
}
