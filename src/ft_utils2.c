/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:39:02 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/27 19:05:32 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_zero(const char *s)
{
	char	*new;

	new = malloc(sizeof (char));
	if (new == NULL)
		return (NULL);
	new[0] = s[0];
	return (new);
}

char	*ft_strjoin(char *s1, char *s2, int index)
{
	char	*dest;
	size_t	i;
	size_t	j;

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
	dest = malloc (sizeof(char) * (ft_strlen(src) + 1));
	if (!dest)
		return (0);
	while (*src)
	{
		dest[i] = *src;
		i++;
		src++;
	}
	dest[i] = 0;
	if (index == TRUE)
		free(src);
	return (dest);
}
