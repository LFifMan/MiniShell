/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:33:33 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/16 13:44:18 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_malloc_str(int size)
{
	char	*dest;

	dest = malloc(sizeof(char) * (size));
	if (!dest)
		exit (EXIT_FAILURE);
	return (dest);
}

char	**ft_malloc_array(int size)
{
	char	**dest;

	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		exit (EXIT_FAILURE);
	return (dest);
}
