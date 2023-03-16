/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_dolla.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:29:16 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/14 14:28:28 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_remove_dollar(char *data, int start)
{
	char	*ret;
	int		end;
	int		size;
	int		i;

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

char	*ft_repdoll(char **env, char *data, int status)
{
	int	j;
	int	index;
	int	place;

	place = ft_get_dollar_place(data);
	j = 0;
	index = FALSE;
	if (data[place + 1] == QUESTION)
		return (ft_replace_status(data, status, place));
	while (env[j])
	{
		if (ft_look_in_envp(data, env[j], place + 1) == TRUE)
		{
			data = ft_replace(data, env[j], place + 1);
			index = TRUE;
			break ;
		}
		j++;
	}
	if (index == FALSE)
		data = ft_remove_dollar(data, place);
	return (data);
}

void	ft_pars_dollar(t_tabs **tabs, t_var *var)
{
	t_tabs	*tmp;
	int		i;

	tmp = (*tabs)->next;
	while (tmp)
	{
		i = 0;
		while (tmp->cmds[i])
		{
			while (ft_look_for_dollar(tmp->cmds[i]) == TRUE)
				tmp->cmds[i] = ft_repdoll(var->env, tmp->cmds[i], var->tmp_g);
			i++;
		}
		i = 0;
		while (tmp->redop[i])
		{
			while (ft_look_for_dollar(tmp->redop[i]) == TRUE)
				tmp->redop[i] = ft_repdoll(var->env, tmp->redop[i], var->tmp_g);
			i++;
		}
		tmp = tmp->next;
	}
}
