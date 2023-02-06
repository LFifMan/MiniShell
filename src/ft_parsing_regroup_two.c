/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_regroup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:25:12 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/31 14:23:31 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_prepare_new(t_shell *new, t_shell *shell)
{
	t_shell	*tmp;
	int		i;

	tmp = shell->next;
	while (tmp)
	{
		i = 0;
		if (tmp->index == PIPE)
			tmp->index = CHARS;
		if (tmp->index == CHARS || tmp->index == GREAT || tmp->index == SMALL)
		{
			while (tmp->data[i] != PIPE && tmp->data[i])
				i++;
			if (tmp->data[i] == PIPE)
				ft_split_pipes(&new, tmp->data);
			else
				ft_lst_new(&new, tmp->data, FALSE);
		}
		else
			ft_lst_new(&new, tmp->data, FALSE);
		tmp = tmp->next;
	}
}

t_shell	*ft_create_new(void)
{
	t_shell	*new;

	new = malloc(sizeof(t_shell));
	if (!new)
		exit(EXIT_FAILURE);
	new->next = NULL;
	return (new);
}

t_shell	*parsing_pipes(t_shell *shell)
{
	t_shell	*new;

	new = ft_create_new();
	ft_prepare_new(new, shell);
	ft_free_shell(shell);
	free(shell);
	return (new);
}
