/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:31:32 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/31 14:24:44 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_parsing_sh(char *const *envp)
{
	char	*shell_paths;
	int		i;
	int		j;
	int		count;

	i = 0;
	while (ft_memcmp((char *)envp[i], "SHELL=", 6) != 0)
		i++;
	j = 0;
	count = 0;
	while ((char)envp[i][j] != 0)
	{
		j++;
		if ((char)envp[i][j] == '/')
			count = j;
	}
	j = j - count;
	shell_paths = malloc (sizeof(char) * j + 2);
	if (!shell_paths)
		exit (EXIT_FAILURE);
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

char	*ft_parsing_pwd(char *const *envp)
{
	char	*pwd_path;
	int		i;
	int		j;
	int		count;

	i = 0;
	while (ft_memcmp((char *)envp[i], "PWD=", 4) != 0)
		i++;
	j = 0;
	count = 0;
	while ((char)envp[i][j] != 0)
	{
		j++;
	}
	j -= 4;
	pwd_path = malloc (sizeof(char) * j + 2);
	if (!pwd_path)
		exit (EXIT_FAILURE);
	j = 0;
	count = 4;
	while ((char)envp[i][count] != 0)
	{
		pwd_path[j] = (char)envp[i][count];
		count++;
		j++;
	}
	pwd_path[j] = '\0';
	return (pwd_path);
}
