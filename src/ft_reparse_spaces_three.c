/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reparse_spaces_three.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:39:45 by max               #+#    #+#             */
/*   Updated: 2023/03/20 17:36:18 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_incr_spaces(char *cmd, int i)
{
	while (cmd[i] && cmd[i] == SPACE)
		i++;
	return (i);
}

int	ft_incr_quotes(char *cmd, int i, char c)
{
	i++;
	while (cmd[i] && cmd[i] != c)
		i++;
	if (cmd[i])
		i++;
	return (i);
}

int	ft_incr_chars(char *cmd, int i)
{
	while (cmd[i] && cmd[i] != DQ && cmd[i] != SQ && cmd[i] != SPACE)
		i++;
	return (i);
}

int	count_words(char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == SPACE)
			i = ft_incr_spaces(cmd, i);
		else if (cmd[i] && (cmd[i] == SQ || cmd[i] == DQ))
		{
			i = ft_incr_quotes(cmd, i, cmd[i]);
			if (cmd[i] == SPACE || cmd[i] == 0)
				count++;
		}
		else
		{
			i = ft_incr_chars(cmd, i);
			if (cmd[i] == SPACE || cmd[i] == 0)
				count++;
		}
	}
	return (count);
}

int	count_total_words(char **cmd)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (cmd[i])
	{
		size += count_words(cmd[i]);
		i++;
	}
	return (size);
}
