/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:29:16 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/17 18:28:15 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_iteration(char c)
{
	if ((c == 95 || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	|| (c >= '0' && c <= '9')))
		return (TRUE);
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

char	*ft_replace_status(char *data, int status, int place)
{
	int		i;
	int		j;
	int		k;
	char	*str_status;
	char	*dest;

	str_status = ft_itoa(status);
	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(data) + ft_strlen(str_status) - 1));
	while (i < place)
	{
		dest[i] = data[i];
		i++;
	}
	k = i + 2;
	j = 0;
	while (str_status[j])
		dest[i++] = str_status[j++];
	while (data[k])
		dest[i++] = data[k++];
	dest[i] = 0;
	free(data);
	free(str_status);
	return (dest);
}

int	ft_look_in_envp(char *data, char *env, int i)
{
	int	j;

	j = 0;
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

int	count_words_dollars(char *cmd, int cw, int cs, int cc)
{
	int	i;

	i = 0;
	if (cmd[0] == SPACE) // white space
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
	if (cmd[i - 1] == SPACE) // white space
		cs++;
	return(((cw * 2) + cw - 1) + cc + cs);
}

char	*ft_rep_quotes(char *cmd)
{
	int		i;
	int		j;
	char	*ret;

	ret = ft_malloc_str(count_words_dollars(cmd, 0, 0, 0) + 1);
	i = 0;
	j = 0;
	if (cmd[0] == SPACE) // white space
		ret[j++] = SPACE;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == SPACE || (cmd[i] >= 9 && cmd[i] <= 13)))
			i++;
		// the space could be put here! and must
		if (!cmd[i])
			break ;
		if (j != 0 && ret[j - 1] != SPACE)
			ret[j++] = SPACE;
		ret[j++] = DQ;
		while (cmd[i] && (cmd[i] != SPACE && (cmd[i] < 9 || cmd[i] > 13)))
		{
			ret[j] = cmd[i];
			i++;
			j++;
		}
		ret[j++] = DQ;
	}
	if (cmd[i - 1] == SPACE) // white space
		ret[j++] = SPACE;
	ret[j] = 0;
	return (ret);
}

char	*ft_replace(char *data, char *env, int data_i)
{
	int		env_i;
	int		i;
	char	*ret;

	//todo: check whitespace --> return a str with 1 space
	if (ft_is_whitespace(data) == TRUE)
		return (ft_strdup(" ", FALSE));
	env_i = 0;
	i = 0;
	while (env[env_i] == data[data_i + env_i])
		env_i++;
	env_i++;
	ret = malloc(sizeof(char) * (data_i + 1)); // todo: add check malloc +  + 3?
	while (i < data_i - 1)
	{
		ret[i] = data[i];
		i++;
	}
	ret[i] = 0;
	ret = ft_strjoin(ret, ft_rep_quotes(&env[env_i]), TRUE); // replace " &env[env_i]" by a func that puts quotes! and strjoin becomes true
	ret = ft_strjoin(ret, &data[data_i + env_i - 1], FALSE);
	free(data);
	return (ret);
}
