/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lsts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:14:47 by max               #+#    #+#             */
/*   Updated: 2023/01/22 23:26:51 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_shell(t_shell *lst)
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

int	free_tabs(t_tabs *lst)
{
	t_tabs	*tmp;
	t_tabs	*end;
	int		i;

	end = lst;
	lst = lst->next;
	while (lst != NULL)
	{
		i = 0;
		tmp = lst;
		lst = lst->next;
		while (tmp->cmds[i])
		{
			free(tmp->cmds[i]);
			i++;
		}
		free(tmp->cmds);
		i = 0;
		while (tmp->paths[i])
		{
			free(tmp->paths[i]);
			i++;
		}
		free(tmp->paths);
		free(tmp);
	}
	lst = end;
	lst->next = NULL;
	return (0);
}