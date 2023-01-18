/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:45:45 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/18 15:37:18 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_lst(t_shell *lst)
{
	t_shell	*tmp;
	t_shell	*end;

	end = lst;
	lst = lst->next;
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->data);
		//free(tmp);
	}
	lst = end;
	lst->next = NULL;
	return (0);
}

int	ft_lstsize(t_shell **lst)
{
	t_shell	*tmp;
	int		i;

	tmp = (*lst)->next;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_lstadd_back(t_shell **lst, char *input)
{
	t_shell	*tmp;
	t_shell	*curr;
	int		i;

	tmp = malloc(sizeof(t_shell));
	if (!tmp)
		return ;
	tmp->next = NULL;
	if (input[0] == 34 || input[0] == 39) // create an index to know if the lst is a quotation or not
		tmp->index = 1;
	else
		tmp->index = 0;
	i = 0;
	tmp->data = malloc(sizeof(char) * ft_strlen(input) + 1);
	if (!tmp->data)
		return ;
	while (input[i])
	{
		tmp->data[i] = input[i];
		i++;
	}
	tmp->data[i] = 0;
	curr = *lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = tmp;
	free (input);
}
