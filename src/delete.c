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
void	printed(t_shell **a)
{
	t_shell	*tmpa;

	if ((*a)->next != NULL)
	{
		tmpa = (*a);
		printf("A = ");
		(*a) = (*a)->next;
		while ((*a) != NULL)
		{
			printf("%s \n", (*a)->data);
			(*a) = (*a)->next;
		}
		(*a) = tmpa;
	}
	printf("\n");
}