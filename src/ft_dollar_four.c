/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_four.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:29:16 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/20 14:20:46 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_words_dollars(char *cmd, int cw, int cs, int cc)
{
	int	i;

	i = 0;
	if ((cmd[0] == SPACE || (cmd[0] >= 9 && cmd[0] <= 13)))
		cs++;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == SPACE || (cmd[i] >= 9 && cmd[i] <= 13)))
			i++;
		if (!cmd[i])
			break ;
		cw++;
		while (cmd[i] && (cmd[i] != SPACE && (cmd[i] < 9 || cmd[i] > 13)))
		{
			i++;
			cc++;
		}
	}
	if (cmd[i - 1] && (cmd[i - 1] == SPACE || \
	(cmd[i - 1] >= 9 && cmd[i - 1] <= 13)))
		cs++;
	return (((cw * 2) + cw - 1) + cc + cs);
}

char	*ft_rep_quotes(char *cmd, int i, int j)
{
	char	*ret;

	ret = ft_malloc_str(count_words_dollars(cmd, 0, 0, 0) + 1);
	if ((cmd[0] == SPACE || (cmd[0] >= 9 && cmd[0] <= 13)))
		ret[j++] = SPACE;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == SPACE || (cmd[i] >= 9 && cmd[i] <= 13)))
			i++;
		if (!cmd[i])
			break ;
		if (j != 0 && ret[j - 1] != SPACE)
			ret[j++] = SPACE;
		ret[j++] = DQ;
		while (cmd[i] && (cmd[i] != SPACE && (cmd[i] < 9 || cmd[i] > 13)))
			ret[j++] = cmd[i++];
		ret[j++] = DQ;
	}
	if (cmd[i - 1] && (cmd[i - 1] == SPACE || \
	(cmd[i - 1] >= 9 && cmd[i - 1] <= 13)))
		ret[j++] = SPACE;
	ret[j] = 0;
	return (ret);
}
