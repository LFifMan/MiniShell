/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reparse_spaces_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:39:45 by max               #+#    #+#             */
/*   Updated: 2023/03/20 17:34:38 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_start(char *cmd, int end)
{
	while (cmd[end] && (cmd[end] == SPACE))
	{
		end++;
	}
	if (!cmd[end])
		return (-1);
	return (end);
}

int	find_end(char *cmd, int i)
{
	while (cmd[i] && cmd[i] != SPACE)
	{
		if (cmd[i] && (cmd[i] == SQ || cmd[i] == DQ))
		{
			i = ft_incr_quotes(cmd, i, cmd[i]);
			if (cmd[i] == SPACE || cmd[i] == 0)
				break ;
		}
		else
		{
			i = ft_incr_chars(cmd, i);
			if (cmd[i] == SPACE || cmd[i] == 0)
				break ;
		}
	}
	return (i);
}

char	*fill_malloc(char *cmd, int start, int end)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_malloc_str((end - start + 1));
	while (start < end)
	{
		result[i++] = cmd[start++];
	}
	result[i] = 0;
	return (result);
}
