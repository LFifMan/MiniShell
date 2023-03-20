/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_paths_two.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:56:33 by max               #+#    #+#             */
/*   Updated: 2023/03/16 13:46:18 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**ft_split_bin(char *str, char c, char *argv, int i)
{
	int		count;
	int		j;
	char	**dst;
	char	*str_ptr;

	count = ft_countwords(str, c);
	dst = ft_malloc_array(count);
	j = 0;
	while (str[j] != '\0' && i < count)
	{
		if (str[j] && str[j] != c)
		{
			str_ptr = &str[j];
			dst[i] = ft_mallocfill_bin(&str_ptr, c, argv, i);
			i++;
		}
		while (str[j] && str[j] != c)
			j++;
		if (str[j] == c)
			j++;
	}
	dst[i] = 0;
	return (dst);
}
