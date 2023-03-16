/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:29:16 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/10 17:33:30 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	loop_get_dollar_place(char *data, int i)
{
	if (data[i] == DQ)
	{
		i++;
		while (data[i] != DQ)
		{
			if (data[i] == DOLLAR)
				if (data[i + 1] != SPACE && data[i + 1] != 0)
					return (i);
			i++;
		}
		i++;
	}
	else
	{
		while (data[i] && data[i] != SQ && data[i] != DQ)
		{
			if (data[i] == DOLLAR)
				if (data[i + 1] != SPACE && data[i + 1] != 0)
					return (i);
			i++;
		}
	}
	return (i);
}

int	ft_get_dollar_place(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == SQ)
		{
			i++;
			while (data[i] != SQ)
				i++;
			i++;
		}
		else
		{
			i = loop_get_dollar_place(data, i);
			if (data[i] == DOLLAR)
				return (i);
		}
	}
	return (i);
}

int	loop_look_for_dollar(char *data, int i)
{
	if (data[i] == DQ)
	{
		i++;
		while (data[i] != DQ)
		{
			if (data[i] == DOLLAR)
				if (data[i + 1] != SPACE && data[i + 1] != 0)
					return (i);
			i++;
		}
		i++;
	}
	else
	{
		while (data[i] && data[i] != SQ && data[i] != DQ)
		{
			if (data[i] == DOLLAR)
				if (data[i + 1] != SPACE && data[i + 1] != 0)
					return (i);
			i++;
		}
	}
	return (i);
}

int	ft_look_for_dollar(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == SQ)
		{
			i++;
			while (data[i] && data[i] != SQ)
				i++;
			if (data[i])
				i++;
		}
		else
		{
			i = loop_look_for_dollar(data, i);
			if (data[i] == DOLLAR)
				return (TRUE);
		}
	}
	return (FALSE);
}
