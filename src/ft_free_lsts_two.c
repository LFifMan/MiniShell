/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lst_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:14:47 by max               #+#    #+#             */
/*   Updated: 2023/01/31 14:19:39 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
