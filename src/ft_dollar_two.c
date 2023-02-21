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

int	ft_size_malloc(char *data, char *env, int start_data, int start_env)
{
	int	size_data;
	int	size_env;
	int	size_dollar;
	int	len;

	size_data = (int)ft_strlen(data);
	size_env = ft_env_len(env, start_env);
	size_dollar = ft_dollar_len(data, start_data - 1);
	len = size_data - size_dollar + size_env;
	return (len);
}

char	*ft_malloc_cpy(char *data, char *env, int size)
{
	int		ret_i;
	int		env_i;
	int		data_i;
	char	*ret;

	ret_i = 0;
	ret = malloc(sizeof(char) * size + 1);
	if (!ret)
		exit (EXIT_FAILURE);
	while (data[ret_i] && data[ret_i] != DOLLAR)
	{
		ret[ret_i] = data[ret_i];
		ret_i++;
	}
	env_i = ft_dollar_len(data, ret_i + 1) + 1;
	data_i = env_i + ret_i;
	while (env[env_i])
		ret[ret_i++] = env[env_i++];
	while (data[data_i])
		ret[ret_i++] = data[data_i++];
	ret[ret_i] = 0;
	return (ret);
}

char	*ft_replace(char *data, char *env)
{
	int		data_i;
	int		env_i;
	int		size_malloc;
	char	*ret;

	data_i = 0;
	env_i = 0;
	while (data[data_i] && data[data_i] != DOLLAR)
		data_i++;
	data_i++;
	while (env[env_i] == data[data_i + env_i])
		env_i++;
	env_i++;
	size_malloc = ft_size_malloc(data, env, data_i, env_i);
	ret = ft_malloc_cpy(data, env, size_malloc);
	free(data);
	return (ret);
}

int	ft_iteration(char c)
{
	if ((c == 95 || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	|| (c >= '0' && c <= '9')))
		return (TRUE);
	return (FALSE);
}

char	*ft_remove_dollar(char *data)
{
	char	*ret;
	int		start;
	int		end;
	int		size;
	int		i;

	start = 0;
	while (data[start] && data[start] != DOLLAR)
		start++;
	end = start + 1;
	while (data[end] && ft_iteration(data[end]) == TRUE)
		end++;
	size = (int)ft_strlen(data) - end + start;
	ret = malloc(sizeof(char) * size + 1);
	if (!ret)
		exit (EXIT_FAILURE);
	size = 0;
	i = 0;
	while (data[i] && size < start)
		ret[size++] = data[i++];
	while (data[end])
		ret[size++] = data[end++];
	free(data);
	ret[size] = 0;
	return (ret);
}
