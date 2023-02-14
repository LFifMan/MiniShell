/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:25:26 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/14 14:24:15 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_trim_count(char *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] && cmd[i] == SQ)
		{
			i++;
			while (cmd[i] && cmd[i] != SQ)
			{
				i++;
				j++;
			}
			i++;
		}
		else if (cmd[i] && cmd[i] == DQ)
		{
			i++;
			while (cmd[i] && cmd[i] != DQ)
			{
				i++;
				j++;
			}
			i++;
		}
		else
		{
			while (cmd[i] && cmd[i] != DQ && cmd[i] != SQ)
			{
				i++;
				j++;
			}
		}
	}
	return (j);
}

char	*ft_trim_cmds(char *cmd, int size)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		exit (EXIT_FAILURE);
	while (cmd[i])
	{
		if (cmd[i] && cmd[i] == SQ)
		{
			i++;
			while (cmd[i] && cmd[i] != SQ)
			{
				dest[j] = cmd[i];
				i++;
				j++;
			}
			i++;
		}
		else if (cmd[i] && cmd[i] == DQ)
		{
			i++;
			while (cmd[i] && cmd[i] != DQ)
			{
				dest[j] = cmd[i];
				i++;
				j++;
			}
			i++;
		}
		else
		{
			while (cmd[i] && cmd[i] != DQ && cmd[i] != SQ)
			{
				dest[j] = cmd[i];
				i++;
				j++;
			}
		}
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
		if (tmp->cmds)
		{
			while (tmp->cmds[i])
			{
				size = ft_trim_count(tmp->cmds[i]);
				tmp->cmds[i] = ft_trim_cmds(tmp->cmds[i], size);
				i++;
			}
		}
		i = 0;
		if (tmp->redop)
		{	
			while (tmp->redop[i])
			{
				size = ft_trim_count(tmp->redop[i]);
				tmp->redop[i] = ft_trim_cmds(tmp->redop[i], size);
				i++;
			}
		}
		tmp = tmp->next;
	}
}
