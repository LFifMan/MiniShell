/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verifs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:38:41 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/20 03:33:35 by max              ###   ########.fr       */
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

void	ft_print_tabs_cmds(t_tabs **a)
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
			printf("ELEMENT %d:\n", lstnb + 1);
			while ((*a)->cmds[i])
			{
				printf("lst %d | index %d	| data : %s\n", lstnb, i, (*a)->cmds[i]);
				i++;
			}
			lstnb++;
			(*a) = (*a)->next;
		}
		(*a) = tmpa;
	}
	printf("\n");
}

void	ft_print_tabs_paths(t_tabs **a)
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
			printf("ELEMENT %d:\n", lstnb + 1);
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