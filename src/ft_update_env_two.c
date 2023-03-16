/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/03/10 14:36:23 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_old(t_var *var)
{
	int	k;

	k = -1;
	while (var->exp[++k])
	{
		if (ft_strncmp(var->exp[k], "declare -x OLDPWD=\"", 19) == TRUE)
		{
			if (var->exp[k][19] != DQ)
			{
				break ;
			}
		}
	}
	return (k);
}
