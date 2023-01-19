/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:38:41 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/18 15:38:57 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
A function to print the list, will be removed at the end, it's meant for testing
*/
void	ft_print_lst(t_shell **a)
{
	t_shell	*tmpa;
	int		i;

	i = 1;
	if ((*a)->next != NULL)
	{
		tmpa = (*a);
		(*a) = (*a)->next;
		while ((*a) != NULL)
		{
			printf("Element %d	| address : %p	| data : %s\n", i++, &(*a)->data, (*a)->data);
			(*a) = (*a)->next;
		}
		(*a) = tmpa;
	}
	printf("\n");
}