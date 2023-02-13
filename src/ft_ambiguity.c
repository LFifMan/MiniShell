/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambiguity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:16:05 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/13 17:41:51 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_check_ambiguity(t_tabs **tabs)
{
	int i;
	t_tabs	*tmp;

	i = 0;
	tmp = (*tabs)->next;
	while (tmp)
	{
		i = 0;
		while (tmp->redop[i])
		{
			if (tmp->redop[i][0] != GREAT || tmp->redop[i][0] != SMALL)
				return (FALSE);
			i++;
			if (tmp->redop[i][0] == GREAT || tmp->redop[i][0] == SMALL)
				return (FALSE);
			i++;
		}
		tmp = tmp->next;
	}
	return (TRUE);
}