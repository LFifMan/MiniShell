/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:56:33 by max               #+#    #+#             */
/*   Updated: 2023/01/27 18:13:16 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_paths(t_vars vars, t_tabs **tabs)
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

char	**ft_create_paths(char *argv)
{
	char	**dst;

	dst = malloc(sizeof(char *) * 2 + 1);
	if (!dst)
		return (NULL);
	dst[0] = ft_strjoin("/bin/", argv, FALSE); // TODO: NOT FREE S1
	dst[1] = ft_strjoin("/usr/bin/", argv, FALSE);// TODO: NOT FREE S1
	dst[2] = 0;
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
		binaries_paths = ft_create_paths(argv);
	else
		binaries_paths = ft_split_bin((char *)envp[i], ':', argv);
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
		return (NULL);
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

int	ft_countwords(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != 0)
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

char	**ft_split_bin(char *str, char c, char *argv)
{
	int		count;
	int		i;
	int		j;
	char	**dst;
	char	*str_ptr;

	count = ft_countwords(str, c);
	dst = malloc(sizeof(char *) * (count + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (str[j] != '\0' && i < count)
	{
		while (str[j] && str[j] == c)
			j++;
		if (str[j] && str[j] != c)
		{
			str_ptr = &str[j];
			dst[i] = ft_mallocfill_bin(&str_ptr, c, argv, i);
			if (!dst[i])
				return (NULL);
			i++;
		}
		if (str[j] == '\0')
			break;

	}
	dst[i] = 0;
	return (dst);
}