/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:39:02 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/23 20:54:45 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(char *input, char *str)
{
	int	i;

	i = 0;
	if (!input)
		return (FALSE);
	while (str[i] && input[i])
	{
		if (str[i] != input[i])
			return (FALSE);
		i++;
	}
	if (str[i] != 0 || input[i] != 0)
		return (FALSE);
	return (TRUE);
}

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	i = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}

char	*ft_zero(const char *s)
{
	char	*new;

	new = malloc(sizeof (char));
	if (new == NULL)
		return (NULL);
	new[0] = s[0];
	return (new);
}

char	*ft_strjoin(char *s1, char const *s2)
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

	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc (sizeof(char) * ft_strlen(src) + 1);
	if (!dest)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i + 1 < size)
	{
		dest[i] = src[i];
		i++;
	}
	if (size != 0)
		dest[i] = '\0';
	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

int		ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		if (i < (n - 1))
			i++;
		else
			return (TRUE);
	}
	return ((FALSE));
}