/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:03:36 by max               #+#    #+#             */
/*   Updated: 2023/02/08 16:13:36 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_to_name(t_shell *tmp, t_shell *new, int option)
{
	if (option == 0)
	{
		ft_lst_new(&new, tmp->data, FALSE, tmp->index);
		if (tmp->next && tmp->index != SPACE && \
		(tmp->next->index == GREAT || tmp->next->index == SMALL))
			ft_lst_new(&new, " ", FALSE, 0);
	}
	else
	{
		ft_lst_new(&new, tmp->data, FALSE, tmp->index);
		if (tmp->next && tmp->next->index != SPACE)
			ft_lst_new(&new, " ", FALSE, 0);
	}
}

t_shell	*ft_space_redops(t_shell **shell)
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
		if (tmp->index != GREAT && tmp->index != SMALL)
			ft_to_name(tmp, new, 0);
		else
			ft_to_name(tmp, new, 1);
		tmp = tmp->next;
	}
	ft_free_shell(*shell);
	free(*shell);
	return (new);
}

void	ft_split_redirections(t_shell **shell, char *str)
{
	int		i;
	int		j;
	char	type;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == GREAT || str[i] == SMALL)
		{
			type = str[i];
			while (str[i + j] == type)
				j++;
			ft_lst_new(shell, parse_quotation(&str[i], type, j, 0), TRUE, 0);
		}
		else if (str[i])
		{
			while (str[i + j] && str[i + j] != SMALL && str[i + j] != GREAT)
				j++;
			ft_lst_new(shell, parse_quotation(&str[i], 0, j, 0), TRUE, 0);
		}
		else
			return ;
		i += j;
	}
}

void	ft_split_add(t_shell *tmp, t_shell *new)
{
	int	i;

	i = 0;
	if (tmp->index == GREAT || tmp->index == SMALL)
		tmp->index = CHARS;
	if (tmp->index == CHARS)
	{
		while (tmp->data[i] != GREAT && tmp->data[i] != SMALL && tmp->data[i])
			i++;
		if (tmp->data[i] == GREAT || tmp->data[i] == SMALL)
			ft_split_redirections(&new, tmp->data);
		else
			ft_lst_new(&new, tmp->data, FALSE, 0);
	}
	else
		ft_lst_new(&new, tmp->data, FALSE, 0);
}

t_shell	*parsing_redops(t_shell **shell)
{
	t_shell	*tmp;
	t_shell	*tmp2;
	t_shell	*new;

	new = malloc(sizeof(t_shell));
	if (!new)
		exit (EXIT_FAILURE);
	new->next = NULL;
	tmp = (*shell)->next;
	tmp2 = (*shell);
	while (tmp)
	{
		ft_split_add(tmp, new);
		tmp = tmp->next;
	}
	*shell = tmp2;
	ft_free_shell(*shell);
	free(*shell);
	return (new);
}
