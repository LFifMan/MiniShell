/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:38:40 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/07 16:39:17 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parse_quotation(char *input, char index, int size, int i)
{
	char	*data;

	if (index == DQ || index == SQ)
	{
		data = malloc(sizeof(char) * size + 3);
		if (!data)
			exit (EXIT_FAILURE);
		data[i] = index;
		i--;
		while (++i < size)
			data[i + 1] = input[i];
		data[++i] = index;
		data[++i] = 0;
	}
	else
	{
		data = malloc(sizeof(char) * size + 1);
		if (!data)
			exit (EXIT_FAILURE);
		i--;
		while (++i < size)
			data[i] = input[i];
		data[i] = 0;
	}
	return (data);
}

int	parsing_quotations(t_shell **shell, char *input)
{
	int		i;
	int		j;
	char	type;

	i = 0;
	while (input[i])
	{
		j = 0;
		if (input[i] == DQ || input[i] == SQ)
		{
			type = input[i++];
			while (input[i + j] && input[i + j] != type)
				j++;
			if (!input[i + j])
				return (FALSE);
			ft_lst_new(shell, parse_quotation(&input[i], type, j, 0), TRUE);
			i++;
		}
		else
		{
			while (input[i + j] && input[i + j] != SQ && input[i + j] != DQ)
				j++;
			ft_lst_new(shell, parse_quotation(&input[i], \
			0, j, 0), TRUE);
		}
		i += j;
	}
	return (TRUE);
}

void	split_spaces(t_shell **shell, char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		if (input[i] == SPACE)
		{
			while (input[i + j] == SPACE)
				j++;
			ft_lst_new(shell, parse_quotation(&input[i], SPACE, j, 0), TRUE);
		}
		else if (input[i])
		{
			while (input[i + j] && input[i + j] != SPACE)
				j++;
			ft_lst_new(shell, parse_quotation(&input[i], 0, j, 0), TRUE);
		}
		else
			return ;
		i += j;
	}
}

t_shell	*parsing_spaces(t_shell **shell)
{
	t_shell	*tmp;
	t_shell	*new;

	new = malloc(sizeof(t_shell));
	if (!new)
		exit (EXIT_FAILURE);
	new->next = NULL;
	tmp = (*shell)->next;
	while (tmp)
	{
		if (tmp->index == SQ || tmp->index == DQ)
			ft_lst_new(&new, tmp->data, FALSE);
		else
			split_spaces(&new, tmp->data);
		tmp = tmp->next;
	}
	ft_free_shell(*shell);
	free(*shell);
	return (new);
}
