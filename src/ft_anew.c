/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_anew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:25:26 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/08 22:39:33 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_trim_cmds(char *cmd)
{
	int	i;
	char	*dest;

	i = 0;
	while (cmd[i])
	{

		i++
	}
}

void	ft_trim_quotes(t_tabs **tabs)
{
	int		i;
	t_tabs	*tmp;

	i = 0;
	tmp = (*tabs)->next;
	while (tmp)
	{
		while (tmp->cmds[i])
		{
			tmp->cmds[i] = ft_trim_cmds(tmp->cmds[i]);
			i++;
		}
		i = 0;
		while (tmp->redop[i])
		{
			tmp->redop[i] = ft_trim_redop(tmp->cmds[i]);
			i++;
		}
		tmp = tmp->next;
	}

}