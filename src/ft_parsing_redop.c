/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_redop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:38:54 by max               #+#    #+#             */
/*   Updated: 2023/02/09 19:10:39 by mstockli         ###   ########.fr       */
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
		if (cmd[i][0] == GREAT || cmd[i][0] == SMALL)
			count++;
		i++;
	}
	count = count * 2;
	return (count);
}

char	**ft_remove_redop_cmds(char **cmd, int index)
{
	char	**dst;
	int		i;
	int		j;

	(void)index;
	i = 0;
	while (cmd[i])
		i++;
	dst = malloc(sizeof(char *) * (i - ft_count_redops(cmd) + 1));
	if (!dst)
		exit (EXIT_FAILURE);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == GREAT || cmd[i][0] == SMALL)
			i = i + 2;
		else
			dst[j++] = ft_strdup(cmd[i++], FALSE);
	}
	dst[j] = 0;
	ft_free_array(cmd, i);
	return (dst);
}

int	ft_tmp_redop(t_tabs *tmp, int i, int j)
{
	tmp->redop[j] = ft_strdup(tmp->cmds[i], FALSE);
	tmp->redop[j + 1] = ft_strdup(tmp->cmds[i + 1], FALSE);
	j = j + 2;
	return (j);
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
		tmp->redop = ft_malloc_array((ft_count_redops(tmp->cmds) + 1));
		tmp->redop[0] = 0;
		while (tmp->cmds[i])
		{
			if (tmp->cmds[i][0] == GREAT || tmp->cmds[i][0] == SMALL)
				j = ft_tmp_redop(tmp, i++, j);
			i++;
		}
		tmp->redop[j] = 0;
		tmp->cmds = ft_remove_redop_cmds(tmp->cmds, 0);
		tmp = tmp->next;
	}
}
