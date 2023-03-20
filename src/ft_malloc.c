/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:33:33 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/20 14:29:54 by max              ###   ########.fr       */
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
