/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambiguity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:16:05 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/06 18:10:26 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_ambiguity(t_tabs **tabs)
{
	t_tabs	*tmp;

	tmp = (*tabs)->next;
	while (tmp)
	{
		tmp->ambiguity = FALSE;
		tmp = tmp->next;
	}
}

int	ft_check_ambiguity(t_tabs **tabs)
{
	int		i;
	t_tabs	*tmp;

	ft_set_ambiguity(tabs);
	tmp = (*tabs)->next;
	while (tmp)
	{
		i = 0;
		while (tmp->redop && tmp->redop[i])
		{
			if ((tmp->redop[i][0] != GREAT && tmp->redop[i][0] != SMALL) \
			|| !tmp->redop[i + 1] || tmp->redop[i + 1][0] == GREAT \
			|| tmp->redop[i + 1][0] == SMALL)
			{
				write (2, "minishell: error: ambiguous redirection\n", 40);
				tmp->ambiguity = TRUE;
				break ;
			}
			i = i + 2;
		}
		tmp = tmp->next;
	}
	return (TRUE);
}
