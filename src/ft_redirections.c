/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:03:36 by max               #+#    #+#             */
/*   Updated: 2023/01/21 16:03:59 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*ft_space_redop(t_shell **shell)
{
	t_shell *tmp;
	t_shell *new;

	new = malloc(sizeof(t_shell));
	if (!new)
		return (NULL);
	new->next = NULL;
	tmp = (*shell)->next; // error check?
	while (tmp)
	{
		if (tmp->index != GREATER && tmp->index != SMALLER)
		{
				ft_lstadd_back(&new, tmp->data);
				if (tmp->next && tmp->index != SPACE && (tmp->next->index == GREATER || tmp->next->index == SMALLER))
					ft_lstadd_back(&new, " ");
		}
		else 
		{
			ft_lstadd_back(&new, tmp->data);
			if (tmp->next && tmp->next->index != SPACE)
				ft_lstadd_back(&new, " ");
		}
		tmp = tmp->next;
	}
	//free_lst(*shell); --> does not work, I'm lost in translation
	return (new);
}
void	ft_split_redirections(t_shell **shell, char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		if (input[i] == GREATER)
		{
			while (input[i + j] == GREATER)
				j++;
			ft_lstadd_back(shell, parse_quotation(&input[i], GREATER, j, 0));
		}
		else if (input[i] == SMALLER)
		{
			while (input[i + j] == SMALLER)
				j++;
			ft_lstadd_back(shell, parse_quotation(&input[i], SMALLER, j, 0));
		}
		else if (input[i])
		{
			while (input[i + j] && input[i + j] != SMALLER && input[i + j] != GREATER)
				j++;
			ft_lstadd_back(shell, parse_quotation(&input[i], 0, j, 0));
		}
		else
			return ;
		i += j;
	}
}

t_shell	*ft_redirections(t_shell **shell)
{
	t_shell *tmp;
	t_shell *tmp2;
	t_shell *new;
	int		i;

	new = malloc(sizeof(t_shell));
	if (!new)
		return (NULL);
	new->next = NULL;
	tmp = (*shell)->next; // error check?
	tmp2 = (*shell);
	while (tmp)
	{
		i = 0;
		if (tmp->index == GREATER || tmp->index == SMALLER)
			tmp->index = CHARS;
		if (tmp->index == CHARS)
		{
			while (tmp->data[i] != GREATER && tmp->data[i] != SMALLER && tmp->data[i])
			{
				i++;
			}
			if (tmp->data[i] == GREATER || tmp->data[i] == SMALLER)
			{
				//printf("tmp data %c\n\n\n\n", tmp->data[i]);
				ft_split_redirections(&new, tmp->data);
			}
			else
				ft_lstadd_back(&new, tmp->data);
		}
		else
			ft_lstadd_back(&new, tmp->data);
		tmp = tmp->next;
	}
	*shell = tmp2;
	free_lst(*shell);
	return (new);
}
