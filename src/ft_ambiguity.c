/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambiguity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:16:05 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/21 19:10:24 by mstockli         ###   ########.fr       */
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
		tmp->ambiguity = FALSE;
		tmp = tmp->next;
	}
	tmp = (*tabs)->next;
	while (tmp)
	{
		i = 0;
		while (tmp->redop[i])
		{
			if ((tmp->redop[i][0] != GREAT && tmp->redop[i][0] != SMALL) || !tmp->redop[i + 1] || tmp->redop[i + 1][0] == GREAT || tmp->redop[i + 1][0] == SMALL)
			{
				write (2, "minishell: error: ambiguous redirection\n", ft_strlen("minishell: error: ambiguous redirection\n"));
				tmp->ambiguity = TRUE;
				break ;
			}
			i = i + 2;
		}
		tmp = tmp->next;
	}
	return (TRUE);
}
