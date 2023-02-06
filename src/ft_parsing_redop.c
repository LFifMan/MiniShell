/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_redop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:38:54 by max               #+#    #+#             */
/*   Updated: 2023/01/31 14:23:00 by mstockli         ###   ########.fr       */
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
		if (cmd[i][0] == GREAT || cmd[i][0] ==  SMALL)
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
	if (!dst)
		exit (EXIT_FAILURE);
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
//
//int	ft_uugt(t_tabs *tmp, int i, int j)
//{
//
//	return (j);
//}

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
		if (!tmp->redop)
			exit (EXIT_FAILURE);
		tmp->redop[0] = 0;
		while (tmp->cmds[i])
		{
			if (tmp->cmds[i][0] == GREAT || tmp->cmds[i][0] == SMALL)
			{
				tmp->redop[j] = tmp->cmds[i];
				tmp->redop[j + 1] = tmp->cmds[i + 1];
				tmp->cmds = ft_remove_redop_cmds(tmp->cmds, i);
				j = j + 2;
			}
			else
				i++;
		}
		tmp->redop[j] = 0;
		tmp->cmds[i] = 0;
		tmp = tmp->next;
	}
}
