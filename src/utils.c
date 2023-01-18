/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:39:02 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/18 15:38:53 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(char *input, char *str)
{
	int	i;

	i = 0;
	while (str[i] && input[i])
	{
		if (str[i] != input[i])
			return (FALSE);
		i++;
	}
	if (str[i] != 0 || input[i] != 0)
		return (FALSE);
	return (TRUE);
}