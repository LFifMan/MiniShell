/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:25:26 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/10 17:23:38 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_iter_i_j(int *i, int *j)
{
	int	t_i;
	int	t_j;

	t_i = *i + 1;
	t_j = *j + 1;
	*(i) = t_i;
	*(j) = t_j;
}

int	ft_trim_count(char *cmd, int i, int j)
{
	while (cmd[i])
	{
		if (cmd[i] && cmd[i] == SQ)
		{
			i++;
			while (cmd[i] && cmd[i] != SQ)
				ft_iter_i_j(&i, &j);
			if (cmd[i])
				i++;
		}
		else if (cmd[i] && cmd[i] == DQ)
		{
			i++;
			while (cmd[i] && cmd[i] != DQ)
				ft_iter_i_j(&i, &j);
			if (cmd[i])
				i++;
		}
		else
			while (cmd[i] && cmd[i] != DQ && cmd[i] != SQ)
				ft_iter_i_j(&i, &j);
	}
	return (j);
}

char	*ft_trim_cmds(char *cmd, int size, int i, int j)
{
	char	*dest;
	char	tmp;

	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		exit (EXIT_FAILURE);
	while (cmd[i])
	{
		if (cmd[i] && (cmd[i] == SQ || cmd[i] == DQ))
		{
			tmp = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != tmp)
				dest[j++] = cmd[i++];
			if (cmd[i])
				i++;
		}
		else
			while (cmd[i] && cmd[i] != DQ && cmd[i] != SQ)
				dest[j++] = cmd[i++];
	}
	dest[j] = 0;
	free(cmd);
	return (dest);
}

void	ft_trim_quotes(t_tabs **tabs)
{
	int		i;
	int		size;
	t_tabs	*tmp;

	tmp = (*tabs)->next;
	while (tmp)
	{
		i = 0;
		while (tmp->cmds && tmp->cmds[i])
		{
			size = ft_trim_count(tmp->cmds[i], 0, 0);
			tmp->cmds[i] = ft_trim_cmds(tmp->cmds[i], size, 0, 0);
			i++;
		}
		i = 0;
		while (tmp->redop && tmp->redop[i])
		{
			size = ft_trim_count(tmp->redop[i], 0, 0);
			tmp->redop[i] = ft_trim_cmds(tmp->redop[i], size, 0, 0);
			i++;
		}
		tmp = tmp->next;
	}
}
