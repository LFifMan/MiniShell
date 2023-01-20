/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:56:33 by max               #+#    #+#             */
/*   Updated: 2023/01/20 03:06:59 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parsing_paths(t_vars vars, t_tabs **tabs)
{
	t_tabs	*tmp;

	tmp = (*tabs);
	tmp = tmp->next;
	while (tmp)
	{
		tmp->paths = ft_parsing_binaries(vars.envp, tmp->cmds[0]);
		tmp = tmp->next;
	}
}

char	**ft_parsing_binaries(char *const *envp, char *argv)
{
	char	**binaries_paths;
	int		i;

	i = 0;
	while (ft_memcmp((char *)envp[i], "PATH=", 5) != 0)
		i++;
	binaries_paths = ft_split_bin((char *)envp[i], ':', argv);
	if (!binaries_paths)
		return (NULL);
	return (binaries_paths);
}

char	*ft_mallocfill_bin(char **s, char c, char *argv, int beg)
{
	int		i;
	int		start;
	char	*dst;

	start = 0;
	if (beg == 0)
		start = 5;
	i = 0;
	while (*(*s + i) && *(*s + i) != c)
		i++;
	dst = malloc(sizeof(char) * i + 2 + ft_strlen(argv) - start);
	if (!dst)
		return (NULL);
	i = 0;
	while (*(*s + start + i) && *(*s + start + i) != c)
	{
		dst[i] = *(*s + start + i);
		i++;
	}
	dst[i++] = '/';
	dst[i] = 0;
	dst = ft_strjoin(dst, argv);
	*s += i + start;
	return (dst);
}

int	ft_countwords(char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != 0)
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

char	**ft_split_bin(char *s, char c, char *argv)
{
	int		count;
	int		i;
	char	**dst;

	count = ft_countwords(s, c);
	dst = malloc(sizeof(char *) * (count + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (*s && i < count)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			dst[i] = ft_mallocfill_bin(&s, c, argv, i);
			if (!dst[i])
				return (NULL);
			i++;
		}
	}
	dst[i] = 0;
	return (dst);
}