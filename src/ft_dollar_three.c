/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_ctrl_twr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:27:44 by max               #+#    #+#             */
/*   Updated: 2023/02/03 16:18:56 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_look_for_dollar(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == DOLLAR)
			if (data[i + 1] != SPACE && data[i + 1] != 0)
				return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_check_allowed_char(char c, int pos)
{
	if (c >= 'a' && c <= 'z')
		return (TRUE);
	if (c >= 'A' && c <= 'Z')
		return (TRUE);
	if (c == '_' || (c >= '0' && c <= '9' && pos != 1))
		return (TRUE);
	return (FALSE);
}

int	ft_look_in_envp(char *data, char *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i] != DOLLAR)
		i++;
	i++;
	while (data[i + j] && env[j] != '=' && data[i + j] == env[j])
	{
		if (ft_check_allowed_char(data[i + j], i + j) == FALSE)
			break ;
		j++;
	}
	if (env[j] == '=' && ft_check_allowed_char(data[i + j], i + j) == FALSE)
		return (TRUE);
	return (FALSE);
}

int	ft_dollar_len(char *data, int start)
{
	int	len;

	len = 0;
	while (data[start] && ft_check_allowed_char(data[start], start) == TRUE)
	{
		start++;
		len++;
	}
	return (len);
}

int	ft_env_len(char *env, int start)
{
	int	len;

	len = 0;
	while (env[start])
	{
		start++;
		len++;
	}
	return (len);
}
