/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:38:15 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/03 16:39:22 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dest(int n, int count)
{
	char	*dest;
	int		i;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648", FALSE));
	dest = (char *)malloc(sizeof(char) * (count + 2));
	if (!dest)
		return (0);
	dest[count + 1] = 0;
	if (n < 0)
	{
		dest[i] = '-';
		n = n * -1;
		i++;
	}
	while (count >= i)
	{
		dest[count] = (n % 10) + '0';
		n = n / 10;
		count--;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	int		count;
	int		tmp;

	tmp = n;
	count = -1;
	if (tmp < 0)
	{
		count++;
		tmp = -tmp;
	}
	while (tmp > 0)
	{
		tmp = tmp / 10;
		count++;
	}
	if (n == 0)
		count++;
	return (dest(n, count));
}

int	ft_is_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = ft_is_whitespace(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (sign * res);
}
