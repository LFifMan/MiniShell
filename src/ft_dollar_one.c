/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:27:44 by max               #+#    #+#             */
/*   Updated: 2023/02/10 14:16:52 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_replace_status(char *data, int status)
{ 
	int		i;
	int		j;
	int		k;
	char	*str_status;
	char	*dest;

	str_status = ft_itoa(status);
	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(data) + ft_strlen(str_status) - 1));
	while (data[i] && data[i] != DOLLAR)
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

int	ft_look_for_status(char *data)
{
	int	i;

	i = 0;
	while (data[i] && data[i] != DOLLAR)
		i++;
	if (data[i + 1] && data[i] == DOLLAR && data[i + 1] == QUESTION)
		return (TRUE);
	return (FALSE);
}

char	*ft_to_be_named(char **env, char *data, int status)
{
	int	j;
	int	index;

	j = 0;
	index = FALSE;
	if (ft_look_for_status(data) == TRUE)
	{
		return (ft_replace_status(data, status));
	}
	while (env[j])
	{
		if (ft_look_in_envp(data, env[j]) == TRUE)
		{
			data = ft_replace(data, env[j]);
			index = TRUE;
			break ;
		}
		j++;
	}
	if (index == FALSE)
		data = ft_remove_dollar(data);
	return (data);
}

void	ft_pars_dollar(t_shell **shell, t_var *var)
{
	t_shell	*tmp;

	tmp = (*shell)->next;
	while (tmp)
	{
		if (tmp->index == DQ || tmp->index == CHARS || tmp->index == DOLLAR)
			while (ft_look_for_dollar(tmp->data) == TRUE)
				tmp->data = ft_to_be_named(var->env, tmp->data, var->tmp_g);
		tmp = tmp->next;
	}
}
