/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_dolla.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:29:16 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/08 19:58:13 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	ft_look_for_dollar(char *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data[i])
// 	{
// 		if (data[i] == SQ) // put to a function
// 		{
// 			i++;
// 			while (data[i] != SQ)
// 				i++;
// 		}
// 		else if (data[i] == DQ) // put to a function
// 		{
// 			i++;
// 			while (data[i] != DQ)
// 				i++;
// 		}
// 		else
// 		{
// 			while (data[i] != DQ && data[i] != SQ)
// 			{

// 			}
// 		}
// 		while (data[i] && data[i] != SQ)
// 		{

// 		}

// 		if (data[i] == DOLLAR)
// 			if (data[i + 1] != SPACE && data[i + 1] != 0)
// 				return (TRUE);
// 		i++;
// 	}
// 	return (FALSE);
// }


// void	ft_pars_dollar2(t_tabs **tabs, t_var *var)
// {
// 	t_tabs	*tmp;
// 	int		i;

// 	i = 0;

// 	tmp = (*tabs)->next;
// 	while (tmp)
// 	{
// 		while (tmp->cmds[i])
// 		{
// 			while (ft_look_for_dollar(tmp->cmds[i]) == TRUE)
// 					tmp->data = ft_to_be_named(var->env, tmp->data, var->tmp_g);
// 			i++;
// 		}
// 		i = 0;
// 		while (tmp->redop[i])
// 		{
// 			if (tmp->index == DQ || tmp->index == CHARS || tmp->index == DOLLAR)
// 				while (ft_look_for_dollar(tmp->data) == TRUE)
// 					tmp->data = ft_to_be_named(var->env, tmp->data, var->tmp_g);
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// }

// 			if (tmp->cmds[i][0] == DQ || tmp->cmds[i][0] == CHARS || tmp->cmds[i][0] == DOLLAR)
