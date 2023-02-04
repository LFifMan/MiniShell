/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_free_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:14:47 by max               #+#    #+#             */
/*   Updated: 2023/01/31 14:19:39 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_free_shell(t_shell *lst)
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
		free(tmp);
	}
	lst = end;
	lst->next = NULL;
	return (0);
}

int	ft_free_tabs(t_tabs *lst)
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

void	ft_free_lst(t_shell *shell, t_tabs *tabs, char *input, int index)
{
	free(input);
	if (index > 0)
	{
		ft_free_shell(shell);
		if (index == 2)
		{
			ft_free_tabs(tabs);
			free(tabs);
		}
	}
}

void	ft_free_vars(t_vars vars)
{
	int	i;

	i = 0;
	while (vars.envp[i])
		free(vars.envp[i++]);
	free(vars.envp);
	i = 0;
	while (vars.export[i])
		free(vars.export[i++]);
	free(vars.export);
}

void	ft_free_array(char **exp, int len_env)
{
	int	i;

	i = 0;
	while (i < len_env)
	{
		free(exp[i]);
		i++;
	}
	free(exp);
}
