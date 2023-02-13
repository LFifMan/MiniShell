/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_dolla.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:29:16 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/13 18:02:43 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



char	*ft_replace_status2(char *data, int status, int place)
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




int	ft_look_in_envp2(char *data, char *env, int i)
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




char	*ft_replace2(char *data, char *env, int data_i)
{
	int		env_i;
	int		i;
	int		size_malloc;
	char	*ret;

	env_i = 0;
	i = 0;
	while (env[env_i] == data[data_i + env_i])
		env_i++;
	env_i++;
	ret = malloc(sizeof(char) * (data_i + 1));
	while (i < data_i - 1)
	{
		ret[i] = data[i];
		i++;
	}
	ret[i] = 0;
	size_malloc = ft_strlen(env) + ft_strlen(data) - env_i - env_i;
	//size_malloc = ft_size_malloc(data, env, data_i, env_i);
	ret = ft_strjoin(ret, &env[env_i], FALSE);
	ret = ft_strjoin(ret, &data[data_i + env_i - 1], FALSE);
	printf("%s\n", ret);
	//ret = ft_malloc_cpy(data, env, size_malloc);
	free(data);
	return (ret);
}

char	*ft_remove_dollar2(char *data, int start)
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


char	*ft_replace_dollar2(char **env, char *data, int status)
{
	int	j;
	int	index;
	int	place;

	place = ft_get_dollar_place(data);
	j = 0;
	index = FALSE;
	if (!data[place]) // test to remove
		printf("wft\n");
	if (data[place + 1] == QUESTION)
	{
		return (ft_replace_status2(data, status, place));
	}
	while (env[j])
	{
		if (ft_look_in_envp2(data, env[j], place + 1) == TRUE)
		{
			data = ft_replace2(data, env[j], place + 1);
			index = TRUE;
			break ;
		}
		j++;
	}
	if (index == FALSE)
		data = ft_remove_dollar2(data, place);
	return (data);
}


void	ft_pars_dollar2(t_tabs **tabs, t_var *var)
{
	t_tabs	*tmp;
	int		i;

	tmp = (*tabs)->next;
	while (tmp)
	{
		i = 0;
		while (tmp->cmds[i])
		{
			while (ft_look_for_dollar2(tmp->cmds[i]) == TRUE)
				tmp->cmds[i] = ft_replace_dollar2(var->env, tmp->cmds[i], var->tmp_g);
			i++;
		}
		i = 0;
		while (tmp->redop[i])
		{
			while (ft_look_for_dollar2(tmp->redop[i]) == TRUE)
				tmp->redop[i] = ft_replace_dollar2(var->env, tmp->redop[i], var->tmp_g);
			i++;
		}
		tmp = tmp->next;
	}
}


/* DONE */






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
		}
		else if (data[i] == DQ)
		{
			i++;
			while (data[i] != DQ)
			{
				if (data[i] == DOLLAR)
					if (data[i + 1] != SPACE && data[i + 1] != 0)
						return (i);
				i++;
			}
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
		if (data[i])
			i++;
	}
	return (i);
}


int	ft_look_for_dollar2(char *data)
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
 		}
		else if (data[i] == DQ)
		{
			i++;
			while (data[i] != DQ)
			{
				if (data[i] == DOLLAR)
					if (data[i + 1] != SPACE && data[i + 1] != 0)
						return (TRUE);
				i++;
			}
		}
		else
		{
			while (data[i] && data[i] != SQ && data[i] != DQ)
			{
				if (data[i] == DOLLAR)
					if (data[i + 1] != SPACE && data[i + 1] != 0)
						return (TRUE);

				i++;
			}
		}
		if (data[i])
			i++;
	}
	return (FALSE);
}


// REMOVED
/*
int	ft_look_for_status(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == SQ) // put to a function
		{
			i++;
			while (data[i] != SQ)
				i++;
		}
		else if (data[i] == DQ) // put to a function
		{
			i++;
			while (data[i] != DQ)
			{
				if (data[i] == DOLLAR)
					if (data[i + 1] && data[i] == DOLLAR && data[i + 1] == QUESTION)
						return (TRUE);
				i++;
			}
		}
		else
		{
			while (data[i] != DQ && data[i] != SQ)
			{
				if (data[i] == DOLLAR)
					if (data[i + 1] && data[i] == DOLLAR && data[i + 1] == QUESTION)
						return (TRUE);

				i++;
			}
		}
		i++;
	}
	return (FALSE);
}



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
	while (data[i])
	{
		if (data[i] == SQ)
		{
			dest[i] = data[i];
			i++;
			while (data[i] != SQ)
			{
				dest[i] = data[i];
				i++;
			}
			dest[i] = data[i];
			i++;
		}
		else if (data[i] == DQ)
		{
			dest[i] = data[i];
			i++;
			while (data[i] != DQ)
			{
				if (data[i] == DOLLAR)
				{
					dest = ft_strjoin(ft_strjoin(dest, str_status, TRUE), &data[i + 2], FALSE);
					free(data);
					return (dest);
				}
				else
					dest[i] = data[i];
				i++;
			}
			dest[i] = data[i];
			i++;
		}
		else
		{
			while (data[i] != DQ && data[i] != SQ)
			{
				if (data[i] == DOLLAR)
				{
					dest = ft_strjoin(ft_strjoin(dest, str_status, TRUE), &data[i + 2], FALSE);
					free(data);
					return (dest);
				}
				else
					dest[i] = data[i];
				i++;
			}
		}
	}
	return (dest);
}
*/