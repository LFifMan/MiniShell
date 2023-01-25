/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verifs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:38:41 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/25 14:47:44 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
A function to print the list, will be removed at the end, it's meant for testing
*/
void	PRINT_SHELL(t_shell **a)
{
	t_shell	*tmpa;
	int		i;

	i = 1;
	printf("\n SHELL ELEMENTS\n");
	if ((*a)->next != NULL)
	{
		tmpa = (*a);
		(*a) = (*a)->next;
		while ((*a) != NULL)
		{
			printf("SHELL Element %d	| address data : %p	| index : %d | data : %s\n", i++, (*a), (*a)->index, (*a)->data);
			(*a) = (*a)->next;
		}
		(*a) = tmpa;
	}
	printf("\n");
}

void	PRINT_CMDS(t_tabs **a)
{
	t_tabs	*tmpa;
	int		i;
	int		lstnb;

	lstnb = 0;
	if ((*a)->next != NULL)
	{
		tmpa = (*a);
		(*a) = (*a)->next;
		while ((*a) != NULL)
		{
			i = 0;
			printf("CMDS ELEMENT %d:\n", lstnb + 1);
			while ((*a)->cmds[i])
			{
				printf("lst %d | index %d	| address %p	| data : %s\n", lstnb, i, (*a)->cmds[i], (*a)->cmds[i]);
				i++;
			}
			lstnb++;
			(*a) = (*a)->next;
		}
		(*a) = tmpa;
	}
	printf("\n");
}

void	PRINT_REDOP(t_tabs **a)
{
	t_tabs	*tmpa;
	int		i;
	int		lstnb;

	lstnb = 0;
	if ((*a)->next != NULL)
	{
		tmpa = (*a);
		(*a) = (*a)->next;
		while ((*a) != NULL)
		{
			i = 0;
			printf("REDOP ELEMENT %d:\n", lstnb + 1);
			while ((*a)->redop[i])
			{
				printf("lst %d | index %d	| data : %s\n", lstnb, i, (*a)->redop[i]);
				i++;
			}
			lstnb++;
			(*a) = (*a)->next;
		}
		(*a) = tmpa;
	}
	printf("\n");
}

void	PRINT_PATHS(t_tabs **a)
{
	t_tabs	*tmpa;
	int		i;
	int		lstnb;

	lstnb = 0;
	if ((*a)->next != NULL)
	{
		tmpa = (*a);
		(*a) = (*a)->next;
		while ((*a) != NULL)
		{
			i = 0;
			printf("PATHS ELEMENT %d:\n", lstnb + 1);
			while ((*a)->paths[i])
			{
				printf("lst %d | index %d	| data : %s\n", lstnb, i, (*a)->paths[i]);
				i++;
			}
			lstnb++;
			(*a) = (*a)->next;
		}
		(*a) = tmpa;
	}
	printf("\n");
}