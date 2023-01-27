/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_redop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:38:54 by max               #+#    #+#             */
/*   Updated: 2023/01/27 19:05:09 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_redops(char **cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == GREATER || cmd[i][0] ==  SMALLER)
			count++;
		i++;
	}
	count = count * 2;
	return (count);
}

char	**ft_remove_redop_cmds(char **cmd, int index)
{
	char	**dst;
	int		size;
	int		i;
	int		j;

	size = 0;
	while (cmd[size])
		size++;
	dst = malloc(sizeof(char *) * size - 2);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (i == index || i == index + 1)
			i++;
		else
		{
			dst[j] = cmd[i];
			i++;
			j++;
		}
	}
	dst[j] = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	i = 0;
	return (dst);	
}

void	ft_redops(t_tabs **tabs)
{
	int		i;
	int		j;
	t_tabs	*tmp;

	tmp = (*tabs);
	tmp = tmp->next;
	while (tmp)
	{
		i = 0;
		j = 0;
		tmp->redop = malloc (sizeof(char *) * (ft_count_redops(tmp->cmds) + 1));
		tmp->redop[0] = 0;
		while (tmp->cmds[i])
		{
			if (tmp->cmds[i][0] == GREATER || tmp->cmds[i][0] ==  SMALLER)
			{
				tmp->redop[j] = tmp->cmds[i];
				tmp->redop[j + 1] = tmp->cmds[i + 1];
				tmp->cmds = ft_remove_redop_cmds(tmp->cmds, i);
				j = j + 2;
			}
			else
				i++;
		}
		tmp->redop[j] = malloc (sizeof(char));
		tmp->redop[j] = 0;
		tmp->cmds[i] = 0;
		tmp = tmp->next;
	}
}
