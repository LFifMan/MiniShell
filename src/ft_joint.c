/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:39:02 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/03 13:51:18 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//char	*ft_join(int index, char *s1, char *s2, char *dest)
//{
//	size_t	i;
//	size_t	j;
//	int		count;
//
//	count = 0;
//	i = 0;
//	j = -1;
//	if (!s1)
//		s1 = ft_zero("\0");
//	if (s1)
//		while (s1[++j])
//			dest[j] = s1[j];
//	if (s2)
//	{
//		while (s2[i])
//		{
//			if (i > 1 && s2[i - 1] == EQUAL && count++ == 0)
//				dest[j++] = DOUBLEQUOTE;
//			dest[j++] = s2[i++];
//		}
//	}
//	if (index == TRUE && count == 0)
//		dest[j++] = DOUBLEQUOTE;
//	if (index == TRUE)
//		dest[j++] = DOUBLEQUOTE;
//	dest[j] = '\0';
//	free(s1);
//	return (dest);
//}
