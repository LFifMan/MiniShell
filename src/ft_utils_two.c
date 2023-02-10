/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:39:02 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/10 15:04:38 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_join(int index, char *s1, char *s2, char *dest)
{
	size_t	i;
	size_t	j;
	int		count;

	count = 0;
	i = -1;
	j = 0;
	if (!s1)
		s1 = ft_zero("\0");
	while (s1[++i])
		dest[i] = s1[i];
	while (s2 && s2[j])
	{
		if (j > 1 && s2[j - 1] == EQUAL && count++ == 0)
			dest[i++] = DQ;
		dest[i++] = s2[j++];
	}
	if (index == TRUE && count == 0)
		dest[i++] = DQ;
	if (index == TRUE)
		dest[i++] = DQ;
	dest[i] = 0;
	free(s1);
	return (dest);
}

char	*ft_join_exp(char *s1, char *s2, int index)
{
	char	*dest;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2);
	if (index == TRUE)
		size += 2;
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		exit (EXIT_FAILURE);
	return (ft_join(index, s1, s2, dest));
}

int	ft_cmp_ascii(char *input, char *str)
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

char	*ft_strjoin(char *s1, char *s2, int index)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		exit (EXIT_FAILURE);
	i = 0;
	j = -1;
	if (!s1)
		s1 = ft_zero("\0");
	if (s1)
		while (s1[++j])
			dest[j] = s1[j];
	if (s2)
		while (s2[i])
			dest[j++] = s2[i++];
	dest[j] = '\0';
	free(s1);
	if (index == TRUE)
		free(s2);
	return (dest);
}

char	*ft_strdup(char *src, int index)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc (sizeof(char) * ft_strlen(src) + 1);
	if (!dest)
		exit (EXIT_FAILURE);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	if (index == TRUE)
		free(src);
	return (dest);
}
