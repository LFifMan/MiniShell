/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:38:54 by max               #+#    #+#             */
/*   Updated: 2023/02/09 18:11:55 by mstockli         ###   ########.fr       */
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

	i = 0;
	while (cmd[i])
		i++;
	dst = malloc(sizeof(char) * (i - ft_count_redops(cmd) + 1));
	if (!dst)
		exit (EXIT_FAILURE);
	




	printf("the i %d\n", i);
	if (i < 3)
	{
		dst = NULL;
		return (dst);
	
	}
	dst = ft_malloc_array(i - 1);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (i == index || i == index + 1)
			i++;
		else
			dst[j++] = cmd[i++];
	}
	dst[j] = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
	i = 0;
	return (dst);
}

int	ft_tmp_redop(t_tabs *tmp, int i, int j)
{
	tmp->redop[j] = tmp->cmds[i];
	tmp->redop[j + 1] = tmp->cmds[i + 1];
	//printf("tmp->cmds %s\n", tmp->cmds);
	j = j + 2;
	return (j);
}

void	ft_redops(t_tabs **tabs)
{
	int		i;
	int		j;
	t_tabs	*tmp;
	char	**new_cmd;

	tmp = (*tabs);
	tmp = tmp->next;
	printf("REDOPS = \n");
	while (tmp)
	{

		i = 0;
		j = 0;
		tmp->redop = ft_malloc_array((ft_count_redops(tmp->cmds) + 1));
		tmp->redop[0] = 0;
		while (tmp->cmds[i])
		{
			printf("REDOPS  %d = %s\n", i, tmp->cmds[i]);
			if (tmp->cmds[i][0] == GREAT || tmp->cmds[i][0] == SMALL)
			{
				j = ft_tmp_redop(tmp, i, j);
			}
			else
				i++;
			// if (!tmp->cmds)
			// 	break;
		}
		tmp->redop[j] = 0;
		tmp->cmds = ft_remove_redop_cmds(tmp->cmds, i);
		tmp = tmp->next;
		printf("NEXT!!!\n");
	}
}












void	ft_edit_tabs(t_tabs **tabs)
{
	char	**new_cmd;
	char	**new_redop;
	t_tabs	*tmp;

	tmp = (*tabs);
	tmp = tmp->next; // check if empty?
	while (tmp)
	{
		new_redop = ft_malloc_array((ft_count_redops(tmp->cmds) + 1));

		

		tmp = tmp->next;
	}


}
