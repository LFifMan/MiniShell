/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lsts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:14:47 by max               #+#    #+#             */
/*   Updated: 2023/01/30 17:57:58 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_shell(t_shell *lst)
{
	t_shell	*tmp;
	t_shell	*end;

	end = lst;
	lst = lst->next;
	// printf("FREE SHELL\n");
	while (lst != NULL)
	{
		tmp = lst;
		// printf("tmp : %p	| tmp->data adress : %p	| tmp->data : %s\n", tmp, tmp->data, tmp->data);
		lst = lst->next;
		free(tmp->data);
		free(tmp);
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
	//printf("malloc cmd %p path %p redop %p\n", lst->cmds, lst->paths, lst->redop);
	while (lst != NULL)
	{
		i = 0;
		tmp = lst;
		//printf("\nFREE CMDS\n");
		while (tmp->cmds[i])
		{
			//printf("cmd : %p	| cmd->data adress : %p	| cmd->data : %s\n", tmp->cmds, tmp->cmds[i], tmp->cmds[i]);
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
		i = 0;
		while (tmp->redop[i])
		{
			free(tmp->redop[i]);
			i++;
		}
		free(tmp->redop);
		lst = lst->next;
		free(tmp);

	}
	lst = end;
	lst->next = NULL;
	return (0);
}

void	free_lsts(t_shell *shell, t_tabs *tabs, char *input, int index)
{
	free(input);
	if (index > 0)
	{
		free_shell(shell);
		if (index == 2)
		{
			free_tabs(tabs);
			free(tabs);
		}
	}
}