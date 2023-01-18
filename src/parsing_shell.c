/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:31:32 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/18 15:37:18 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*ft_parsing_sh(char *const *envp)
{
	char	*shell_paths;
	int		i;
	int		j;
	int		c;
	int		count;

	i = 0;
	while (ft_memcmp((char *)envp[i], "SHELL=", 6) != 0)
		i++;
	j = 0;
	c = 0;
	count = 0;
	while ((char)envp[i][j] != 0)
	{
		j++;
		if ((char)envp[i][j] == '/')
			count = j;
	}
	j = j - count;
	shell_paths = malloc (sizeof(char) * j + 2);
	j = 0;
	count++;
	while ((char)envp[i][count] != 0)
	{
		shell_paths[j] = (char)envp[i][count];
		count++;
		j++;
	}
	shell_paths[j++] = '>';
	shell_paths[j++] = ' ';
	shell_paths[j] = '\0';
	return (shell_paths);
}
